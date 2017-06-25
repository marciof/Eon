#include "../Bit.h"
#include "../IO.h"
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
            ? E_BIT_CLEAR(mode, 5)
            : E_BIT_SET(mode, 5)));
    }
    
    uint8_t read(Register reg) {
        e_IO_write_byte(ADDRESS_PORT, reg);
        return e_IO_read_byte(DATA_PORT);
    }

    void write(Register reg, uint8_t data) {
        e_IO_write_byte(ADDRESS_PORT, reg);
        e_IO_write_byte(DATA_PORT, data);
    }
}}}}
