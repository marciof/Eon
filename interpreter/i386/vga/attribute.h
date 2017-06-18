#pragma once
#include <stdint.h>

/**
 * @brief Attribute controller register interface
 *
 * Defines the interface of the VGA attribute controller register. This
 * register formats the pixel color information such that the pixel values
 * can be submitted to the DAC (Digital to Analog Converter).
 */


namespace eon {
namespace i386 {
namespace vga {
namespace attribute {
    typedef uint8_t Register;
    enum {
        /** There are 16 consecutive palette registers. */
        PALETTES = 0,
        ATTRIBUTE_MODE_CONTROL = 16,
        OVERSCAN_COLOR,
        COLOR_PLANE_ENABLE,
        HORIZONTAL_PIXEL_PANNING,
        COLOR_SELECT
    };
    
    
    /**
     * Enables or disables blink mode when in text mode.
     *
     * @param [in] enable true to enable or false to disable
     * @note The text mode must be initialized.
     */
    void enable_blink_mode(bool enable = true);
    
    
    /**
     * Enables or disables graphics mode.
     *
     * @param [in] enable true to enable or false to disable
     * @note The text mode must be initialized.
     */
    void enable_graphics_mode(bool enable = true);
    
    
    /**
     * Reads a byte from an attribute controller register.
     *
     * @param [in] reg register to read from
     * @return byte read
     * @note The text mode must be initialized.
     */
    uint8_t read(Register reg);
    
    
    /**
     * Writes a byte to an attribute controller register.
     *
     * @param [in] reg register to write to
     * @param [in] data byte to write
     * @note The text mode must be initialized.
     */
    void write(Register reg, uint8_t data);
}}}}
