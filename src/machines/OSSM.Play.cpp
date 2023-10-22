
#include "OSSM.h"

#include "extensions/u8g2Extensions.h"

void OSSM::drawPlay() {
    display.clearBuffer();
    drawStr::title("Play");
    display.sendBuffer();
}
