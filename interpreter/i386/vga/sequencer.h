#pragma once
#include <stdint.h>

/**
 * @brief Sequencer register interface
 *
 * Defines the interface of the VGA sequencer register. This register reads
 * the information in the frame buffer and converts it into pixel color
 * information.
 *
 * It also sends signals to the CRT controller so that it can provide the
 * timing signals the monitor requires.
 */


namespace eon {
namespace i386 {
namespace vga {
namespace sequencer {
    typedef uint8_t Register;
    enum {
        RESET = 0,
        CLOCKING_MODE,
        MAP_MASK,
        CHARACTER_MAP_SELECT,
        SEQUENCER_MEMORY_MODE
    };
    
    
    /**
     * Turns the screen on or off.
     *
     * @param [in] enable true to enable (on) or false to disable (off)
     */
    void enable_screen(bool enable = true);
    
    
    /**
     * Reads a byte from a sequencer register.
     *
     * @param [in] reg register to read from
     * @return byte read
     */
    uint8_t read(Register reg);
    
    
    /**
     * Writes a byte to a sequencer register.
     *
     * @param [in] reg register to write to
     * @param [in] data byte to write
     */
    void write(Register reg, uint8_t data);
}}}}
