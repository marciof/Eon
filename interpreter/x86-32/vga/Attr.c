#include "../../core/bit.h"
#include "../IO.h"
#include "Attr.h"
#include "Extern.h"

typedef uint16_t Port;
enum {
    ADDRESS_PORT = 0x3C0,
    DATA_WRITE_PORT = 0x3C0,
    DATA_READ_PORT = 0x3C1,
};

enum {
    /** Palette address source bit. */
    PAS_BIT = 5,

    /** Attribute address bits. */
    ADDRESS_BITS = 0x1F,
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
static void reset_state(void) {
    k_VGA_Extern_read_input_status_reg_1();
}

void k_VGA_Attr_enable_text_blink_mode(bool enable) {
    uint8_t mode = k_VGA_Attr_read(K_VGA_ATTR_MODE_CONTROL);

    k_VGA_Attr_write(K_VGA_ATTR_MODE_CONTROL, (uint8_t) (enable
        ? (mode | K_BIT(3))
        : K_BIT_CLEAR(mode, K_BIT(3))));
}

void k_VGA_Attr_enable_gfx_mode(bool enable) {
    uint8_t mode = k_VGA_Attr_read(K_VGA_ATTR_MODE_CONTROL);

    k_VGA_Attr_write(K_VGA_ATTR_MODE_CONTROL, (uint8_t) (enable
        ? (mode | K_BIT(0))
        : K_BIT_CLEAR(mode, K_BIT(0))));
}

uint8_t k_VGA_Attr_read(k_VGA_Attr_Register reg) {
    reset_state();

    uint8_t status = (uint8_t) (
        (k_IO_read_byte(ADDRESS_PORT) & K_BIT(PAS_BIT))
        | (reg & ADDRESS_BITS));

    reset_state();
    k_IO_write_byte(ADDRESS_PORT, status);
    return k_IO_read_byte(DATA_READ_PORT);
}

void k_VGA_Attr_write(k_VGA_Attr_Register reg, uint8_t data) {
    reset_state();

    uint8_t status = (uint8_t) (
        (k_IO_read_byte(ADDRESS_PORT) & K_BIT(PAS_BIT))
        | (reg & ADDRESS_BITS));

    reset_state();
    k_IO_write_byte(ADDRESS_PORT, status);
    k_IO_write_byte(DATA_WRITE_PORT, data);
}
