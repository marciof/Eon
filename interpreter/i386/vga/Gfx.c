#include "../Bit.h"
#include "../IO.h"
#include "Gfx.h"

typedef uint16_t Port;
enum {
    ADDRESS_PORT = 0x3CE,
    DATA_PORT = 0x3CF,
};

static const struct k_VGA_Gfx_Memory_Map MEMORY_MAPS[] = {
    {
        false,
        (uint8_t*) 0xA0000,
        128 * 1024,
        25,
        80,
    },
    {
        true,
        (uint8_t*) 0xA0000,
        64 * 1024,
        25,
        80,
    },
    {
        false,
        (uint8_t*) 0xB0000,
        32 * 1024,
        25,
        80,
    },
    {
        true,
        (uint8_t*) 0xB8000,
        32 * 1024,
        25,
        80,
    },
};

const struct k_VGA_Gfx_Memory_Map* k_VGA_Gfx_get_memory_map() {
    size_t position = (size_t)
        ((k_VGA_Gfx_read(K_VGA_GFX_MISC) & (K_BIT(3) | K_BIT(2))) >> 2);

    return &MEMORY_MAPS[position];
}

uint8_t k_VGA_Gfx_read(k_VGA_Gfx_Register reg) {
    k_IO_write_byte(ADDRESS_PORT, reg);
    return k_IO_read_byte(DATA_PORT);
}

void k_VGA_Gfx_write(k_VGA_Gfx_Register reg, uint8_t data) {
    k_IO_write_byte(ADDRESS_PORT, reg);
    k_IO_write_byte(DATA_PORT, data);
}
