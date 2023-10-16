#include "HomePage.h"

#include "DebugLog.h"
#include "services/display.h"
#include "services/stepper.h"
#include "utilities/analog.h"

HomePage::HomePage(OSSM *ossm) {
    LOG_DEBUG("HomePage::HomePage");
    this->ossm = ossm;

    this->startMillis = 0;
    this->currentSensorOffset = 0;
    this->measuredStrokeMm = 0;
}

void HomePage::handleEvent() {
    LOG_TRACE("HomePage::handleEvent");

    if (event == HOME_NS::Events::NONE) {
        return;
    }

    switch (state) {
        case HOME_NS::States::NONE:
            if (event == HOME_NS::Events::DONE) {
                state = HOME_NS::States::HOMING;
            }
            break;
        case HOME_NS::States::HOMING:
            if (event == HOME_NS::Events::DONE) {
                // During the transition from HOMING to HOMING_REVERSE, we will
                // set the target position to a large negative number.
                ossm->stepper.setTargetPositionInMillimeters(-400);
                this->startMillis = millis();
                state = HOME_NS::States::HOMING_REVERSE;
            }
            break;
        case HOME_NS::States::HOMING_REVERSE:
            if (event == HOME_NS::Events::DONE) {
                // During the transition from HOMING to HOMING_REVERSE, we will
                // set the target position to a large positive number.
                ossm->stepper.setTargetPositionInMillimeters(400);
                this->startMillis = millis();
                state = HOME_NS::States::HOMING_FORWARD;
            }
            break;
        case HOME_NS::States::HOMING_FORWARD:
            if (event == HOME_NS::Events::DONE) {
                state = HOME_NS::States::IDLE;
            }
            break;
        case HOME_NS::States::IDLE:
        default:
            break;
    }

    clearEvent();
}

void HomePage::loopInternal() {
    // Use static cast to convert state to a string and log it

    // convert d2 to string
    LOG_DEBUG("HomePage::HomePage state:", (int)state);

    u8g2.setFont(u8g2_font_helvR08_te);
    u8g2.drawUTF8(0, 40, UserConfig::copy.Homing);
    switch (state) {
        case HOME_NS::States::NONE:
            event = HOME_NS::Events::DONE;
            break;
        case HOME_NS::States::HOMING:
            homingStart();
            break;
        case HOME_NS::States::HOMING_REVERSE:
        case HOME_NS::States::HOMING_FORWARD:
            homing();
            break;
        default:
            u8g2.setFont(u8g2_font_helvR08_te);
            u8g2.drawUTF8(0, 40, UserConfig::copy.YouShouldNotBeHere);
    }
}

/**
 * If we're in the homingStart state, then the machine has just been turned on.
 * We will automatically find a suitable play range.
 */
void HomePage::homingStart() {
    LOG_TRACE("HomePage::homingStart");

    // Drop the speed and acceleration to something reasonable.
    ossm->stepper.setAccelerationInMillimetersPerSecondPerSecond(1000);
    ossm->stepper.setDecelerationInMillimetersPerSecondPerSecond(10000);
    ossm->stepper.setSpeedInMillimetersPerSecond(25);

    // Clear the stored values.
    this->measuredStrokeMm = 0;

    // Recalibrate the current sensor offset.
    this->currentSensorOffset =
        (getAnalogAveragePercent(Pins::Driver::currentSensorPin, 1000));

    // Set the event to done so that the machine will move to the next state.
    event = HOME_NS::Events::DONE;
}

void HomePage::homing() {
    // If we've been homing for more than 15 seconds, then the user should check
    // the power and restart.
    if (millis() - this->startMillis > 15000) {
        LOG_ERROR(
            "HomePage::homing, homing took too long. Check power and restart.");
        ossm->setError(UserConfig::copy.HomingTookTooLong);
        return;
    }

    // measure the current analog value.
    float current =
        getAnalogAveragePercent(Pins::Driver::currentSensorPin, 200) -
        currentSensorOffset;

    // If we have not detected a "bump" with a hard stop, then return and let
    // the loops continue.
    if (current < Config::Driver::sensorlessCurrentLimit) {
        return;
    }
    LOG_DEBUG("HOMING BUMP DETECTED");

    // Otherwise, if we have detected a bump, then we need to stop the motor.
    ossm->stepper.setTargetPositionToStop();

    // And then move the motor back by the configured offset.
    // This offset will be positive for reverse homing and negative for forward
    // homing.
    float sign = state == HOME_NS::States::HOMING_REVERSE ? 1.0f : -1.0f;
    ossm->stepper.moveRelativeInMillimeters(
        sign * Config::Advanced::strokeZeroOffsetmm);  //"move to" is blocking

    if (state == HOME_NS::States::HOMING_FORWARD) {
        // If we are homing forward, then we need to measure the stroke length
        // before resetting the home position.
        measuredStrokeMm = abs(ossm->stepper.getCurrentPositionInMillimeters());

        LOG_DEBUG("HomePage::homing, measuredStrokeMm", measuredStrokeMm);
    }
    // And finally, we'll set the most forward position as the new "zero"
    // position.
    ossm->stepper.setCurrentPositionAsHomeAndStop();

    // Set the event to done so that the machine will move to the next state.
    event = HOME_NS::Events::DONE;
}
