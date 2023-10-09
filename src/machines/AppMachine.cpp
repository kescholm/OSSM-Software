#include "AppMachine.h"

#include <DebugLog.h>

#include "services/display.h"

AppMachine::AppMachine() { LOG_TRACE("AppMachine::AppMachine") }

void AppMachine::setup() { LOG_TRACE("AppMachine::setup") }

void AppMachine::loop() {
    LOG_TRACE("AppMachine::loop")

    this->handleEvent();
    this->updateDisplay();
}

void AppMachine::handleEvent() {
    LOG_TRACE("AppMachine::handleEvent")

    // If there's no event to handle, then exit. This is a no-op.
    if (this->event == App::Events::NONE) {
        LOG_TRACE("AppMachine::handleEvent: No event to handle.")

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

void AppMachine::updateDisplay() {
    LOG_TRACE("AppMachine::updateDisplay")

    // TODO: implement display updates for each state.
    switch (this->state) {
        default:
            u8g2.setFont(u8g2_font_helvR08_tf);
            u8g2.setCursor(0, 40);
            u8g2.printf("State: %u not implemented.", state);
            break;
    }
};
