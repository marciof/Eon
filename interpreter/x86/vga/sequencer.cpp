#include "../Bit.h"
#include "../io.h"
#include "sequencer.h"


namespace eon {
namespace x86 {
namespace vga {
namespace sequencer {
    typedef uint16_t Port;
    enum {
        ADDRESS_PORT = 0x3C4,
        DATA_PORT = 0x3C5
    };
    
    
    void enable_screen(bool enable) {
        uint8_t mode = read(CLOCKING_MODE);
        
        mode = enable ? BIT_CLEAR(mode, 5) : BIT_SET(mode, 5);
        write(CLOCKING_MODE, mode);
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
