#include "../Bit.h"
#include "../IO.h"
#include "Attr.h"
#include "Extern.h"

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
    e_VGA_Extern_read_input_status(1);
}

void e_VGA_Attr_enable_text_blink_mode(bool enable) {
    uint8_t mode = e_VGA_Attr_read(E_VGA_ATTR_MODE_CONTROL);

    e_VGA_Attr_write(E_VGA_ATTR_MODE_CONTROL, static_cast<uint8_t>(enable
        ? E_BIT_SET(mode, 3)
        : E_BIT_CLEAR(mode, 3)));
}

void e_VGA_Attr_enable_gfx_mode(bool enable) {
    uint8_t mode = e_VGA_Attr_read(E_VGA_ATTR_MODE_CONTROL);

    e_VGA_Attr_write(E_VGA_ATTR_MODE_CONTROL, static_cast<uint8_t>(enable
        ? E_BIT_SET(mode, 0)
        : E_BIT_CLEAR(mode, 0)));
}

uint8_t e_VGA_Attr_read(e_VGA_Attr_Register reg) {
    reset_state();

    uint8_t status = static_cast<uint8_t>(
        E_BIT_GET(e_IO_read_byte(ADDRESS_PORT), PAS_BIT)
        | (reg & ADDRESS_BITS));

    reset_state();
    e_IO_write_byte(ADDRESS_PORT, status);
    return e_IO_read_byte(DATA_READ_PORT);
}

void e_VGA_Attr_write(e_VGA_Attr_Register reg, uint8_t data) {
    reset_state();

    uint8_t status = static_cast<uint8_t>(
        E_BIT_GET(e_IO_read_byte(ADDRESS_PORT), PAS_BIT)
        | (reg & ADDRESS_BITS));

    reset_state();
    e_IO_write_byte(ADDRESS_PORT, status);
    e_IO_write_byte(DATA_WRITE_PORT, data);
}
