#ifndef OSSM_SOFTWARE_HEADERBAR_H
#define OSSM_SOFTWARE_HEADERBAR_H

#include "services/display.h"

class HeaderBar {
    static void updateFPS() {
        static int lastTime = 0;
        static int frames = 0;
        static int fps = 0;

        frames++;

        // update FPS
        if (millis() - lastTime >= 1000) {
            fps = frames;
            frames = 0;
            lastTime = millis();
        }

        u8g2.setFont(u8g2_font_4x6_tf);
        u8g2.setCursor(0, 6);
        u8g2.print(fps);
    }

  public:
    static void loop() { updateFPS(); }

    // constructor
    HeaderBar() = default;
};

#endif  // OSSM_SOFTWARE_HEADERBAR_H
