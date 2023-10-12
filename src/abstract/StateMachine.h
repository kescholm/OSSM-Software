#ifndef OSSM_SOFTWARE_STATEMACHINE_H
#define OSSM_SOFTWARE_STATEMACHINE_H

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
    // The setup method is called once at the beginning of the program
    virtual void setup() = 0;

    /** the loop method is called repeatedly by the main thread.
     This loop must call the loop method of any children machines.

     Here's an example of what a loop method might look like:

     // YourMachine.h
     void loop override();

     // YourMachine.cpp
     void OSSM::loop() {

        childMachine.loop();

        this->handleEvent();
        this->updateDisplay();
     }
     */
    virtual void loop() = 0;

    /**
     * Transition that state if necessary, based on the current event state.
     *
     * */
    virtual void handleEvent() = 0;

    /**
     * Transition that state if necessary, based on the current event state.
     *
     * */
    virtual void updateDisplay() = 0;

  public:
    // Constructor
    StateMachine() = default;

    // Store the current event.
    EventEnum event = EventEnum::NONE;

    // Store the current event.
    StateEnum state = StateEnum::NONE;

    // method to clear that stored event.
    void clearEvent() { this->event = EventEnum::NONE; }
};

#endif  // OSSM_SOFTWARE_STATEMACHINE_H
