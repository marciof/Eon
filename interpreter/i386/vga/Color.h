/**
 * Color register interface. These registers provide a mapping
 * from the palette of between 2 and 256 colors to a larger 18-bit color space.
 */

#pragma once
#include <stddef.h>

/**
 * DAC color entry.
 */
struct k_VGA_Color {
    unsigned int red: 6;
    unsigned int green: 6;
    unsigned int blue: 6;
};

/**
 * Reads the DAC color registers.
 *
 * @param start index of the first DAC entry to read from
 * @param length number of DAC entries to read
 * @param colors where to write the DAC entries read
 */
void k_VGA_Color_read(uint8_t start, size_t length, struct k_VGA_Color* colors);

/**
 * Writes to the DAC color registers.
 *
 * @param start index of the first DAC entry to write to
 * @param length number of DAC entries to write
 * @param colors DAC entries to write
 */
void k_VGA_Color_write(
    uint8_t start, size_t length, struct k_VGA_Color* colors);
