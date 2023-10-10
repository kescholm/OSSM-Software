#include <DebugLog.h>

#include "Arduino.h"
#include "FastLED.h"
#include "machines/AppMachine.h"
#include "services/display.h"

// Create an instance of the OSSM state machine
AppMachine* appMachine;

void setup() {
    LOG_TRACE("main::setup");

    /** Hardware setup */
    Serial.begin(115200);

    /** Service setup */
    u8g2.begin();

    /** App setup*/
    appMachine = new AppMachine();
    appMachine->setup();
};

void loop() {
    u8g2.clearBuffer();
    FastLED.clear();

    appMachine.loop();

    FastLED.show();
    u8g2.sendBuffer();
};