#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../Bit.h"

/**
 * @see http://www.osdever.net/FreeVGA/home.htm
 * @see http://www.acid.org/info/xbin/x_tut.htm
 */

typedef uint8_t e_VGA_Text_Color;
enum {
    // Normal color set.
    TEXT_BLACK = 0,
    TEXT_BLUE,
    TEXT_GREEN,
    TEXT_CYAN,
    TEXT_RED,
    TEXT_MAGENTA,
    TEXT_BROWN,
    TEXT_LIGHT_GRAY,

    // Brighter/Blinking color set.
    TEXT_DARK_GRAY = E_BIT_SET(TEXT_BLACK, 3),
    TEXT_LIGHT_BLUE = E_BIT_SET(TEXT_BLUE, 3),
    TEXT_LIGHT_GREEN = E_BIT_SET(TEXT_GREEN, 3),
    TEXT_LIGHT_CYAN = E_BIT_SET(TEXT_CYAN, 3),
    TEXT_LIGHT_RED = E_BIT_SET(TEXT_RED, 3),
    TEXT_LIGHT_MAGENTA = E_BIT_SET(TEXT_MAGENTA, 3),
    TEXT_YELLOW = E_BIT_SET(TEXT_BROWN, 3),
    TEXT_WHITE = E_BIT_SET(TEXT_LIGHT_GRAY, 3)
};

size_t e_VGA_Text_get_columns();
size_t e_VGA_Text_get_rows();
void e_VGA_Text_init();
void e_VGA_Text_print(char ch);
void e_VGA_Text_print(const char* string);
void e_VGA_Text_set_color(
    e_VGA_Text_Color foreground = TEXT_LIGHT_GRAY,
    e_VGA_Text_Color background = TEXT_BLACK);
