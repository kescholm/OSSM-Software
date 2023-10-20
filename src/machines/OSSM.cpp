#include "OSSM.h"

#include <DebugLog.h>

#include "extensions/u8g2Extensions.h"
#include "services/stepper.h"

namespace sml = boost::sml;
using namespace sml;

// Now we can define the OSSM constructor since OSSMStateMachine::operator() is
// fully defined
OSSM::OSSM(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &display)
    : sm(std::make_unique<sml::sm<OSSMStateMachine, sml::logger<StateLogger>>>(
          logger, *this)),
      display(display) {
    LOG_TRACE("OSSM::OSSM");

    initStepper(stepper);

    // All initializations are done, so start the state machine.
    sm->process_event(Done{});
}

void OSSM::drawHello() {
    display.clearBuffer();
    // get the current state as a string
    u8g2Str::title("Hello World!");
    display.sendBuffer();
}
