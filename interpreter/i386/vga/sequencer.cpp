#include "../bit.h"
#include "../io.h"
#include "sequencer.h"

namespace eon {
namespace i386 {
namespace vga {
namespace sequencer {
    typedef uint16_t Port;
    enum {
        ADDRESS_PORT = 0x3C4,
        DATA_PORT = 0x3C5
    };

    void enable_screen(bool enable) {
        uint8_t mode = read(CLOCKING_MODE);

        write(CLOCKING_MODE, static_cast<uint8_t>(enable
            ? BIT_CLEAR(mode, 5)
            : BIT_SET(mode, 5)));
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
