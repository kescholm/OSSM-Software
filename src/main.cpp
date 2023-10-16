#include <DebugLog.h>

#include "Arduino.h"
#include "FastLED.h"
#include "machines/OSSM.h"
#include "services/board.h"
#include "services/display.h"
#include "services/stepper.h"

// Create an instance of the OSSM state machine
OSSM *ossm;

void setup() {
    LOG_TRACE("main::setup");

    /** Board setup */
    initBoard();

    /** Service setup */
    // Display
    u8g2.begin();
    // Stepper

    /** OSSM setup - this must be last.
     * Note: All your services and hardware must be initialized before this.
     * */
    ossm = new OSSM();
};

void loop() {
    LOG_TRACE("main::loop");
    u8g2.clearBuffer();
    FastLED.clear();

    // Looking for the main logic? Checkout OSSM::internalLoop() in
    // src/machines/OSSM.cpp
    ossm->loop();

    FastLED.show();
    u8g2.sendBuffer();
};