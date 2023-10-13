#ifndef OSSM_SOFTWARE_STEPPER_H
#define OSSM_SOFTWARE_STEPPER_H

#include <ESP_FlexyStepper.h>

#include "constants/Config.h"
#include "constants/Pins.h"

/**
 * Here are all the initialization steps for the stepper motor.
 * @param stepper
 */
void initStepper(ESP_FlexyStepper *stepper) {
    stepper = new ESP_FlexyStepper();
    stepper->connectToPins(Pins::Driver::motorStepPin,
                           Pins::Driver::motorDirectionPin);
    stepper->setLimitSwitchActive(Pins::Driver::limitSwitchPin);

    float stepsPerMm =
        Config::Driver::motorStepPerRevolution /
        (Config::Driver::pulleyToothCount * Config::Driver::beltPitchMm);

    stepper->setStepsPerMillimeter(stepsPerMm);
    stepper->startAsService();
}

#endif  // OSSM_SOFTWARE_STEPPER_H
