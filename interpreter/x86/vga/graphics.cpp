#include "../Bit.h"
#include "../io.h"
#include "graphics.h"


namespace eon {
namespace x86 {
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
        uint8_t status = read(MISCELLANEOUS_GRAPHICS);
        size_t position = (status & (BIT(3) | BIT(2))) >> 2;
        
        return &_MEMORY_MAPS[position];
    }
    
    
    uint8_t read(Register reg) {
        uint8_t data;
        
        io::write(ADDRESS_PORT, 1, &reg);
        io::read(DATA_PORT, 1, &data);
        
        return data;
    }
    
    
    void write(Register reg, uint8_t data) {
        io::write(ADDRESS_PORT, 1, &reg);
        io::write(DATA_PORT, 1, &data);
    }
}}}}
