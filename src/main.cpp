#include <DebugLog.h>

#include "Arduino.h"
#include "machines/OSSM.h"
#include "services/board.h"
#include "services/display.h"

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