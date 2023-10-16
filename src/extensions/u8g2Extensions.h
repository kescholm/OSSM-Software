//
// Created by Andrew Koenig on 2023-10-15.
//

#ifndef OSSM_SOFTWARE_U8G2EXTENSIONS_H
#define OSSM_SOFTWARE_U8G2EXTENSIONS_H

#include "services/display.h"

int getUTF8CharLength(const char c) {
    if ((c & 0x80) == 0)
        return 1;  // ASCII
    else if ((c & 0xE0) == 0xC0)
        return 2;  // 2-byte UTF8
    else if ((c & 0xF0) == 0xE0)
        return 3;  // 3-byte UTF8
    else if ((c & 0xF8) == 0xF0)
        return 4;  // 4-byte UTF8
    return 1;      // default to 1 byte for unexpected scenarios
}

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
        u8g2.drawUTF8(x, y, str);
    }

    /**
     * u8g2E a string, breaking it into multiple lines if necessary.
     * This will attempt to break at "/n" characters, or at spaces if no
     * newlines are found.
     * @param x
     * @param y
     * @param str
     */
    void multiLine(int x, int y, const char *str, int lineHeight = 12) {
        int displayWidth = u8g2.getDisplayWidth();
        int stringWidth = 0;
        char glyph[5] = {
            0};  // max UTF-8 glyph length is 4 bytes + 1 for null terminator
        for (const char *ptr = str, *lastBlank = nullptr; *ptr;) {
            while (x == 0 && (*str == ' ' || *str == '\n')) {
                if (ptr == str++) ++ptr;
            }

            int charLength = getUTF8CharLength(*ptr);
            strncpy(glyph, ptr, charLength);
            glyph[charLength] = 0;  // Ensure null-terminated

            ptr += charLength;  // Move pointer by character length

            stringWidth += u8g2.getStrWidth(glyph);
            if (*glyph == ' ')
                lastBlank = ptr - charLength;
            else
                ++stringWidth;

            if (*glyph == '\n' || x + stringWidth > displayWidth) {
                int starting_xloc = x;
                while (str < (lastBlank ? lastBlank : ptr)) {
                    charLength = getUTF8CharLength(*str);
                    strncpy(glyph, str, charLength);
                    glyph[charLength] = 0;  // Ensure null-terminated
                    x += u8g2.drawUTF8(x, y, glyph);
                    str += charLength;
                }
                stringWidth -= x - starting_xloc;
                y += lineHeight;
                x = 0;
                lastBlank = nullptr;
            }
        }
        while (*str) {
            int charLength = getUTF8CharLength(*str);
            strncpy(glyph, str, charLength);
            glyph[charLength] = 0;  // Ensure null-terminated
            x += u8g2.drawUTF8(x, y, glyph);
            str += charLength;
        }
    }
};

#endif  // OSSM_SOFTWARE_U8G2EXTENSIONS_H
