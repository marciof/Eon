#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * Sequencer register interface. This register reads the information
 * in the frame buffer and converts it into pixel color information.
 * It also sends signals to the CRT controller so that it can provide the
 * timing signals the monitor requires.
 */

typedef uint8_t e_VGA_Seqr_Register;
enum {
    E_VGA_SEQR_RESET = 0,
    E_VGA_SEQR_CLOCKING_MODE,
    E_VGA_SEQR_MAP_MASK,
    E_VGA_SEQR_CHARACTER_MAP_SELECT,
    E_VGA_SEQR_SEQUENCER_MEMORY_MODE,
};

/**
 * Turns the screen on or off.
 *
 * @param [in] enable true to enable (on) or false to disable (off)
 */
void e_VGA_Seqr_enable_screen(bool enable);

/**
 * Reads a byte from a sequencer register.
 *
 * @param [in] reg register to read from
 * @return byte read
 */
uint8_t e_VGA_Seqr_read(e_VGA_Seqr_Register reg);

/**
 * Writes a byte to a sequencer register.
 *
 * @param [in] reg register to write to
 * @param [in] data byte to write
 */
void e_VGA_Seqr_write(e_VGA_Seqr_Register reg, uint8_t data);
