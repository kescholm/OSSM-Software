
#include "OSSM.h"

#include "extensions/u8g2Extensions.h"
#include "utilities/analog.h"

void OSSM::drawPlayControlsTask(void *pvParameters) {
    // parse ossm from the parameters
    OSSM *ossm = (OSSM *)pvParameters;
    auto menuString = menuStrings[ossm->menuOption];

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
        float speedPercentage =
            getAnalogAveragePercent(SampleOnPin{Pins::Remote::speedPotPin, 50});
        if (speedPercentage < 0.5) {
            ossm->sm->process_event(Done{});
            break;
        };

        ossm->display.clearBuffer();
        drawStr::title(menuString);
        String speedString =
            UserConfig::language.Speed + ": " + String(speedPercentage) + "%";
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

    while (isInCorrectState(ossm)) {
        ossm->display.clearBuffer();

        drawStr::title(menuString);
        ossm->display.sendBuffer();

        // Saying hi to the watchdog :).
        vTaskDelay(100);
    }

    vTaskDelete(nullptr);
}

void OSSM::drawPlayControls() {
    // Use the handle to delete the task.
    //    if (displayTask != nullptr) {
    //        vTaskDelete(displayTask);
    //    }
    // start the draw menu task
    xTaskCreate(drawPlayControlsTask, "drawPlayControlsTask", 2048, this, 1,
                &displayTask);
}
