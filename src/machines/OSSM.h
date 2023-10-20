#ifndef OSSM_SOFTWARE_OSSMSERVICE_H
#define OSSM_SOFTWARE_OSSMSERVICE_H

#include <memory>

#include "ESP_FlexyStepper.h"
#include "Events.h"
#include "OSSMStatesEvents.h"
#include "StateLogger.h"
#include "U8g2lib.h"
#include "boost/sml.hpp"

namespace sml = boost::sml;
using namespace sml;

class OSSM {
  public:
    explicit OSSM(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display);

    ESP_FlexyStepper stepper;
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display;
    OSSM_StateLogger logger;

    void drawHello();  // The action to be called from the state machine

    // State transition table struct
    struct OSSMStateMachine {
        auto operator()() const {
            return make_transition_table(
                *"idle"_s / [](OSSM &owner) { owner.drawHello(); } =
                    "running"_s,
                "running"_s + event<ButtonPress> /
                                  [](OSSM &owner) { owner.drawHello(); } =
                    "idle"_s);
        }
    };

    std::unique_ptr<sml::sm<OSSMStateMachine, sml::logger<OSSM_StateLogger>>>
        sm;  // The state machine
    // Using unique_ptr to manage the state machine's lifetime
};

#endif  // OSSM_SOFTWARE_OSSMSERVICE_H
