#ifndef OSSM_SOFTWARE_EN_US_H
#define OSSM_SOFTWARE_EN_US_H

#include "abstract/CopyStruct.h"

// English copy
static const CopyStruct enUs = {
    .Error = "Error",
    .Homing = "Homing",
    .HomingSensorless = "Finding Home Sensorless",
    .HomingTookTooLong =
        "Homing took too long.\nPlease check your wiring and try again.",
    .NoInternalLoop = "No display handler implemented.",
    .StateNotImplemented = "State: %u not implemented.",
    .YouShouldNotBeHere = "You should not be here.",
    .Idle = "Initializing",
};

#endif  // OSSM_SOFTWARE_EN_US_H
