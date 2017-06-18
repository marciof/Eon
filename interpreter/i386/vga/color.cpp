#include "../io.h"
#include "color.h"

namespace eon {
namespace i386 {
namespace vga {
namespace color {
    typedef uint16_t Port;
    enum {
        DAC_ADDRESS_WRITE_MODE_PORT = 0x3C8,
        DAC_ADDRESS_READ_MODE_WRITE_PORT = 0x3C7,
        DAC_DATA_PORT = 0x3C9,
        DAC_STATE_READ_PORT = 0x3C7
    };
    
    void read(uint8_t start, size_t length, Color* colors) {
        io::write_byte(DAC_ADDRESS_READ_MODE_WRITE_PORT, start);
        
        for (size_t i = 0; i < length; ++i) {
            colors[i].red = io::read_byte(DAC_DATA_PORT);
            colors[i].green = io::read_byte(DAC_DATA_PORT);
            colors[i].blue = io::read_byte(DAC_DATA_PORT);
        }
    }

    void write(uint8_t start, size_t length, Color* colors) {
        io::write_byte(DAC_ADDRESS_WRITE_MODE_PORT, start);
        
        for (size_t i = 0; i < length; ++i) {
            io::write_byte(DAC_DATA_PORT, static_cast<uint8_t>(colors[i].red));
            io::write_byte(DAC_DATA_PORT, static_cast<uint8_t>(colors[i].green));
            io::write_byte(DAC_DATA_PORT, static_cast<uint8_t>(colors[i].blue));
        }
    }
}}}}
