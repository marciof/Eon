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
    VGA_TEXT_BLACK = 0,
    VGA_TEXT_BLUE,
    VGA_TEXT_GREEN,
    VGA_TEXT_CYAN,
    VGA_TEXT_RED,
    VGA_TEXT_MAGENTA,
    VGA_TEXT_BROWN,
    VGA_TEXT_LIGHT_GRAY,

    // Brighter/Blinking color set.
    VGA_TEXT_DARK_GRAY = E_BIT_SET(VGA_TEXT_BLACK, 3),
    VGA_TEXT_LIGHT_BLUE = E_BIT_SET(VGA_TEXT_BLUE, 3),
    VGA_TEXT_LIGHT_GREEN = E_BIT_SET(VGA_TEXT_GREEN, 3),
    VGA_TEXT_LIGHT_CYAN = E_BIT_SET(VGA_TEXT_CYAN, 3),
    VGA_TEXT_LIGHT_RED = E_BIT_SET(VGA_TEXT_RED, 3),
    VGA_TEXT_LIGHT_MAGENTA = E_BIT_SET(VGA_TEXT_MAGENTA, 3),
    VGA_TEXT_YELLOW = E_BIT_SET(VGA_TEXT_BROWN, 3),
    VGA_TEXT_WHITE = E_BIT_SET(VGA_TEXT_LIGHT_GRAY, 3)
};

size_t e_VGA_Text_get_columns();
size_t e_VGA_Text_get_lines();

void e_VGA_Text_init();

void e_VGA_Text_print(char ch);
void e_VGA_Text_print(const char* string);

void e_VGA_Text_set_color(
    e_VGA_Text_Color foreground = VGA_TEXT_LIGHT_GRAY,
    e_VGA_Text_Color background = VGA_TEXT_BLACK);
