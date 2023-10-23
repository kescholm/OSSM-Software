
#include "OSSM.h"

#include "extensions/u8g2Extensions.h"
#include "utilities/analog.h"

void OSSM::drawPlayControlsTask(void *pvParameters) {
    // parse ossm from the parameters
    OSSM *ossm = (OSSM *)pvParameters;
    auto menuString = menuStrings[ossm->menuOption];
    float speedPercentage = 0;
    long strokePercentage = 0;
    int currentTime = 0;

    ossm->speedPercentage = 0;
    ossm->strokePercentage = 0;

    /**
     * /////////////////////////////////////////////
     * //// Safely Block High Speeds on Startup ///
     * /////////////////////////////////////////////
     *
     * This is a safety feature to prevent the user from accidentally beginning
     * a session at max speed. After the user decreases the speed to 0.5% or
     * less, the state machine will be allowed to continue.
     */

    auto isInPreflight = [](OSSM *ossm) {
        // Add your preflight checks states here.
        return ossm->sm->is("simplePenetration.preflight"_s);
    };

    do {
        speedPercentage =
            getAnalogAveragePercent(SampleOnPin{Pins::Remote::speedPotPin, 50});
        if (speedPercentage < 0.5) {
            ossm->sm->process_event(Done{});
            break;
        };

        ossm->display.clearBuffer();
        drawStr::title(menuString);
        String speedString = UserConfig::language.Speed + ": " +
                             String((int)speedPercentage) + "%";
        drawStr::centered(25, speedString);
        drawStr::multiLine(0, 40, UserConfig::language.SpeedWarning);

        ossm->display.sendBuffer();
        vTaskDelay(100);
    } while (isInPreflight(ossm));

    /**
     * /////////////////////////////////////////////
     * /////////// Play Controls Display ///////////
     * /////////////////////////////////////////////
     *
     * This is a safety feature to prevent the user from accidentally beginning
     * a session at max speed. After the user decreases the speed to 0.5% or
     * less, the state machine will be allowed to continue.
     */
    auto isInCorrectState = [](OSSM *ossm) {
        // Add any states that you want to support here.
        return ossm->sm->is("simplePenetration"_s) ||
               ossm->sm->is("simplePenetration.idle"_s);
    };

    // Prepare the encoder
    ossm->encoder.setBoundaries(0, 100, false);
    ossm->encoder.setAcceleration(25);
    ossm->encoder.setEncoderValue(0);

    // TODO: prepare the stepper with safe values.

    int16_t y = 64;
    int16_t w = 10;
    int16_t x;
    int16_t h;
    int16_t padding = 4;

    // Line heights
    int16_t lh1 = 22;
    int16_t lh2 = 34;
    int16_t lh3 = 46;
    int16_t lh4 = 64;

    // record session start time rounded to the nearest second
    ossm->sessionStartTime = floor(millis() / 1000);

    bool valueChanged = false;

    while (isInCorrectState(ossm)) {
        speedPercentage =
            getAnalogAveragePercent(SampleOnPin{Pins::Remote::speedPotPin, 50});
        strokePercentage = ossm->encoder.readEncoder();
        currentTime = floor(millis() / 1000);

        if (ossm->speedPercentage != speedPercentage ||
            ossm->strokePercentage != strokePercentage ||
            ossm->sessionStartTime != currentTime) {
            valueChanged = true;
            ossm->speedPercentage = speedPercentage;
            ossm->strokePercentage = strokePercentage;
        }

        if (!valueChanged) {
            vTaskDelay(100);
            continue;
        }

        if (ossm->speedPercentage > 1.0f) {
            ossm->stepper.setSpeedInMillimetersPerSecond(
                Config::Driver::maxSpeedMmPerSecond * ossm->speedPercentage /
                100.0);
            ossm->stepper.setAccelerationInMillimetersPerSecondPerSecond(
                Config::Driver::maxSpeedMmPerSecond * ossm->speedPercentage *
                ossm->speedPercentage / Config::Advanced::accelerationScaling);
        }

        ossm->display.clearBuffer();
        ossm->display.setFont(Config::Font::base);

        drawStr::title(menuString);

        // draw a rectangle on the left for the speed
        x = 0;
        h = ceil(64 * speedPercentage / 100);
        ossm->display.drawBox(x, y - h, w, h);
        ossm->display.drawFrame(x, 0, w, 64);
        String speedString = UserConfig::language.Speed + ": " +
                             String((int)speedPercentage) + "%";
        ossm->display.drawUTF8(x + w + padding, lh1, speedString.c_str());

        // draw a rectangle on the right for the stroke
        x = 124;
        h = ceil(64 * ossm->encoder.readEncoder() / 100);
        ossm->display.drawBox(x - w, y - h, w, h);
        ossm->display.drawFrame(x - w, 0, w, 64);
        String strokeString = UserConfig::language.Stroke + ": " +
                              String(ossm->encoder.readEncoder()) + "%";
        auto stringWidth = ossm->display.getUTF8Width(strokeString.c_str());
        ossm->display.drawUTF8(x - w - stringWidth - padding, lh2,
                               strokeString.c_str());

        // Draw the session time.

        // TODO: add labels to the session time & stroke count.
        // TODO: Pretty format the time.
        drawStr::centered(lh3, String(currentTime - ossm->sessionStartTime));
        drawStr::centered(lh4, String(ossm->sessionStrokeCount));

        ossm->display.sendBuffer();

        // Saying hi to the watchdog :).
        vTaskDelay(100);
    }

    // Clean up!
    ossm->encoder.setAcceleration(0);

    vTaskDelete(nullptr);
}

void OSSM::drawPlayControls() {
    xTaskCreate(drawPlayControlsTask, "drawPlayControlsTask", 2048, this, 1,
                &displayTask);
}
