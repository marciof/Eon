/**
 * Graphics registers interface. These registers allow to query
 * display information such as color, width, and height.
 */

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t k_VGA_Gfx_Register;
enum {
    K_VGA_GFX_SET_RESET = 0,
    K_VGA_GFX_ENABLE_SET_RESET,
    K_VGA_GFX_COLOR_COMPARE,
    K_VGA_GFX_DATA_ROTATE,
    K_VGA_GFX_READ_MAP_SELECT,
    K_VGA_GFX_MODE,
    K_VGA_GFX_MISC,
    K_VGA_GFX_COLOR_DONT_CARE,
    K_VGA_GFX_BIT_MASK,
};

/**
 * Specifies the range of memory addresses that is decoded by the VGA
 * hardware and mapped into display memory accesses.
 */
struct k_VGA_Gfx_Memory_Map {
    bool is_color;
    uint8_t* start;
    size_t length;
    size_t lines;
    size_t columns;
};

const struct k_VGA_Gfx_Memory_Map* k_VGA_Gfx_get_memory_map(void);
uint8_t k_VGA_Gfx_read(k_VGA_Gfx_Register reg);
void k_VGA_Gfx_write(k_VGA_Gfx_Register reg, uint8_t data);
