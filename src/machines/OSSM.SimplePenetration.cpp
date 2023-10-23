#include "OSSM.h"

#include "constants/Config.h"

void OSSM::startSimplePenetrationTask(void *pvParameters) {
    OSSM *ossm = (OSSM *)pvParameters;

    auto isInCorrectState = [](OSSM *ossm) {
        // Add any states that you want to support here.
        return ossm->sm->is("simplePenetration"_s) ||
               ossm->sm->is("simplePenetration.idle"_s);
    };

    while (isInCorrectState(ossm)) {
        if (ossm->stepper.getDistanceToTargetSigned() != 0) {
            vTaskDelay(5);  // wait for motion to complete and requested stroke
                            // more than zero
            continue;
        }
        ossm->isForward = !ossm->isForward;

        double targetPosition = ossm->isForward
                                    ? -((float)ossm->strokePercentage / 100.0) *
                                          ossm->measuredStrokeMm
                                    : 0;
        LOG_TRACE("Moving stepper to position ",
                  static_cast<long int>(targetPosition));

        ossm->stepper.setDecelerationInMillimetersPerSecondPerSecond(
            Config::Driver::maxSpeedMmPerSecond * ossm->speedPercentage *
            ossm->speedPercentage / Config::Advanced::accelerationScaling);
        vTaskDelay(1);
        ossm->stepper.setTargetPositionInMillimeters(targetPosition);
        vTaskDelay(1);

        //
        //        while ((ossm->stepper.getDistanceToTargetSigned() != 0))
        //        {
        //            vTaskDelay(5); // wait for motion to complete, since we
        //            are going back to
        //            // zero, don't care about stroke value
        //        }
        //        targetPosition = 0;
        //        // Serial.printf("Moving stepper to position %ld \n",
        //        targetPosition); vTaskDelay(1);
        //        stepper.setDecelerationInMillimetersPerSecondPerSecond(maxSpeedMmPerSecond
        //        * speedPercentage * speedPercentage /
        //                                                               accelerationScaling);
        //        stepper.setTargetPositionInMillimeters(targetPosition);
        //        vTaskDelay(1);
        // if (currentStrokeMm > 1)
        //        numberStrokes++;
        //        travelledDistanceMeters += (0.002 * currentStrokeMm);
        //        updateLifeStats();
    }

    vTaskDelete(nullptr);
}

void OSSM::startSimplePenetration() {
    xTaskCreate(startSimplePenetrationTask, "startSimplePenetrationTask", 2048,
                this, 1, &operationTask);
}