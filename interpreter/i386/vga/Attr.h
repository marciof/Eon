#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * Attribute controller register interface. This register formats the
 * pixel color information such that the pixel values can be submitted
 * to the DAC (Digital to Analog Converter).
 */

typedef uint8_t k_VGA_Attr_Register;
enum {
    /** There are 16 consecutive palette registers. */
    K_VGA_ATTR_PALETTES = 0,
    K_VGA_ATTR_MODE_CONTROL = 16,
    K_VGA_ATTR_OVERSCAN_COLOR,
    K_VGA_ATTR_COLOR_PLANE_ENABLE,
    K_VGA_ATTR_HORIZONTAL_PIXEL_PANNING,
    K_VGA_ATTR_COLOR_SELECT,
};

void k_VGA_Attr_enable_text_blink_mode(bool enable);
void k_VGA_Attr_enable_gfx_mode(bool enable);
uint8_t k_VGA_Attr_read(k_VGA_Attr_Register reg);
void k_VGA_Attr_write(k_VGA_Attr_Register reg, uint8_t data);
