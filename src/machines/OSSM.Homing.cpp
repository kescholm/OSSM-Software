#include "OSSM.h"

#include <DebugLog.h>

#include "constants/UserConfig.h"
#include "extensions/u8g2Extensions.h"
#include "services/stepper.h"
#include "utilities/analog.h"

namespace sml = boost::sml;
using namespace sml;

/** OSSM Homing methods
 *
 * This is a collection of methods that are associated with the homing state on
 * the OSSM. technically anything can go here, but please try to keep it
 * organized.
 */
void OSSM::clearHoming() {
    LOG_TRACE("HomePage::homingStart");
    isForward = true;

    // Drop the speed and acceleration to something reasonable.
    stepper.setAccelerationInMillimetersPerSecondPerSecond(1000);
    stepper.setDecelerationInMillimetersPerSecondPerSecond(10000);
    stepper.setSpeedInMillimetersPerSecond(25);

    // Clear the stored values.
    this->measuredStrokeMm = 0;

    // Recalibrate the current sensor offset.
    this->currentSensorOffset = (getAnalogAveragePercent(
        SampleOnPin{Pins::Driver::currentSensorPin, 1000}));
};

void OSSM::homingTask(void *pvParameters) {
    LOG_DEBUG("OSSM::homingTask :D");
    TickType_t xTaskStartTime = xTaskGetTickCount();

    // parse parameters to get OSSM reference
    auto ossm = static_cast<OSSM *>(pvParameters);

    float target = ossm->isForward ? -400 : 400;
    ossm->stepper.setTargetPositionInMillimeters(target);

    // run loop for 15second or until loop exits
    do {
        TickType_t xCurrentTickCount = xTaskGetTickCount();
        // Calculate the time in ticks that the task has been running.
        TickType_t xTicksPassed = xCurrentTickCount - xTaskStartTime;

        // If you need the time in milliseconds, convert ticks to milliseconds.
        // 'portTICK_PERIOD_MS' is the number of milliseconds per tick.
        uint32_t msPassed = xTicksPassed * portTICK_PERIOD_MS;

        if (msPassed > 15000) {
            LOG_ERROR(
                "HomePage::homing, homing took too long. Check power and "
                "restart.");
            ossm->sm->process_event(Error{});
            break;
        }

        // measure the current analog value.
        float current = getAnalogAveragePercent(
                            SampleOnPin{Pins::Driver::currentSensorPin, 200}) -
                        ossm->currentSensorOffset;

        LOG_DEBUG("current: " + String(current));

        // If we have not detected a "bump" with a hard stop, then return and
        // let the loop continue.
        if (current < Config::Driver::sensorlessCurrentLimit) {
            // Wait a millisecond to let the other tasks run.
            vTaskDelay(1);
            continue;
        }

        LOG_DEBUG("HOMING BUMP DETECTED");

        // Otherwise, if we have detected a bump, then we need to stop the
        // motor.
        ossm->stepper.setTargetPositionToStop();

        // And then move the motor back by the configured offset.
        // This offset will be positive for reverse homing and negative for
        // forward homing.
        float sign = ossm->isForward ? 1.0f : -1.0f;
        ossm->stepper.moveRelativeInMillimeters(
            sign *
            Config::Advanced::strokeZeroOffsetmm);  //"move to" is blocking

        if (ossm->isForward) {
            // If we are homing forward, then we need to measure the stroke
            // length before resetting the home position.
            ossm->measuredStrokeMm =
                abs(ossm->stepper.getCurrentPositionInMillimeters());

            LOG_DEBUG("HomePage::homing, measuredStrokeMm: " +
                      String(ossm->measuredStrokeMm));
        }

        // And finally, we'll set the most forward position as the new "zero"
        // position.
        ossm->stepper.setCurrentPositionAsHomeAndStop();

        // Set the event to done so that the machine will move to the next
        // state.
        ossm->sm->process_event(Done{});
        break;
    } while (true);

    vTaskDelete(nullptr);
}

void OSSM::homing() {
    // Create task
    xTaskCreate(homingTask, "homingTask", 10000, this, 1, nullptr);
}

auto OSSM::isStrokeTooShort() -> bool {
    if (measuredStrokeMm > Config::Advanced::minStrokeLengthmm) {
        return false;
    }
    this->errorMessage = UserConfig::language.StrokeTooShort;
    return true;
}