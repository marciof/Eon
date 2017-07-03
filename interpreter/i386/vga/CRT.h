#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * CRT controller register interface. This register adds timing signals
 * to allow the monitor to display analog color information.
 */

typedef uint8_t e_VGA_CRT_Register;
enum {
    E_VGA_CRT_HORIZONTAL_TOTAL = 0,
    E_VGA_CRT_HORIZONTAL_DISPLAY_END,
    E_VGA_CRT_HORIZONTAL_BLANKING_START,
    E_VGA_CRT_HORIZONTAL_BLANKING_END,
    E_VGA_CRT_HORIZONTAL_RETRACE_START,
    E_VGA_CRT_HORIZONTAL_RETRACE_END,
    E_VGA_CRT_VERTICAL_TOTAL,
    E_VGA_CRT_DISPLAY_OVERFLOW,
    E_VGA_CRT_PRESET_ROW_SCAN,
    E_VGA_CRT_MAXIMUM_SCAN_LINE,
    E_VGA_CRT_CURSOR_START,
    E_VGA_CRT_CURSOR_END,
    E_VGA_CRT_START_ADDRESS_HIGH,
    E_VGA_CRT_START_ADDRESS_LOW,
    E_VGA_CRT_CURSOR_LOCATION_HIGH,
    E_VGA_CRT_CURSOR_LOCATION_LOW,
    E_VGA_CRT_VERTICAL_RETRACE_START,
    E_VGA_CRT_VERTICAL_RETRACE_END,
    E_VGA_CRT_VERTICAL_DISPLAY_END,
    E_VGA_CRT_OFFSET,
    E_VGA_CRT_UNDERLINE_LOCATION,
    E_VGA_CRT_VERTICAL_BLANKING_START,
    E_VGA_CRT_VERTICAL_BLANKING_END,
    E_VGA_CRT_CONTROLLER_MODE_CONTROL,
    E_VGA_CRT_LINE_COMPARE,
};

void e_VGA_CRT_enable_color_mode(bool enable);
void e_VGA_CRT_enable_cursor(bool enable);
void e_VGA_CRT_move_cursor(uint32_t line, uint32_t column);
uint8_t e_VGA_CRT_read(e_VGA_CRT_Register reg);
void e_VGA_CRT_write(e_VGA_CRT_Register reg, uint8_t data);
