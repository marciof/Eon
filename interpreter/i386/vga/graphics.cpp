#include "../bit.h"
#include "../io.h"
#include "graphics.h"

namespace eon {
namespace i386 {
namespace vga {
namespace graphics {
    typedef uint16_t Port;
    enum {
        ADDRESS_PORT = 0x3CE,
        DATA_PORT = 0x3CF
    };

    static const struct Memory_Map _MEMORY_MAPS[] = {
        {
            false,
            reinterpret_cast<uint8_t*>(0xA0000),
            128 * 1024,
            25,
            80,
        },
        {
            true,
            reinterpret_cast<uint8_t*>(0xA0000),
            64 * 1024,
            25,
            80,
        },
        {
            false,
            reinterpret_cast<uint8_t*>(0xB0000),
            32 * 1024,
            25,
            80,
        },
        {
            true,
            reinterpret_cast<uint8_t*>(0xB8000),
            32 * 1024,
            25,
            80,
        },
    };
    
    const Memory_Map* get_memory_map() {
        size_t position = static_cast<size_t>(
            (read(MISCELLANEOUS_GRAPHICS) & (BIT(3) | BIT(2))) >> 2);
        
        return &_MEMORY_MAPS[position];
    }
    
    uint8_t read(Register reg) {
        io::write_byte(ADDRESS_PORT, reg);
        return io::read_byte(DATA_PORT);
    }

    void write(Register reg, uint8_t data) {
        io::write_byte(ADDRESS_PORT, reg);
        io::write_byte(DATA_PORT, data);
    }
}}}}
