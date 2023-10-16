//
// Created by Andrew Koenig on 2023-10-15.
//

#ifndef OSSM_SOFTWARE_U8G2EXTENSIONS_H
#define OSSM_SOFTWARE_U8G2EXTENSIONS_H

#include "services/display.h"

/**
 * This namespace contains functions that extend the functionality of the
 * U8G2 library.
 *
 * Specifically, it contains functions that are used to draw text on the
 * display.
 */
namespace u8g2Str {
    static void centered(int y, const char *str) {
        int x = (u8g2.getDisplayWidth() - u8g2.getStrWidth(str)) / 2;
        u8g2.drawStr(x, y, str);
    }

    /**
     * u8g2E a string, breaking it into multiple lines if necessary.
     * This will attempt to break at "/n" characters, or at spaces if no
     * newlines are found.
     * @param x
     * @param y
     * @param str
     */
    void multiLine(int x, int y, const char *str) {
        // display width in pixels
        int displayWidth = u8g2.getDisplayWidth();
        // string width in pixels
        int stringWidth = 0;
        char glyph[2];
        glyph[1] = 0;
        for (const char *ptr = str, *lastBlank = nullptr; *ptr; ++ptr) {
            while (x == 0 && (*str == ' ' || *str == '\n'))
                // skip blanks and newlines at the left edge of the display
                if (ptr == str++) ++ptr;
            glyph[0] = *ptr;

            // accumulate the pixel width
            stringWidth += u8g2.getStrWidth(glyph);
            // remember where the last blank was found
            if (*ptr == ' ') lastBlank = ptr;

            // non-blanks will be separated by one additional pixel
            else
                ++stringWidth;

            // if we found a newline character, or if we ran past the right edge
            // of the display
            if (*ptr == '\n' || x + stringWidth > displayWidth) {
                int starting_xloc = x;
                // print to just before the last blank, or to just before where
                // we got to
                while (str < (lastBlank ? lastBlank : ptr)) {
                    glyph[0] = *str++;
                    x += u8g2.drawStr(x, y, glyph);
                }
                // account for what we printed
                stringWidth -= x - starting_xloc;

                // advance to the next line
                y += u8g2.getMaxCharHeight();
                x = 0;
                lastBlank = nullptr;
            }
        }
        // print any characters left over
        while (*str) {
            glyph[0] = *str++;
            x += u8g2.drawStr(x, y, glyph);
        }
    }
};

#endif  // OSSM_SOFTWARE_U8G2EXTENSIONS_H
