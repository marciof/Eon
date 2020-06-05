#include "../../core/bit.h"
#include "../IO.h"
#include "Seqr.h"

typedef uint16_t Port;
enum {
    ADDRESS_PORT = 0x3C4,
    DATA_PORT = 0x3C5,
};

void k_VGA_Seqr_enable_screen(bool enable) {
    uint8_t mode = k_VGA_Seqr_read(K_VGA_SEQR_CLOCKING_MODE);

    k_VGA_Seqr_write(K_VGA_SEQR_CLOCKING_MODE, (uint8_t) (enable
        ? K_BIT_CLEAR(mode, K_BIT(5))
        : (mode | K_BIT(5))));
}

uint8_t k_VGA_Seqr_read(k_VGA_Seqr_Register reg) {
    k_IO_write_byte(ADDRESS_PORT, reg);
    return k_IO_read_byte(DATA_PORT);
}

void k_VGA_Seqr_write(k_VGA_Seqr_Register reg, uint8_t data) {
    k_IO_write_byte(ADDRESS_PORT, reg);
    k_IO_write_byte(DATA_PORT, data);
}
