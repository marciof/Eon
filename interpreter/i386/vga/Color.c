#include "../IO.h"
#include "Color.h"

typedef uint16_t Port;
enum {
    DAC_ADDRESS_WRITE_MODE_PORT = 0x3C8,
    DAC_ADDRESS_READ_MODE_WRITE_PORT = 0x3C7,
    DAC_DATA_PORT = 0x3C9,
    DAC_STATE_READ_PORT = 0x3C7,
};

void e_VGA_Color_read(uint8_t start, size_t length, struct e_VGA_Color* colors) {
    e_IO_write_byte(DAC_ADDRESS_READ_MODE_WRITE_PORT, start);

    for (size_t i = 0; i < length; ++i) {
        colors[i].red = e_IO_read_byte(DAC_DATA_PORT);
        colors[i].green = e_IO_read_byte(DAC_DATA_PORT);
        colors[i].blue = e_IO_read_byte(DAC_DATA_PORT);
    }
}

void e_VGA_Color_write(uint8_t start, size_t length, struct e_VGA_Color* colors) {
    e_IO_write_byte(DAC_ADDRESS_WRITE_MODE_PORT, start);

    for (size_t i = 0; i < length; ++i) {
        e_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].red);
        e_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].green);
        e_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].blue);
    }
}
