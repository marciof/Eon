#include "../io.h"
#include "color.h"


namespace eon {
namespace x86 {
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
        io::write(DAC_ADDRESS_READ_MODE_WRITE_PORT, 1, &start);
        
        for (size_t i = 0; i < length; ++i) {
            uint8_t red, green, blue;
            
            io::read(DAC_DATA_PORT, 1, &red);
            io::read(DAC_DATA_PORT, 1, &green);
            io::read(DAC_DATA_PORT, 1, &blue);
            
            colors[i].red = red;
            colors[i].green = green;
            colors[i].blue = blue;
        }
    }
    
    
    void write(uint8_t start, size_t length, Color* colors) {
        io::write(DAC_ADDRESS_WRITE_MODE_PORT, 1, &start);
        
        for (size_t i = 0; i < length; ++i) {
            uint8_t red = colors[i].red;
            uint8_t green = colors[i].green;
            uint8_t blue = colors[i].blue;
            
            io::write(DAC_DATA_PORT, 1, &red);
            io::write(DAC_DATA_PORT, 1, &green);
            io::write(DAC_DATA_PORT, 1, &blue);
        }
    }
}}}}
