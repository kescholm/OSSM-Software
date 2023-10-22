#ifndef OSSM_SOFTWARE_BOARD_H
#define OSSM_SOFTWARE_BOARD_H

#include <Arduino.h>

#include "constants/Pins.h"

void drawWelcome(void *pvParameters) {
    static int count = 0;
    while (!Serial && count++ < 10) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    // Print a few empty lines to separate the ASCII art from the boot messages
    Serial.println();
    Serial.println();

    // ASCII art stored as a multi-line string literal. Note the use of \n for
    // new lines
    Serial.println(
        F("  ██████╗ ███████╗███████╗███╗   ███╗\n"
          " ██╔═══██╗██╔════╝██╔════╝████╗ ████║\n"
          " ██║   ██║███████╗███████╗██╔████╔██║\n"
          " ██║   ██║╚════██║╚════██║██║╚██╔╝██║\n"
          " ╚██████╔╝███████║███████║██║ ╚═╝ ██║\n"
          "  ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝"));

    // Print a few empty lines to separate the ASCII art from the boot messages
    Serial.println();
    Serial.println();

    vTaskDelete(nullptr);
}

/**
 * This file changes the configuration of the board.
 */
void initBoard() {
    Serial.begin(115200);

    pinMode(Pins::Remote::encoderSwitch,
            INPUT_PULLDOWN);  // Rotary Encoder Pushbutton

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

    //    xTaskCreate(drawWelcome, "drawWelcome", 2048, nullptr, 1, nullptr);
}

#endif  // OSSM_SOFTWARE_BOARD_H
