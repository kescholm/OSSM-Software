#ifndef OSSM_SOFTWARE_ANALOG_H
#define OSSM_SOFTWARE_ANALOG_H

#include <esp32-hal-adc.h>

#include "constants/Pins.h"

// public static function to get the analog value of a pin
static float getAnalogAveragePercent(Pins::Driver pinNumber, int samples) {
    int sum = 0;
    float average = 0;
    float percentage = 0;

    for (int i = 0; i < samples; i++) {
        // TODO: Possibly use fancier filters?
        sum += analogRead((int)pinNumber);
    }
    average = (float)sum / (float)samples;
    // TODO: Might want to add a deadband
    percentage = 100.0f * average / 4096.0f;  // 12 bit resolution
    return percentage;
}

#endif  // OSSM_SOFTWARE_ANALOG_H
