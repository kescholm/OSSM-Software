#include <DebugLog.h>

#include "Arduino.h"
#include "machines/Events.h"
#include "machines/OSSM.h"
#include "services/board.h"
#include "services/display.h"
#include "services/encoder.h"

/*
 *  ██████╗ ███████╗███████╗███╗   ███╗
 * ██╔═══██╗██╔════╝██╔════╝████╗ ████║
 * ██║   ██║███████╗███████╗██╔████╔██║
 * ██║   ██║╚════██║╚════██║██║╚██╔╝██║
 * ╚██████╔╝███████║███████║██║ ╚═╝ ██║
 *  ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝
 *
 * Welcome to the open source sex machine!
 * This is a product of Kinky Makers and is licensed under the MIT license.
 *
 * Research and Desire is a financial sponsor of this project.
 *
 * But our biggest sponsor is you! If you want to support this project, please
 * contribute, fork, branch and share!
 */

OSSM *ossm;

// TODO: Move this to a service
bool handlePress = false;
int counter = 0;
bool isDouble = false;
long lastPressed = 0;

void IRAM_ATTR encoderPressed() { handlePress = true; }

void setup() {
    LOG_TRACE("main::setup");

    /** Board setup */
    initBoard();

    /** Service setup */
    // Encoder
    initEncoder();
    // Display
    display.begin();

    ossm = new OSSM(display, encoder);

    attachInterrupt(digitalPinToInterrupt(Pins::Remote::encoderSwitch),
                    encoderPressed, RISING);
};

void loop() {
    // TODO: Relocate this code.
    if (handlePress) {
        handlePress = false;

        // detect if a double click occurred
        if (millis() - lastPressed < 300) {
            isDouble = true;
        } else {
            isDouble = false;
        }
        lastPressed = millis();

        LOG_DEBUG("BUTTON PRESS, but was it double? ENCODER ", isDouble);

        ossm->sm->process_event(ButtonPress{.isDouble = isDouble});
    }

    // Print the status of the operationTask handler from FREERTOS
    if (operationTask != nullptr) {
        LOG_DEBUG("operationTask: " + String(eTaskGetState(operationTask)));
    }
};