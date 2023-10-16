#include "OSSM.h"

#include <DebugLog.h>

#include "constants/UserConfig.h"
#include "extensions/u8g2Extensions.h"
#include "pages/home/HomePage.h"
#include "services/display.h"
#include "services/stepper.h"

/**
 * Page definitions.
 *
 * Create pointers here which are initialized in the constructor.
 */
HomePage *homePage;

OSSM::OSSM() {
    LOG_TRACE("OSSM::OSSM")

    this->state = OSSM_NS::States::INITIALIZING;
    this->event = OSSM_NS::Events::NONE;

    errorMessage = nullptr;

    initStepper(stepper);

    homePage = new HomePage(this);
}

void OSSM::handleEvent() {
    LOG_TRACE("OSSM::handleEvent");

    // If there's no event to handle, then exit. This is a no-op.
    if (this->event == OSSM_NS::Events::NONE) {
        LOG_TRACE("OSSM::handleEvent: No event to handle.");
        return;
    }

    // If an error has been encountered, then transition to the ERROR state.
    // And immediately throw the emergency brake.
    if (this->event == OSSM_NS::Events::ERROR) {
        LOG_ERROR(
            "OSSM::handleEvent: An Error event was encountered. Throwing the "
            "emergency brake. Error:",
            this->errorMessage);
        stepper.emergencyStop();
        this->state = OSSM_NS::States::ERROR;
        clearEvent();
        return;
    }

    // TODO: implement event handling.
    switch (this->state) {
        default:
            break;
    }

    // After handling the event, clear it.
    clearEvent();
}

void OSSM::loopInternal() {
    LOG_TRACE("OSSM::loopInternal")

    // TODO: implement display updates for each state.
    switch (this->state) {
        case OSSM_NS::States::NONE:
        case OSSM_NS::States::INITIALIZING:
            homePage->loop();
            break;
        case OSSM_NS::States::ERROR:
            u8g2.setFont(u8g2_font_helvR08_te);
            u8g2.drawUTF8(0, 8, UserConfig::copy.Error);
            u8g2Str::multiLine(0, 16, this->errorMessage);
            break;
        default:
            LOG_TRACE("OSSM::loopInternal - State: %u not implemented.", state)
            // set x,y positions as variables
            u8g2.setFont(u8g2_font_helvR08_te);
            u8g2.setCursor(0, 40);
            u8g2.printf(UserConfig::copy.StateNotImplemented, state);
            break;
    }
}

/**
 * Set the error message and transition to the ERROR state.
 *
 * @param message
 */
void OSSM::setError(const char *message) {
    LOG_TRACE("OSSM::setError")

    this->errorMessage = message;
    this->event = OSSM_NS::Events::ERROR;
};
