#include <DebugLog.h>

#include "Arduino.h"
#include "FastLED.h"
#include "machines/OSSM.h"
#include "services/display.h"

// Create an instance of the OSSM state machine
OSSM* ossm;

void setup() {
    LOG_TRACE("main::setup");

    /** Hardware setup */
    Serial.begin(115200);

    /** Service setup */
    u8g2.begin();

    /** OSSM setup - this must be last.*/
    ossm = new OSSM();
    ossm->setup();
};

void loop() {
    LOG_TRACE("main::loop");
    u8g2.clearBuffer();
    FastLED.clear();

    ossm->loop();

    FastLED.show();
    u8g2.sendBuffer();
};