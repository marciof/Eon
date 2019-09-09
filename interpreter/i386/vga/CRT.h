/**
 * CRT controller register interface. This register adds timing signals
 * to allow the monitor to display analog color information.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t k_VGA_CRT_Register;
enum {
    K_VGA_CRT_HORIZONTAL_TOTAL = 0,
    K_VGA_CRT_HORIZONTAL_DISPLAY_END,
    K_VGA_CRT_HORIZONTAL_BLANKING_START,
    K_VGA_CRT_HORIZONTAL_BLANKING_END,
    K_VGA_CRT_HORIZONTAL_RETRACE_START,
    K_VGA_CRT_HORIZONTAL_RETRACE_END,
    K_VGA_CRT_VERTICAL_TOTAL,
    K_VGA_CRT_DISPLAY_OVERFLOW,
    K_VGA_CRT_PRESET_ROW_SCAN,
    K_VGA_CRT_MAXIMUM_SCAN_LINE,
    K_VGA_CRT_CURSOR_START,
    K_VGA_CRT_CURSOR_END,
    K_VGA_CRT_START_ADDRESS_HIGH,
    K_VGA_CRT_START_ADDRESS_LOW,
    K_VGA_CRT_CURSOR_LOCATION_HIGH,
    K_VGA_CRT_CURSOR_LOCATION_LOW,
    K_VGA_CRT_VERTICAL_RETRACE_START,
    K_VGA_CRT_VERTICAL_RETRACE_END,
    K_VGA_CRT_VERTICAL_DISPLAY_END,
    K_VGA_CRT_OFFSET,
    K_VGA_CRT_UNDERLINE_LOCATION,
    K_VGA_CRT_VERTICAL_BLANKING_START,
    K_VGA_CRT_VERTICAL_BLANKING_END,
    K_VGA_CRT_CONTROLLER_MODE_CONTROL,
    K_VGA_CRT_LINE_COMPARE,
};

void k_VGA_CRT_enable_color_mode(bool enable);
void k_VGA_CRT_enable_cursor(bool enable);
void k_VGA_CRT_move_cursor(uint32_t line, uint32_t column);
uint8_t k_VGA_CRT_read(k_VGA_CRT_Register reg);
void k_VGA_CRT_write(k_VGA_CRT_Register reg, uint8_t data);
