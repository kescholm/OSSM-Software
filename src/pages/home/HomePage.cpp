//
// Created by Andrew Koenig on 2023-10-13.
//

#include "HomePage.h"

#include "DebugLog.h"
#include "services/display.h"

HomePage::HomePage(OSSM *ossm) {
    LOG_DEBUG("HomePage::HomePage");
    this->ossm = ossm;
}

void HomePage::loop() {
    switch (state) {
        case HOME_NS::States::NONE:
            // This should intentionally fall through to the next case.
            state = HOME_NS::States::HOMING;
        case HOME_NS::States::HOMING:
            homing();
            break;
        default:
            u8g2.setFont(u8g2_font_helvR08_tf);
            u8g2.setCursor(0, 40);
            u8g2.printf("You shouldn't be here.");
    }
}

/**
 * If we're in the homing state, then the machine has just been turned on.
 * We will automatically find a suitable play range.
 */
void HomePage::homing() {
    LOG_DEBUG("HomePage::homing");
    // In progress- porting over the homing code from the OSSM HARDWARE project.
}
