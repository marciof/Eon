#pragma once
#include <stddef.h>
#include <stdint.h>


/**
 * @brief Graphics registers interface
 *
 * Defines the interface of the VGA graphics registers. These registers allow
 * to query display information such as color, width, and height.
 */


namespace eon {
namespace x86 {
namespace vga {
namespace graphics {
    typedef uint8_t Register;
    enum {
        SET_RESET = 0,
        ENABLE_SET_RESET,
        COLOR_COMPARE,
        DATA_ROTATE,
        READ_MAP_SELECT,
        GRAPHICS_MODE,
        MISCELLANEOUS_GRAPHICS,
        COLOR_DONT_CARE,
        BIT_MASK
    };
    
    
    /**
     * Specifies the range of memory addresses that is decoded by the VGA
     * hardware and mapped into display memory accesses.
     */
    struct Memory_Map {
        bool is_color;
        uint8_t* start;
        size_t length;
        size_t rows;
        size_t columns;
    };
    
    
    const Memory_Map* get_memory_map();
    uint8_t read(Register reg);
    void write(Register reg, uint8_t data);
}}}}
