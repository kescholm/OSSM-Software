#include "OSSM.h"

#include <DebugLog.h>

#include "services/display.h"

OSSM::OSSM() = default;

void OSSM::setup() { LOG_TRACE("OSSM::setup") }

void OSSM::loop() {
    LOG_TRACE("OSSM::loop")

    this->handleEvent();
    this->updateDisplay();
}

void OSSM::handleEvent() {
    LOG_TRACE("OSSM::handleEvent")

    // If there's no event to handle, then exit. This is a no-op.
    if (this->event == OSSM_NS::Events::NONE) {
        LOG_TRACE("OSSM::handleEvent: No event to handle.")

        return;
    }

    // TODO: implement event handling.
    switch (this->event) {
        default:
            break;
    }

    // After handling the event, clear it.
    clearEvent();
}

void OSSM::updateDisplay() {
    LOG_TRACE("OSSM::updateDisplay")

    // TODO: implement display updates for each state.
    switch (this->state) {
        default:
            LOG_TRACE("OSSM::updateDisplay - State: %u not implemented.", state)
            // set x,y positions as variables
            u8g2.setFont(u8g2_font_helvR08_tf);
            u8g2.setCursor(0, 40);
            u8g2.printf("State: %u not implemented.", state);
            break;
    }
};
