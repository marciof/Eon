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

/**
 * Enables or disables blink mode when in text mode.
 *
 * @param [in] enable true to enable or false to disable
 * @note The text mode must be initialized.
 */
void k_VGA_Attr_enable_text_blink_mode(bool enable);

/**
 * Enables or disables graphics mode.
 *
 * @param [in] enable true to enable or false to disable
 * @note The text mode must be initialized.
 */
void k_VGA_Attr_enable_gfx_mode(bool enable);

/**
 * Reads a byte from an attribute controller register.
 *
 * @param [in] reg register to read from
 * @return byte read
 * @note The text mode must be initialized.
 */
uint8_t k_VGA_Attr_read(k_VGA_Attr_Register reg);

/**
 * Writes a byte to an attribute controller register.
 *
 * @param [in] reg register to write to
 * @param [in] data byte to write
 * @note The text mode must be initialized.
 */
void k_VGA_Attr_write(k_VGA_Attr_Register reg, uint8_t data);
