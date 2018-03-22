#include "../Bit.h"
#include "../IO.h"
#include "CRT.h"
#include "Text.h"

typedef uint16_t Port;
enum {
    COLOR_ADDRESS_PORT = 0x3D4,
    COLOR_DATA_PORT = 0x3D5,

    MONOCHROME_ADDRESS_PORT = 0x3B4,
    MONOCHROME_DATA_PORT = 0x3B5,
};

static bool is_color_mode_enabled = true;

void k_VGA_CRT_enable_color_mode(bool enable) {
    is_color_mode_enabled = enable;
}

void k_VGA_CRT_enable_cursor(bool enable) {
    uint8_t status = k_VGA_CRT_read(K_VGA_CRT_CURSOR_START);

    k_VGA_CRT_write(K_VGA_CRT_CURSOR_START, (uint8_t) (enable
        ? K_BIT_CLEAR(status, K_BIT(5))
        : (status | K_BIT(5))));
}

void k_VGA_CRT_move_cursor(uint32_t line, uint32_t column) {
    size_t columns = k_VGA_Text_get_columns();
    uint16_t position = (uint16_t) ((line * columns) + column);

    k_VGA_CRT_write(K_VGA_CRT_CURSOR_LOCATION_LOW,
        (uint8_t) (position & 0xFF));
    k_VGA_CRT_write(K_VGA_CRT_CURSOR_LOCATION_HIGH,
        (uint8_t) (position >> 8));
}

uint8_t k_VGA_CRT_read(k_VGA_CRT_Register reg) {
    k_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_ADDRESS_PORT
        : MONOCHROME_ADDRESS_PORT,
        reg);

    return k_IO_read_byte(
        is_color_mode_enabled
        ? COLOR_DATA_PORT
        : MONOCHROME_DATA_PORT);
}

void k_VGA_CRT_write(k_VGA_CRT_Register reg, uint8_t data) {
    k_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_ADDRESS_PORT
        : MONOCHROME_ADDRESS_PORT,
        reg);

    k_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_DATA_PORT
        : MONOCHROME_DATA_PORT,
        data);
}
