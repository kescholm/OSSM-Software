#include <DebugLog.h>

#include "Arduino.h"
#include "machines/OSSM.h"
#include "services/board.h"
#include "services/display.h"

// Create an instance of the OSSM state machine
OSSM *ossm;

// IRAM_ATTR void encoderPushButton() {
////    ossm->sm->process_event(ButtonPress{});
//};

bool handlePress = false;

void IRAM_ATTR encoderPressed() {
    //    LOG_DEBUG("main::encoderPushButton");
    handlePress = true;
}

void setup() {
    LOG_TRACE("main::setup");

    /** Board setup */
    initBoard();

    /** Service setup */
    // Display
    display.begin();

    ossm = new OSSM(display);

    attachInterrupt(digitalPinToInterrupt(Pins::Remote::encoderSwitch),
                    encoderPressed, RISING);
};

void loop() {
    if (handlePress) {
        handlePress = false;
        ossm->sm->process_event(ButtonPress{});
    }
};