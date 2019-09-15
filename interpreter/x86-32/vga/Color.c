#include "../IO.h"
#include "Color.h"

typedef uint16_t Port;
enum {
    DAC_ADDRESS_WRITE_MODE_PORT = 0x3C8,
    DAC_ADDRESS_READ_MODE_WRITE_PORT = 0x3C7,
    DAC_DATA_PORT = 0x3C9,
    DAC_STATE_READ_PORT = 0x3C7,
};

void k_VGA_Color_read(uint8_t start, size_t length, struct k_VGA_Color* colors) {
    k_IO_write_byte(DAC_ADDRESS_READ_MODE_WRITE_PORT, start);

    for (size_t i = 0; i < length; ++i) {
        colors[i].red = k_IO_read_byte(DAC_DATA_PORT);
        colors[i].green = k_IO_read_byte(DAC_DATA_PORT);
        colors[i].blue = k_IO_read_byte(DAC_DATA_PORT);
    }
}

void k_VGA_Color_write(uint8_t start, size_t length, struct k_VGA_Color* colors) {
    k_IO_write_byte(DAC_ADDRESS_WRITE_MODE_PORT, start);

    for (size_t i = 0; i < length; ++i) {
        k_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].red);
        k_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].green);
        k_IO_write_byte(DAC_DATA_PORT, (uint8_t) colors[i].blue);
    }
}
