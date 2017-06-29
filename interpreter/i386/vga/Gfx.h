#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Graphics registers interface. These registers allow to query
 * display information such as color, width, and height.
 */

typedef uint8_t e_VGA_Gfx_Register;
enum {
    E_VGA_GFX_SET_RESET = 0,
    E_VGA_GFX_ENABLE_SET_RESET,
    E_VGA_GFX_COLOR_COMPARE,
    E_VGA_GFX_DATA_ROTATE,
    E_VGA_GFX_READ_MAP_SELECT,
    E_VGA_GFX_MODE,
    E_VGA_GFX_MISC,
    E_VGA_GFX_COLOR_DONT_CARE,
    E_VGA_GFX_BIT_MASK
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

const struct e_VGA_Gfx_Memory_Map* e_VGA_Gfx_get_memory_map();
uint8_t e_VGA_Gfx_read(e_VGA_Gfx_Register reg);
void e_VGA_Gfx_write(e_VGA_Gfx_Register reg, uint8_t data);
