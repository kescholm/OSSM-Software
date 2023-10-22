#include "OSSM.h"

#include "DebugLog.h"
#include "constants/Config.h"
#include "extensions/u8g2Extensions.h"
#include "utilities/analog.h"

void OSSM::drawMenuTask(void *pvParameters) {
    bool isFirstDraw = true;
    OSSM *ossm = (OSSM *)pvParameters;

    int clicksPerRow = 3;

    ossm->encoder.setBoundaries(0, clicksPerRow * (MenuOption::NUM_OPTIONS)-1,
                                true);
    ossm->encoder.setAcceleration(0);

    ossm->menuOption =
        (MenuOption)floor(ossm->encoder.readEncoder() / clicksPerRow);

    // get the encoder position
    do {
        // Destroy this task if, for some reason, the state is not as expected.
        if (!isFirstDraw && !ossm->sm->is("menu"_s) &&
            !ossm->sm->is("menu.idle"_s)) {
            vTaskDelete(nullptr);
            return;
        }

        if (!isFirstDraw && !ossm->encoder.encoderChanged()) {
            vTaskDelay(1);
            continue;
        }

        isFirstDraw = false;

        ossm->display.clearBuffer();

        // Drawing Variables.
        int leftPadding = 6;  // Padding on the left side of the screen
        int fontSize = 8;
        int itemHeight = 20;   // Height of each item
        int visibleItems = 3;  // Number of items visible on the screen

        auto menuOption =
            (MenuOption)floor(ossm->encoder.readEncoder() / clicksPerRow);
        ossm->menuOption = menuOption;

        drawShape::scroll(100 * ossm->encoder.readEncoder() /
                          (clicksPerRow * MenuOption::NUM_OPTIONS - 1));
        LOG_TRACE("Hovering Over State: " + menuStrings[menuOption]);

        // Loop around to make an infinite menu.
        int lastIdx =
            menuOption - 1 < 0 ? MenuOption::NUM_OPTIONS - 1 : menuOption - 1;
        int nextIdx =
            menuOption + 1 > MenuOption::NUM_OPTIONS - 1 ? 0 : menuOption + 1;

        ossm->display.setFont(Config::Font::base);

        // Draw the previous item
        if (lastIdx >= 0) {
            ossm->display.drawUTF8(leftPadding, itemHeight * (1),
                                   menuStrings[lastIdx].c_str());
        }

        // Draw the next item
        if (nextIdx < MenuOption::NUM_OPTIONS) {
            ossm->display.drawUTF8(leftPadding, itemHeight * (3),
                                   menuStrings[nextIdx].c_str());
        }

        // Draw the current item
        ossm->display.setFont(Config::Font::bold);
        ossm->display.drawUTF8(leftPadding, itemHeight * (2),
                               menuStrings[menuOption].c_str());

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

        vTaskDelay(1);
    } while (true);

    vTaskDelete(nullptr);
}

void OSSM::drawMenu() {
    // Use the handle to delete the task.
    if (displayTask != nullptr) {
        vTaskDelete(displayTask);
    }
    // start the draw menu task
    xTaskCreate(drawMenuTask, "drawMenuTask", 2048, this, 1, &displayTask);
}