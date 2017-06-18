#include "../bit.h"
#include "../io.h"
#include "attribute.h"
#include "general.h"

namespace eon {
namespace i386 {
namespace vga {
namespace attribute {
    typedef uint16_t Port;
    enum {
        ADDRESS_PORT = 0x3C0,
        DATA_WRITE_PORT = 0x3C0,
        DATA_READ_PORT = 0x3C1
    };

    enum {
        /** Palette address source bit. */
        PAS_BIT = 5,
        
        /** Attribute address bits. */
        ADDRESS_BITS = 0x1F
    };

    /**
     * Resets the state of the address register.
     *
     * Since the index and data are written to the same port, there's an
     * internal flip-flop which keeps track of whether the next write is an
     * index or data.
     *
     * Because there's no standard way to know its state, just resetting it
     * will make it handle the next write as an index. To reset the flip-flop,
     * it suffices to read the input status register #1 (from the general
     * registers), discarding the value just read.
     */
    static inline void reset_state() {
        general::read_input_status(1);
    }

    void enable_blink_mode(bool enable) {
        uint8_t mode = read(ATTRIBUTE_MODE_CONTROL);
        
        write(ATTRIBUTE_MODE_CONTROL, static_cast<uint8_t>(enable
            ? BIT_SET(mode, 3)
            : BIT_CLEAR(mode, 3)));
    }

    void enable_graphics_mode(bool enable) {
        uint8_t mode = read(ATTRIBUTE_MODE_CONTROL);
        
        write(ATTRIBUTE_MODE_CONTROL, static_cast<uint8_t>(enable
            ? BIT_SET(mode, 0)
            : BIT_CLEAR(mode, 0)));
    }

    uint8_t read(Register reg) {
        reset_state();

        uint8_t status = static_cast<uint8_t>(
            BIT_GET(io::read_byte(ADDRESS_PORT), PAS_BIT)
            | (reg & ADDRESS_BITS));
        
        reset_state();
        io::write_byte(ADDRESS_PORT, status);
        return io::read_byte(DATA_READ_PORT);
    }

    void write(Register reg, uint8_t data) {
        reset_state();

        uint8_t status = static_cast<uint8_t>(
            BIT_GET(io::read_byte(ADDRESS_PORT), PAS_BIT)
            | (reg & ADDRESS_BITS));
        
        reset_state();
        io::write_byte(ADDRESS_PORT, status);
        io::write_byte(DATA_WRITE_PORT, data);
    }
}}}}
