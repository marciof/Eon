#pragma once
#include <stdint.h>

/**
 * CRT controller register interface. This register adds timing signals
 * to allow the monitor to display analog color information.
 */

typedef uint8_t e_VGA_CRT_Register;
enum {
    VGA_CRT_HORIZONTAL_TOTAL = 0,
    VGA_CRT_HORIZONTAL_DISPLAY_END,
    VGA_CRT_HORIZONTAL_BLANKING_START,
    VGA_CRT_HORIZONTAL_BLANKING_END,
    VGA_CRT_HORIZONTAL_RETRACE_START,
    VGA_CRT_HORIZONTAL_RETRACE_END,
    VGA_CRT_VERTICAL_TOTAL,
    VGA_CRT_DISPLAY_OVERFLOW,
    VGA_CRT_PRESET_ROW_SCAN,
    VGA_CRT_MAXIMUM_SCAN_LINE,
    VGA_CRT_CURSOR_START,
    VGA_CRT_CURSOR_END,
    VGA_CRT_START_ADDRESS_HIGH,
    VGA_CRT_START_ADDRESS_LOW,
    VGA_CRT_CURSOR_LOCATION_HIGH,
    VGA_CRT_CURSOR_LOCATION_LOW,
    VGA_CRT_VERTICAL_RETRACE_START,
    VGA_CRT_VERTICAL_RETRACE_END,
    VGA_CRT_VERTICAL_DISPLAY_END,
    VGA_CRT_OFFSET,
    VGA_CRT_UNDERLINE_LOCATION,
    VGA_CRT_VERTICAL_BLANKING_START,
    VGA_CRT_VERTICAL_BLANKING_END,
    VGA_CRT_CONTROLLER_MODE_CONTROL,
    VGA_CRT_LINE_COMPARE
};

void e_VGA_CRT_enable_color_mode(bool enable = true);
void e_VGA_CRT_enable_cursor(bool enable = true);
void e_VGA_CRT_move_cursor(uint32_t line, uint32_t column);
uint8_t e_VGA_CRT_read(e_VGA_CRT_Register reg);
void e_VGA_CRT_write(e_VGA_CRT_Register reg, uint8_t data);
