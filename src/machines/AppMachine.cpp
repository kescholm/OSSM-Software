#include "AppMachine.h"

#include <Arduino.h>

AppMachine::AppMachine() {}

void AppMachine::setup() {
    // Print a test line
    Serial.println("AppMachine is setting up");
}

void AppMachine::loop() {
    this->handleEvent();
    this->updateDisplay();

    Serial.println("AppMachine is looping");
}

void AppMachine::handleEvent() {
    // If there's no event to handle, then exit. This is a no-op.
    if (this->event == App::Events::NONE) {
        return;
    }

    switch (this->event) {
        case App::Events::NUM_OPTIONS:
            this->state = App::States::NONE;
            break;
        default:
            break;
    }

    // After handling the event, clear it.
    clearEvent();
}

void AppMachine::updateDisplay() {
    // Draw the current state
    switch (this->state) {
        case App::States::NONE:
            break;
        default:
            break;
    }
};
