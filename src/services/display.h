#ifndef OSSM_SOFTWARE_DISPLAY_H
#define OSSM_SOFTWARE_DISPLAY_H
#include <U8g2lib.h>

#include "constants/pins.h"

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,
                                                Pins::Display::oled_reset,
                                                Pins::Remote::display_clock,
                                                Pins::Remote::display_data);

#endif  // OSSM_SOFTWARE_DISPLAY_H
