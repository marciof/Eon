#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * Sequencer register interface. This register reads the information
 * in the frame buffer and converts it into pixel color information.
 * It also sends signals to the CRT controller so that it can provide the
 * timing signals the monitor requires.
 */

typedef uint8_t k_VGA_Seqr_Register;
enum {
    K_VGA_SEQR_RESET = 0,
    K_VGA_SEQR_CLOCKING_MODE,
    K_VGA_SEQR_MAP_MASK,
    K_VGA_SEQR_CHARACTER_MAP_SELECT,
    K_VGA_SEQR_SEQUENCER_MEMORY_MODE,
};

/**
 * Turns the screen on or off.
 *
 * @param [in] enable true to enable (on) or false to disable (off)
 */
void k_VGA_Seqr_enable_screen(bool enable);

/**
 * Reads a byte from a sequencer register.
 *
 * @param [in] reg register to read from
 * @return byte read
 */
uint8_t k_VGA_Seqr_read(k_VGA_Seqr_Register reg);

/**
 * Writes a byte to a sequencer register.
 *
 * @param [in] reg register to write to
 * @param [in] data byte to write
 */
void k_VGA_Seqr_write(k_VGA_Seqr_Register reg, uint8_t data);
