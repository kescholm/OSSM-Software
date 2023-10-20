#ifndef OSSM_SOFTWARE_OSSM_H
#define OSSM_SOFTWARE_OSSM_H

#include <memory>

#include "ESP_FlexyStepper.h"
#include "Events.h"
#include "U8g2lib.h"
#include "boost/sml.hpp"
#include "utilities/StateLogger.h"

namespace sml = boost::sml;

class OSSM {
  private:
    /****************************************
     ********** OSSM State Machine **********
     ****************************************
     *
     * This is the state machine that controls the OSSM.
     * It's based on the Boost SML library, and you don't need to be an expert
     *to use it, just follow the examples in this table:
     *
     * https://boost-ext.github.io/sml/tutorial.html#:~:text=3.%20Create%20a%20transition%20table
     *
     * Here are the basic rules:
     * 1. Each row in the table is a transition.
     * 2. Each transition has a source state, an event, a guard, an action, and
     *a target state.
     * 3. The source state is the state that the machine must be in for the
     *transition to be valid.
     * 4. (optional) The event is the event that triggers the transition.
     * 5. (optional) The guard is a function that returns true or false. If it
     *returns true, then the transition is valid.
     * 6. (optional) The action is a function that is called when the transition
     *is triggered, it can't block the main thread and cannot return a value.
     * 7. The target state is the state that the machine will be in after the
     *transition is complete.
     *
     * Have fun!
     */
    struct OSSMStateMachine {
        auto operator()() const {
            using namespace sml;
            return make_transition_table(
                // The initial state is "idle"
                *"idle"_s +
                    event<Done> / [](OSSM &owner) { owner.drawHello(); } =
                    "homing"_s,

                // Start Homing
                "homing"_s /
                    [](OSSM &owner) {
                        owner.clearHoming();
                        owner.homing();
                    } = "homing.idle"_s,

                // Wait for the homing task to finish the first pass and listen
                // for a motor failure.
                "homing.idle"_s + event<Error> = "error"_s,
                "homing.idle"_s + event<Done> /
                                      [](OSSM &owner) {
                                          owner.isForward = false;
                                          owner.homing();
                                      } = "homing.backward"_s,

                // Start the second pass of homing.
                // Wait for the homing task to finish the second pass and listen
                // for a motor failure.
                "homing.backward"_s + event<Error> = "error"_s,
                "homing.backward"_s + event<Done>[([](OSSM &owner) {
                    return owner.isStrokeTooShort();
                })] = "error"_s,
                "homing.backward"_s + event<Done> = "menu"_s,

                // TODO: Add a menu state.
                //  Right now the menu state is just the hello world screen, and
                //  on button press this will go back to homing.
                "menu"_s + event<ButtonPress> = "homing"_s,

                // You hit an error. Stop the motor and wait for the button to
                // be pressed.
                "error"_s / [](OSSM &owner) { owner.emergencyStop(); } =
                    "error.idle"_s,
                "error.idle"_s + event<ButtonPress> / [] { ESP.restart(); } =
                    X);
        }
    };

    /****************************************
     ********** Objects and Services ********
     ****************************************
     */
    ESP_FlexyStepper stepper;
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display;
    StateLogger logger;

    /****************************************
     ********** Variables and Flags *********
     ****************************************
     */
    float currentSensorOffset = 0;
    float measuredStrokeMm = 0;
    bool isForward = true;
    String errorMessage = "";

    /****************************************
     ********** Private Functions ***********
     ****************************************
     */
    void clearHoming();
    void drawHello();
    void homing();
    void emergencyStop();
    bool isStrokeTooShort();

    /****************************************
     ********** Static Functions ***********
     ****************************************
     */
    static void homingTask(void *pvParameters);
    static void drawHelloTask(void *pvParameters);

  public:
    explicit OSSM(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display);

    std::unique_ptr<sml::sm<OSSMStateMachine, sml::logger<StateLogger>>> sm =
        nullptr;  // The state machine
};

#endif  // OSSM_SOFTWARE_OSSM_H
