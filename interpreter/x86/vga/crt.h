#pragma once
#include <stdint.h>

/**
 * @brief CRT controller register interface
 *
 * Defines the interface of the VGA CRT controller register. This register adds
 * timing signals to allow the monitor to display analog color information.
 */


namespace eon {
namespace x86 {
namespace vga {
namespace crt {
    typedef uint8_t Register;
    enum {
        HORIZONTAL_TOTAL = 0,
        HORIZONTAL_DISPLAY_END,
        HORIZONTAL_BLANKING_START,
        HORIZONTAL_BLANKING_END,
        HORIZONTAL_RETRACE_START,
        HORIZONTAL_RETRACE_END,
        VERTICAL_TOTAL,
        DISPLAY_OVERFLOW,
        PRESET_ROW_SCAN,
        MAXIMUM_SCAN_LINE,
        CURSOR_START,
        CURSOR_END,
        START_ADDRESS_HIGH,
        START_ADDRESS_LOW,
        CURSOR_LOCATION_HIGH,
        CURSOR_LOCATION_LOW,
        VERTICAL_RETRACE_START,
        VERTICAL_RETRACE_END,
        VERTICAL_DISPLAY_END,
        OFFSET,
        UNDERLINE_LOCATION,
        VERTICAL_BLANKING_START,
        VERTICAL_BLANKING_END,
        CRT_CONTROLLER_MODE_CONTROL,
        LINE_COMPARE
    };
    
    
    /**
     * Enables or disables color mode.
     *
     * @param [in] enable true to enable or false to disable
     */
    void enable_color_mode(bool enable = true);
    
    
    /**
     * Enables or disables the cursor when in text mode.
     *
     * @param [in] enable true to enable or false to disable
     */
    void enable_cursor(bool enable = true);
    
    
    /**
     * Moves the cursor when in text mode.
     *
     * @param [in] row row where to move the cursor to
     * @param [in] column column where to move the cursor to
     */
    void move_cursor(uint32_t row, uint32_t column);
    
    
    /**
     * Reads a byte from a CRT controller register.
     *
     * @param [in] reg register to read from
     * @return byte read
     */
    uint8_t read(Register reg);
    
    
    /**
     * Writes a byte to a CRT controller register.
     *
     * @param [in] reg register to write to
     * @param [in] data byte to write
     */
    void write(Register reg, uint8_t data);
}}}}
