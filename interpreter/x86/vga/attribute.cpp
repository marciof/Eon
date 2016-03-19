#include "../../core/util.h"
#include "../Bit.h"
#include "../io.h"
#include "attribute.h"
#include "general.h"


namespace eon {
namespace x86 {
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
        
        mode = enable ? BIT_SET(mode, 3) : BIT_CLEAR(mode, 3);
        write(ATTRIBUTE_MODE_CONTROL, mode);
    }
    
    
    void enable_graphics_mode(bool enable) {
        uint8_t mode = read(ATTRIBUTE_MODE_CONTROL);
        
        mode = enable ? BIT_SET(mode, 0) : BIT_CLEAR(mode, 0);
        write(ATTRIBUTE_MODE_CONTROL, mode);
    }
    
    
    uint8_t read(Register reg) {
        uint8_t data, status;
        
        reset_state();
        io::read(ADDRESS_PORT, 1, &status);
        status = BIT_GET(status, PAS_BIT) | (reg & ADDRESS_BITS);
        
        reset_state();
        io::write(ADDRESS_PORT, 1, &status);
        io::read(DATA_READ_PORT, 1, &data);
        
        return data;
    }
    
    
    void write(Register reg, uint8_t data) {
        uint8_t status;
        
        reset_state();
        io::read(ADDRESS_PORT, 1, &status);
        status = BIT_GET(status, PAS_BIT) | (reg & ADDRESS_BITS);
        
        reset_state();
        io::write(ADDRESS_PORT, 1, &status);
        io::write(DATA_WRITE_PORT, 1, &data);
    }
}}}}
