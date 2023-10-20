#ifndef OSSM_SOFTWARE_EN_US_H
#define OSSM_SOFTWARE_EN_US_H

#include "abstract/LanguageStruct.h"

// English copy
static const LanguageStruct enUs = {
    .Error = "Error",
    .Homing = "Homing",
    .HomingSensorless = "Finding Home Sensorless",
    .HomingTookTooLong =
        "Homing took too long.\nPlease check your wiring and try again.",
    .NoInternalLoop = "No display handler implemented.",
    .StateNotImplemented = "State: %u not implemented.",
    .YouShouldNotBeHere = "You should not be here.",
    .Idle = "Initializing",
    .StrokeTooShort = "Stroke too short. Please check you drive belt."};

#endif  // OSSM_SOFTWARE_EN_US_H
