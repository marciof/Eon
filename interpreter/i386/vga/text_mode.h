#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../bit.h"


/**
 * @see http://www.osdever.net/FreeVGA/home.htm
 * @see http://www.acid.org/info/xbin/x_tut.htm
 */


namespace eon {
namespace i386 {
namespace vga {
namespace text_mode {

    typedef uint8_t Color;
    enum {
        // Normal color set.
        BLACK = 0,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHT_GRAY,

        // Brighter/Blinking color set.
        DARK_GRAY = BIT_SET(BLACK, 3),
        LIGHT_BLUE = BIT_SET(BLUE, 3),
        LIGHT_GREEN = BIT_SET(GREEN, 3),
        LIGHT_CYAN = BIT_SET(CYAN, 3),
        LIGHT_RED = BIT_SET(RED, 3),
        LIGHT_MAGENTA = BIT_SET(MAGENTA, 3),
        YELLOW = BIT_SET(BROWN, 3),
        WHITE = BIT_SET(LIGHT_GRAY, 3)
    };


    size_t get_columns();
    size_t get_rows();
    void initialize();
    void print(char ch);
    void print(const char* string);
    void set_color(Color foreground = LIGHT_GRAY, Color background = BLACK);
}}}}
