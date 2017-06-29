#include "../Bit.h"
#include "../IO.h"
#include "Seqr.h"

typedef uint16_t Port;
enum {
    ADDRESS_PORT = 0x3C4,
    DATA_PORT = 0x3C5
};

void e_VGA_Seqr_enable_screen(bool enable) {
    uint8_t mode = e_VGA_Seqr_read(E_VGA_SEQR_CLOCKING_MODE);

    e_VGA_Seqr_write(E_VGA_SEQR_CLOCKING_MODE, (uint8_t) (enable
        ? E_BIT_CLEAR(mode, 5)
        : E_BIT_SET(mode, 5)));
}

uint8_t e_VGA_Seqr_read(e_VGA_Seqr_Register reg) {
    e_IO_write_byte(ADDRESS_PORT, reg);
    return e_IO_read_byte(DATA_PORT);
}

void e_VGA_Seqr_write(e_VGA_Seqr_Register reg, uint8_t data) {
    e_IO_write_byte(ADDRESS_PORT, reg);
    e_IO_write_byte(DATA_PORT, data);
}
