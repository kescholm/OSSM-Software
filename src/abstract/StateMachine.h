#ifndef OSSM_SOFTWARE_STATEMACHINE_H
#define OSSM_SOFTWARE_STATEMACHINE_H

#include "DebugLog.h"
#include "services/display.h"

// One function works for all data types.
// This would work even for user defined types
// if operator '>' is overloaded
template <typename StateEnum, typename EventEnum>

/**
 * The StateMachine class is an abstract class that all machines must inherit
 * from.
 *
 * To create a new machine, you'll need to inherit and override all these
 * abstract methods. If you forget to override any of these methods, the
 * compiler will throw an error. That's on purpose, but you didn't mess up.
 *
 *
 */
class StateMachine {
    /**
     * Transition that state if necessary, based on the current event state.
     *
     * */
    virtual void handleEvent() {
        LOG_TRACE(
            "StateMachine::handleEvent: Using the default event handler.");
        // If there's no event to handle, then exit. This is a no-op.
        if (this->event == EventEnum::NONE) {
            return;
        }

        clearEvent();
    };

    /**
     * This is the private loop that you should override.
     * You custom logic should live here.
     * If you have children machines, you should call their `loop()` methods
     * here as well.
     *
     * This is called by the public loop method, after handling events.
     * */
    virtual void loopInternal() {
        LOG_TRACE(
            "StateMachine::loopInternal: Using the default display handler.");
        u8g2.setFont(u8g2_font_helvR08_tf);
        u8g2.setCursor(0, 40);
        u8g2.printf("No display handler implemented.");
    };

  public:
    // Constructor
    StateMachine() = default;

    // Store the current event.
    EventEnum event = EventEnum::NONE;

    // Store the current event.
    StateEnum state = StateEnum::NONE;

    /** The loop method is called repeatedly by the main thread.
     * In general, your custom logic should live in the "loopInternal" method,
     * and call "loop" instead.
     *
     * This ensures that the "handleEvent" method is called as expected.
     *
     * You can, however, override the loop method if you need to.
     */
    virtual void loop() {
        LOG_TRACE(
            "StateMachine::internalLoop: Using the default loop "
            "handler.")
        this->handleEvent();
        this->loopInternal();
    }

    // method to clear that stored event.
    void clearEvent() { this->event = EventEnum::NONE; }
};

#endif  // OSSM_SOFTWARE_STATEMACHINE_H
