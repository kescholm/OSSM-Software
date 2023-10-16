#ifndef OSSM_SOFTWARE_CONFIG_H
#define OSSM_SOFTWARE_CONFIG_H

/**
    Default Config for OSSM - Reference board users should tweak UserConfig to
   match their personal build.

    //TODO: restore user overrides with a clever null coalescing operator
*/
namespace Config {

    namespace Limits {
        constexpr float currentLimit = 1.5;
    }

    /**
            Motion System Config
    */
    namespace Driver {

        // Top linear speed of the device.
        constexpr float maxSpeedMmPerSecond = 900.0f;

        // This should match the step/rev of your stepper or servo.
        // N.b. the iHSV57 has a table on the side for setting the DIP switches
        // to your preference.
        constexpr float motorStepPerRevolution = 800.0f;

        // Number of teeth the pulley that is attached to the servo/stepper
        // shaft has.
        constexpr float pulleyToothCount = 20.0f;

        // Set to your belt pitch (Distance between two teeth on the belt) (E.g.
        // GT2 belt has 2mm tooth pitch)
        constexpr float beltPitchMm = 2.0f;

        // This is in millimeters, and is what's used to define how much of
        // your rail is usable.
        // The absolute max your OSSM would have is the distance between the
        // belt attachments subtract the linear block holder length (75mm on
        // OSSM) Recommended to also subtract e.g. 20mm to keep the backstop
        // well away from the device.
        constexpr float maxStrokeLengthMm = 75.f;

        // This is the measured current that use to infer when the device has
        // reached the end of its stroke. during "Homing".
        constexpr float sensorlessCurrentLimit = 1.5f;
    }

    /**
        Web Config
*/
    namespace Web {
        // This should be unique to your device. You will use this on the
        // web portal to interact with your OSSM.
        // there is NO security other than knowing this name, make this unique
        // to avoid collisions with other users
        constexpr char *ossmId = nullptr;
    }

    /**
        Advanced Config
*/
    namespace Advanced {

        // After homingStart this is the physical buffer distance from the
        // effective zero to the home switch This is to stop the home switch
        // being smacked constantly
        constexpr float strokeZeroOffsetmm = 6.0f;
        // The minimum value of the pot in percent
        // prevents noisy pots registering commands when turned down to zero by
        // user
        constexpr float commandDeadzonePercentage = 1.0f;
        // affects acceleration in stepper trajectory (Aggressiveness of motion)
        constexpr float accelerationScaling = 100.0f;
    }

}

#endif  // OSSM_SOFTWARE_CONFIG_H