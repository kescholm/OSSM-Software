#include "OSSM.h"

#include "DebugLog.h"

enum MenuOption { Train, Settings, OPTION_3, OPTION_4, OPTION_5, NUM_OPTIONS };

String menuStrings[MenuOption::NUM_OPTIONS] = {"Train", "Settings", "Option 3",
                                               "Option 4", "Option 5"};

[[noreturn]] void OSSM::drawMenuTask(void *pvParameters) {
    OSSM *ossm = (OSSM *)pvParameters;

    // get the encoder position
    do {
        int position = abs(ossm->encoder.read() % 100);

        LOG_DEBUG("Encoder Position: " + String(ossm->encoder.read()));

        float sizeOfItem = 100.0 / MenuOption::NUM_OPTIONS;

        ossm->display.clearBuffer();

        // Drawing Variables.
        int leftPadding = 28;  // Padding on the left side of the screen
        int fontSize = 8;
        int itemHeight = 20;   // Height of each item
        int visibleItems = 3;  // Number of items visible on the screen

        auto targetIdx =
            static_cast<MenuOption>((int)floor((float)position / sizeOfItem));

        int lastIdx =
            targetIdx - 1 < 0 ? MenuOption::NUM_OPTIONS - 1 : targetIdx - 1;
        int nextIdx =
            targetIdx + 1 > MenuOption::NUM_OPTIONS - 1 ? 0 : targetIdx + 1;

        // Draw the previous item
        if (lastIdx >= 0) {
            ossm->display.setFont(u8g2_font_helvR08_tf);
            ossm->display.drawStr(leftPadding, itemHeight * (1),
                                  menuStrings[lastIdx].c_str());
        }

        // Draw the next item
        if (nextIdx < MenuOption::NUM_OPTIONS) {
            ossm->display.setFont(u8g2_font_helvR08_tf);
            ossm->display.drawStr(leftPadding, itemHeight * (3),
                                  menuStrings[nextIdx].c_str());
        }

        // Draw the current item
        ossm->display.setFont(u8g2_font_helvB08_tf);
        ossm->display.drawStr(leftPadding, itemHeight * (2),
                              menuStrings[targetIdx].c_str());

        // Draw a rounded rectangle around the center item
        ossm->display.drawRFrame(
            0, itemHeight * (visibleItems / 2) - (fontSize - itemHeight) / 2,
            120, itemHeight, 2);

        // Draw Shadow.
        ossm->display.drawLine(2, 2 + fontSize / 2 + 2 * itemHeight, 119,
                               2 + fontSize / 2 + 2 * itemHeight);
        ossm->display.drawLine(120, 4 + fontSize / 2 + itemHeight, 120,
                               1 + fontSize / 2 + 2 * itemHeight);

        ossm->display.sendBuffer();

        // 100 ms
        vTaskDelay(100 / portTICK_PERIOD_MS);

    } while (true);

    vTaskDelete(nullptr);
}

void OSSM::drawMenu() {
    // start the draw menu task
    xTaskCreate(drawMenuTask, "drawMenuTask", 2048, this, 1, nullptr);
}