#include <DebugLog.h>

#include "Arduino.h"
#include "FastLED.h"
#include "machines/OSSM.h"
#include "services/display.h"
#include "services/stepper.h"

// Create an instance of the OSSM state machine
OSSM *ossm;
ESP_FlexyStepper *stepper;

void setup() {
    LOG_TRACE("main::setup");

    /** Board setup */
    Serial.begin(115200);
    pinMode(Pins::Driver::motorEnablePin, OUTPUT);
    pinMode(Pins::Wifi::resetPin, INPUT_PULLDOWN);
    // TODO: Remove wifi toggle pin
    //    pinMode(Pins::Wifi::controlTogglePin, LOCAL_CONTROLLER); // choose
    //    between WIFI_CONTROLLER and LOCAL_CONTROLLER
    // Set analog pots (control knobs)
    pinMode(Pins::Remote::speedPotPin, INPUT);
    adcAttachPin(Pins::Remote::speedPotPin);

    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);  // allows us to read almost full 3.3V range

    /** Service setup */
    // Display
    u8g2.begin();
    // Stepper motor
    initStepper(stepper);

    /** OSSM setup - this must be last.
     * Note: All your services and hardware must be initialized before this.
     * */
    ossm = new OSSM(stepper);
};

void loop() {
    LOG_TRACE("main::internalLoop");
    u8g2.clearBuffer();
    FastLED.clear();

    ossm->internalLoop();

    FastLED.show();
    u8g2.sendBuffer();
};