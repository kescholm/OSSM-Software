#ifndef OSSM_SOFTWARE_OSSM_H
#define OSSM_SOFTWARE_OSSM_H

#include <memory>

#include "AiEsp32RotaryEncoder.h"
#include "ESP_FlexyStepper.h"
#include "Events.h"
#include "U8g2lib.h"
#include "boost/sml.hpp"
#include "constants/Menu.h"
#include "utilities/StateLogger.h"

namespace sml = boost::sml;

class OSSM {
  private:
    /**
     * ///////////////////////////////////////////
     * ////
     * ////  OSSM State Machine
     * ////
     * ///////////////////////////////////////////
     *
     * This is the state machine that controls the OSSM.
     * It's based on the Boost SML library, and you don't need to be an expert
     *to use it, just follow the examples in this table:
     *
     * https://boost-ext.github.io/sml/tutorial.html#:~:text=3.%20Create%20a%20transition%20table
     *
     * Here are the basic rules:
     *  1. Each row in the table is a transition.
     *  2. Each transition has a source state, an event, a guard, an action, and
     *      a target state.
     *  3. The source state is the state that the machine must be in for the
     *      transition to be valid.
     *  4. (optional) The event is the event that triggers the transition.
     *  5. (optional) The guard is a function that returns true or false. If it
     *      returns true, then the transition is valid.
     *  6. (optional) The action is a function that is called when the
     *transition is triggered, it can't block the main thread and cannot return
     *a value.
     *  7. The target state is the state that the machine will be in after the
     *      transition is complete.
     *
     * Have fun!
     */
    struct OSSMStateMachine {
        auto operator()() const {
            // Definitions to make the table easier to read.
            static auto buttonPress = sml::event<ButtonPress>;
            static auto done = sml::event<Done>;
            static auto error = sml::event<Error>;

            using namespace sml;
            return make_transition_table(
                // The initial state is "idle"

                *"idle"_s + done / [](OSSM &o) { o.drawHello(); } = "homing"_s,

                // Start Homing
                "homing"_s /
                    [](OSSM &o) {
                        o.clearHoming();
                        o.homing();
                    } = "homing.idle"_s,

                // Wait for the homing task to finish the first pass and listen
                // for a motor failure.
                "homing.idle"_s + error = "error"_s,
                "homing.idle"_s + done /
                                      [](OSSM &o) {
                                          o.isForward = false;
                                          o.homing();
                                      } = "homing.backward"_s,

                // Start the second pass of homing.
                // Wait for the homing task to finish the second pass and listen
                // for a motor failure.
                "homing.backward"_s + error = "error"_s,
                "homing.backward"_s +
                    done[([](OSSM &o) { return o.isStrokeTooShort(); })] =
                    "error"_s,
                "homing.backward"_s + done = "menu"_s,

                // TODO: Add a menu state.
                //  Right now the menu state is just the hello world screen, and
                //  on button press this will go back to homing.
                "menu"_s / [](OSSM &o) { o.drawMenu(); } = "menu.idle"_s,
                "menu.idle"_s + buttonPress[([](OSSM &o) {
                    return o.menuOption == MenuOption::Play;
                })] = "homing"_s,
                "menu.idle"_s + buttonPress[([](OSSM &o) {
                    return o.menuOption == MenuOption::Help;
                })] = "help"_s,
                "menu.idle"_s + buttonPress[([](OSSM &o) {
                    return o.menuOption == MenuOption::Restart;
                })] = "restart"_s,

                "play"_s / [](OSSM &o) { o.drawPlay(); } = "play.idle"_s,
                // TODO: Change this to a long press so that you don't
                // accidentally exit.
                "play.idle"_s + event<ButtonPress> = "menu"_s,

                "help"_s / [](OSSM &o) { o.drawHelp(); } = "help.idle"_s,
                // TODO: Change this to a long press so that you don't
                // accidentally exit.
                "help.idle"_s + event<ButtonPress> = "menu"_s,

                // You hit an error. Stop the motor and wait for the button to
                // be pressed. on Click, show the help screen. And then on
                // second click, restart the machine.
                "error"_s / [](OSSM &o) { o.emergencyStop(); } = "error.idle"_s,
                "error.idle"_s +
                    event<ButtonPress> / [](OSSM &o) { o.drawHelp(); } =
                    "error.help"_s,
                "error.help"_s + event<ButtonPress> / [] { ESP.restart(); } = X,

                // Restart the machine, instantly.
                "restart"_s / [] { ESP.restart(); } = X);
        }
    };

    /**
     * ///////////////////////////////////////////
     * ////
     * ////  Private Objects and Services
     * ////
     * ///////////////////////////////////////////
     */
    ESP_FlexyStepper stepper;
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display;
    StateLogger logger;
    AiEsp32RotaryEncoder &encoder;

    /**
     * ///////////////////////////////////////////
     * ////
     * ////  Private Variables and Flags
     * ////
     * ///////////////////////////////////////////
     */
    float currentSensorOffset = 0;
    float measuredStrokeMm = 0;
    bool isForward = true;
    String errorMessage = "";
    MenuOption menuOption = MenuOption::Play;

    /**
     * ///////////////////////////////////////////
     * ////
     * ////  Private Functions
     * ////
     * ///////////////////////////////////////////
     */
    void clearHoming();

    void homing();

    bool isStrokeTooShort();

    void emergencyStop();

    void drawHello();

    void drawHelp();

    void drawMenu();

    void drawPlay();

    /**
     * ///////////////////////////////////////////
     * ////
     * ////  Static Functions and Tasks
     * ////
     * ///////////////////////////////////////////
     */
    static void homingTask(void *pvParameters);

    static void drawHelloTask(void *pvParameters);

    static void drawMenuTask(void *pvParameters);

  public:
    explicit OSSM(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display,
                  AiEsp32RotaryEncoder &rotaryEncoder);

    std::unique_ptr<sml::sm<OSSMStateMachine, sml::logger<StateLogger>>> sm =
        nullptr;  // The state machine
};

#endif  // OSSM_SOFTWARE_OSSM_H
