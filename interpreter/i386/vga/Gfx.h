#pragma once
#include <stddef.h>
#include <stdint.h>

/**
 * Graphics registers interface. These registers allow to query
 * display information such as color, width, and height.
 */

typedef uint8_t e_VGA_Gfx_Register;
enum {
    SET_RESET = 0,
    ENABLE_SET_RESET,
    COLOR_COMPARE,
    DATA_ROTATE,
    READ_MAP_SELECT,
    GRAPHICS_MODE,
    MISCELLANEOUS_GRAPHICS,
    COLOR_DONT_CARE,
    BIT_MASK
};

/**
 * Specifies the range of memory addresses that is decoded by the VGA
 * hardware and mapped into display memory accesses.
 */
struct e_VGA_Gfx_Memory_Map {
    bool is_color;
    uint8_t* start;
    size_t length;
    size_t lines;
    size_t columns;
};

const e_VGA_Gfx_Memory_Map* e_VGA_Gfx_get_memory_map();
uint8_t e_VGA_Gfx_read(e_VGA_Gfx_Register reg);
void e_VGA_Gfx_write(e_VGA_Gfx_Register reg, uint8_t data);
