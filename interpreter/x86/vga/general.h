#pragma once
#include <stdint.h>

/**
 * @brief General registers interface
 *
 * Defines the interface of the VGA general registers (also known as external
 * registers).
 */


namespace eon {
namespace x86 {
namespace vga {
namespace general {
    /**
     * Enables or disables color mode.
     *
     * @param [in] enable true to enable or false to disable
     */
    void enable_color_mode(bool enable = true);
    
    
    /**
     * Reads a byte from an input status register.
     *
     * @param [in] register_number number of the register to read from (0 or 1)
     * @return byte read
     */
    uint8_t read_input_status(uint8_t register_number);
}}}}
