#pragma once
#include <stdint.h>

/**
 * @brief CRT controller register interface
 *
 * Defines the interface of the VGA CRT controller register. This register adds
 * timing signals to allow the monitor to display analog color information.
 */

typedef uint8_t e_VGA_CRT_Register;
enum {
    CRT_HORIZONTAL_TOTAL = 0,
    CRT_HORIZONTAL_DISPLAY_END,
    CRT_HORIZONTAL_BLANKING_START,
    CRT_HORIZONTAL_BLANKING_END,
    CRT_HORIZONTAL_RETRACE_START,
    CRT_HORIZONTAL_RETRACE_END,
    CRT_VERTICAL_TOTAL,
    CRT_DISPLAY_OVERFLOW,
    CRT_PRESET_ROW_SCAN,
    CRT_MAXIMUM_SCAN_LINE,
    CRT_CURSOR_START,
    CRT_CURSOR_END,
    CRT_START_ADDRESS_HIGH,
    CRT_START_ADDRESS_LOW,
    CRT_CURSOR_LOCATION_HIGH,
    CRT_CURSOR_LOCATION_LOW,
    CRT_VERTICAL_RETRACE_START,
    CRT_VERTICAL_RETRACE_END,
    CRT_VERTICAL_DISPLAY_END,
    CRT_OFFSET,
    CRT_UNDERLINE_LOCATION,
    CRT_VERTICAL_BLANKING_START,
    CRT_VERTICAL_BLANKING_END,
    CRT_CONTROLLER_MODE_CONTROL,
    CRT_LINE_COMPARE
};

/**
 * Enables or disables color mode.
 *
 * @param [in] enable true to enable or false to disable
 */
void e_VGA_CRT_enable_color_mode(bool enable = true);

/**
 * Enables or disables the cursor when in text mode.
 *
 * @param [in] enable true to enable or false to disable
 */
void e_VGA_CRT_enable_cursor(bool enable = true);

/**
 * Moves the cursor when in text mode.
 *
 * @param [in] row row where to move the cursor to
 * @param [in] column column where to move the cursor to
 */
void e_VGA_CRT_move_cursor(uint32_t row, uint32_t column);

/**
 * Reads a byte from a CRT controller register.
 *
 * @param [in] reg register to read from
 * @return byte read
 */
uint8_t e_VGA_CRT_read(e_VGA_CRT_Register reg);

/**
 * Writes a byte to a CRT controller register.
 *
 * @param [in] reg register to write to
 * @param [in] data byte to write
 */
void e_VGA_CRT_write(e_VGA_CRT_Register reg, uint8_t data);
