#pragma once
#include <stddef.h>

/**
 * @brief Color register interface
 *
 * Defines the interface of the VGA color registers. These registers provide
 * a mapping from the palette of between 2 and 256 colors to a larger 18-bit
 * color space.
 */


namespace eon {
namespace i386 {
namespace vga {
namespace color {
    /**
     * DAC color entry.
     */
    struct Color {
        unsigned int red: 6;
        unsigned int green: 6;
        unsigned int blue: 6;
    };
    
    
    /**
     * Reads the DAC color registers.
     *
     * @param [in] start index of the first DAC entry to read from
     * @param [in] length number of DAC entries to read
     * @param [out] colors where to write the DAC entries read
     */
    void read(uint8_t start, size_t length, Color* colors);
    
    
    /**
     * Writes to the DAC color registers.
     *
     * @param [in] start index of the first DAC entry to write to
     * @param [in] length number of DAC entries to write
     * @param [in] colors DAC entries to write
     */
    void write(uint8_t start, size_t length, Color* colors);
}}}}
