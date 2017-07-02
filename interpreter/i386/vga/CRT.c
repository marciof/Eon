#include "../Bit.h"
#include "../IO.h"
#include "CRT.h"
#include "Text.h"

typedef uint16_t Port;
enum {
    COLOR_ADDRESS_PORT = 0x3D4,
    COLOR_DATA_PORT = 0x3D5,

    MONOCHROME_ADDRESS_PORT = 0x3B4,
    MONOCHROME_DATA_PORT = 0x3B5
};

static bool is_color_mode_enabled = true;

void e_VGA_CRT_enable_color_mode(bool enable) {
    is_color_mode_enabled = enable;
}

void e_VGA_CRT_enable_cursor(bool enable) {
    uint8_t status = e_VGA_CRT_read(E_VGA_CRT_CURSOR_START);

    e_VGA_CRT_write(E_VGA_CRT_CURSOR_START, (uint8_t) (enable
        ? E_FLAG_CLEAR(status, E_BIT(5))
        : E_BIT_SET(status, 5)));
}

void e_VGA_CRT_move_cursor(uint32_t line, uint32_t column) {
    size_t columns = e_VGA_Text_get_columns();
    uint16_t position = (uint16_t) ((line * columns) + column);

    e_VGA_CRT_write(E_VGA_CRT_CURSOR_LOCATION_LOW,
        (uint8_t) (position & 0xFF));
    e_VGA_CRT_write(E_VGA_CRT_CURSOR_LOCATION_HIGH,
        (uint8_t) (position >> 8));
}

uint8_t e_VGA_CRT_read(e_VGA_CRT_Register reg) {
    e_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_ADDRESS_PORT
        : MONOCHROME_ADDRESS_PORT,
        reg);

    return e_IO_read_byte(
        is_color_mode_enabled
        ? COLOR_DATA_PORT
        : MONOCHROME_DATA_PORT);
}

void e_VGA_CRT_write(e_VGA_CRT_Register reg, uint8_t data) {
    e_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_ADDRESS_PORT
        : MONOCHROME_ADDRESS_PORT,
        reg);

    e_IO_write_byte(
        is_color_mode_enabled
        ? COLOR_DATA_PORT
        : MONOCHROME_DATA_PORT,
        data);
}
