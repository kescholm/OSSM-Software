#include "OSSM.h"

#include <DebugLog.h>

#include "pages/home/HomePage.h"
#include "services/display.h"

OSSM::OSSM(ESP_FlexyStepper* stepper) {
    LOG_TRACE("OSSM::OSSM")

    this->stepper = stepper;
    this->state = OSSM_NS::States::INITIALIZING;
    this->event = OSSM_NS::Events::NONE;
}

void OSSM::loop() {
    LOG_TRACE("OSSM::loop")

    this->handleEvent();
    this->draw();
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

void OSSM::draw() {
    LOG_TRACE("OSSM::draw")

    // TODO: implement display updates for each state.
    switch (this->state) {
        case OSSM_NS::States::NONE:
        case OSSM_NS::States::INITIALIZING:
            static auto* homePage = new HomePage(this);
            homePage->loop();
            break;
        case OSSM_NS::States::HOMING:
            break;
        default:
            LOG_TRACE("OSSM::draw - State: %u not implemented.", state)
            // set x,y positions as variables
            u8g2.setFont(u8g2_font_helvR08_tf);
            u8g2.setCursor(0, 40);
            u8g2.printf("State: %u not implemented.", state);
            break;
    }
};
