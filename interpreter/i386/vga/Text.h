#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../Bit.h"

/**
 * @see http://www.osdever.net/FreeVGA/home.htm
 * @see http://www.acid.org/info/xbin/x_tut.htm
 */

typedef uint8_t k_VGA_Text_Color;
enum {
    // Normal color set.
    K_VGA_TEXT_BLACK = 0,
    K_VGA_TEXT_BLUE,
    K_VGA_TEXT_GREEN,
    K_VGA_TEXT_CYAN,
    K_VGA_TEXT_RED,
    K_VGA_TEXT_MAGENTA,
    K_VGA_TEXT_BROWN,
    K_VGA_TEXT_LIGHT_GRAY,

    // Brighter/Blinking color set.
    K_VGA_TEXT_DARK_GRAY = (K_VGA_TEXT_BLACK | K_BIT(3)),
    K_VGA_TEXT_LIGHT_BLUE = (K_VGA_TEXT_BLUE | K_BIT(3)),
    K_VGA_TEXT_LIGHT_GREEN = (K_VGA_TEXT_GREEN | K_BIT(3)),
    K_VGA_TEXT_LIGHT_CYAN = (K_VGA_TEXT_CYAN | K_BIT(3)),
    K_VGA_TEXT_LIGHT_RED = (K_VGA_TEXT_RED | K_BIT(3)),
    K_VGA_TEXT_LIGHT_MAGENTA = (K_VGA_TEXT_MAGENTA | K_BIT(3)),
    K_VGA_TEXT_YELLOW = (K_VGA_TEXT_BROWN | K_BIT(3)),
    K_VGA_TEXT_WHITE = (K_VGA_TEXT_LIGHT_GRAY | K_BIT(3)),
};

size_t k_VGA_Text_get_columns();
size_t k_VGA_Text_get_lines();

void k_VGA_Text_init();

void k_VGA_Text_print_ch(char ch);
void k_VGA_Text_print_str(const char* string);

void k_VGA_Text_set_color(
    k_VGA_Text_Color foreground,
    k_VGA_Text_Color background);
