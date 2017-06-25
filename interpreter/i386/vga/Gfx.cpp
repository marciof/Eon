#include "../Bit.h"
#include "../IO.h"
#include "Gfx.h"

typedef uint16_t Port;
enum {
    ADDRESS_PORT = 0x3CE,
    DATA_PORT = 0x3CF
};

static const struct e_VGA_Gfx_Memory_Map MEMORY_MAPS[] = {
    {
        false,
        reinterpret_cast<uint8_t*>(0xA0000),
        128 * 1024,
        25,
        80,
    },
    {
        true,
        reinterpret_cast<uint8_t*>(0xA0000),
        64 * 1024,
        25,
        80,
    },
    {
        false,
        reinterpret_cast<uint8_t*>(0xB0000),
        32 * 1024,
        25,
        80,
    },
    {
        true,
        reinterpret_cast<uint8_t*>(0xB8000),
        32 * 1024,
        25,
        80,
    },
};

const e_VGA_Gfx_Memory_Map* e_VGA_Gfx_get_memory_map() {
    size_t position = static_cast<size_t>(
        (e_VGA_Gfx_read(VGA_GFX_MISCELLANEOUS) & (E_BIT(3) | E_BIT(2))) >> 2);

    return &MEMORY_MAPS[position];
}

uint8_t e_VGA_Gfx_read(e_VGA_Gfx_Register reg) {
    e_IO_write_byte(ADDRESS_PORT, reg);
    return e_IO_read_byte(DATA_PORT);
}

void e_VGA_Gfx_write(e_VGA_Gfx_Register reg, uint8_t data) {
    e_IO_write_byte(ADDRESS_PORT, reg);
    e_IO_write_byte(DATA_PORT, data);
}
