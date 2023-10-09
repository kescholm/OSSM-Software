#ifndef OSSM_SOFTWARE_PINS_H
#define OSSM_SOFTWARE_PINS_H

/**
 * Pin definitions for the OSSM
 *
 * These are all the hardware pins used by the OSSM.
 * These include pin definitions for Drivers, Buttons and Remotes
 *
 * To reference a pin, import this file and use the Pins namespace as follows:
 *
 * ```cpp
 * #include "constants/pins.h"
 *
 * Pins::button_in
 * Pins::Driver::motor_step_pin
 * Pins::Homing::stop_pin
 *
 * ```
 */

namespace Pins {

    namespace Display {
        // This pin is used by u8g2 to reset the display.
        // Use -1 if this is shared with the board reset pin.
        constexpr int oled_reset = -1;

        // Pin used by RGB LED
        constexpr int led_pin = 25;
    }

    namespace Driver {

        // Pin that pulses on servo/stepper steps - likely labelled PUL on
        // drivers.
        constexpr int motor_step_pin = 14;
        // Pin connected to driver/servo step direction - likely labelled DIR on
        // drivers. N.b. to iHSV57 users - DIP switch #5 can be flipped to
        // invert motor direction entirely
        constexpr int motor_direction_pin = 27;
        // Pin for motor enable - likely labelled ENA on drivers.
        constexpr int motor_enable_pin = 26;
    }

    namespace Homing {
        // define the IO pin the emergency stop switch is connected to
        constexpr int stop_pin = 19;
        // define the IO pin where the limit(homing) switch(es) are connected to
        // (switches in series in normally open setup) Switches wired from IO
        // pin to ground.
        constexpr int limit_switch_pin = 12;
    }

    namespace Wifi {
        // Pin for WiFi reset button (optional)
        constexpr int reset_pin = 23;
        // Pin for the toggle for wifi control (Can be left alone if no hardware
        // toggle is required)
        constexpr int control_toggle_pin = 22;

        // TODO: #OSSM-21 No toggle switch should be required for control. The
        // OSSM should always listen for commands and should decide whether to
        // act on them based on the current control mode. constexpr int
        // control_default = LOCAL_CONTROLLER;
    }

    /** These are configured for the OSSM Remote - which has a screen, a
     * potentiometer and an encoder which clicks*/
    namespace Remote {
        // TODO: #OSSM-23 Documentation for these pins
        constexpr int speed_pot_pin = 34;

        constexpr int encoder_switch = 35;
        constexpr int encoder_a = 18;
        constexpr int encoder_b = 5;
        constexpr int display_data = 21;
        constexpr int display_clock = 19;
    }
}

#endif  // OSSM_SOFTWARE_PINS_H
