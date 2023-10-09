#include "Arduino.h"
#include "machines/AppMachine.h"
#include "services/display.h"

// Create an instance of the OSSM state machine
AppMachine appMachine = AppMachine();

void setup() {
    Serial.begin(115200);

    appMachine.setup();

    // Start Services
    u8g2.begin();
};

void loop() { appMachine.loop(); };