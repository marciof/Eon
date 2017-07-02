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
    E_VGA_TEXT_BLACK = 0,
    E_VGA_TEXT_BLUE,
    E_VGA_TEXT_GREEN,
    E_VGA_TEXT_CYAN,
    E_VGA_TEXT_RED,
    E_VGA_TEXT_MAGENTA,
    E_VGA_TEXT_BROWN,
    E_VGA_TEXT_LIGHT_GRAY,

    // Brighter/Blinking color set.
    E_VGA_TEXT_DARK_GRAY = (E_VGA_TEXT_BLACK | E_BIT(3)),
    E_VGA_TEXT_LIGHT_BLUE = (E_VGA_TEXT_BLUE | E_BIT(3)),
    E_VGA_TEXT_LIGHT_GREEN = (E_VGA_TEXT_GREEN | E_BIT(3)),
    E_VGA_TEXT_LIGHT_CYAN = (E_VGA_TEXT_CYAN | E_BIT(3)),
    E_VGA_TEXT_LIGHT_RED = (E_VGA_TEXT_RED | E_BIT(3)),
    E_VGA_TEXT_LIGHT_MAGENTA = (E_VGA_TEXT_MAGENTA | E_BIT(3)),
    E_VGA_TEXT_YELLOW = (E_VGA_TEXT_BROWN | E_BIT(3)),
    E_VGA_TEXT_WHITE = (E_VGA_TEXT_LIGHT_GRAY | E_BIT(3))
};

size_t e_VGA_Text_get_columns();
size_t e_VGA_Text_get_lines();

void e_VGA_Text_init();

void e_VGA_Text_print_ch(char ch);
void e_VGA_Text_print_str(const char* string);

void e_VGA_Text_set_color(
    e_VGA_Text_Color foreground,
    e_VGA_Text_Color background);
