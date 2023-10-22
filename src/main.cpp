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

bool handlePress = false;
// Counter to detect rage clicks
unsigned int lastPress = 0;

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
    if (handlePress) {
        lastPress = millis();
        handlePress = false;
        ossm->sm->process_event(ButtonPress{});
    }
};