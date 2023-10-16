#ifndef OSSM_SOFTWARE_PINS_CPP
#define OSSM_SOFTWARE_PINS_CPP

/**
 * Pin definitions for the OSSM
 *
 * These are all the hardware pins used by the OSSM.
 * These include pin definitions for Drivers, Buttons and Remotes
 *
 * To reference a pin, import this file and use the Pins namespace as follows:
 *
 * ```cpp
 * #include "constants/pins.cpp"
 *
 * Pins::button_in
 * Pins::Driver::motorStepPin
 * Pins::Homing::stopPin
 *
 * ```
 */

namespace Pins {

    enum class Display {
        // This pin is used by u8g2 to reset the display.
        // Use -1 if this is shared with the board reset pin.
        oledReset = -1,

        // Pin used by RGB LED
        ledPin = 25,
    };

    enum class Driver {
        currentSensorPin = 36,

        // Pin that pulses on servo/stepper steps - likely labelled PUL on
        // drivers.
        motorStepPin = 14,
        // Pin connected to driver/servo step direction - likely labelled DIR on
        // drivers. N.b. to iHSV57 users - DIP switch #5 can be flipped to
        // invert motor direction entirely
        motorDirectionPin = 27,
        // Pin for motor enable - likely labelled ENA on drivers.
        motorEnablePin = 26,

        // define the IO pin the emergency stop switch is connected to
        stopPin = 19,
        // define the IO pin where the limit(homingStart) switch(es) are
        // connected to (switches in series in normally open setup) Switches
        // wired from IO pin to ground.
        limitSwitchPin = 12,
    };

    enum class Wifi {
        // Pin for WiFi reset button (optional)
        resetPin = 23,
        // Pin for the toggle for wifi control (Can be target alone if no
        // hardware toggle is required)
        controlTogglePin = 22,

        // TODO: #OSSM-21 No toggle switch should be required for control. The
        // OSSM should always listen for commands and should decide whether to
        // act on them based on the current control mode. constexpr int
        // control_default = LOCAL_CONTROLLER;
    };

    /** These are configured for the OSSM Remote - which has a screen, a
     * potentiometer and an encoder which clicks*/
    enum class Remote {
        // TODO: #OSSM-23 Documentation for these pins
        speedPotPin = 34,
        encoderSwitch = 35,
        encoderA = 18,
        encoderB = 5,
        displayData = 21,
        displayClock = 19,
    };
}

#endif  // OSSM_SOFTWARE_PINS_CPP
