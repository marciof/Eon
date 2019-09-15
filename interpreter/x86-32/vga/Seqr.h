/**
 * Sequencer register interface. This register reads the information
 * in the frame buffer and converts it into pixel color information.
 * It also sends signals to the CRT controller so that it can provide the
 * timing signals the monitor requires.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t k_VGA_Seqr_Register;
enum {
    K_VGA_SEQR_RESET = 0,
    K_VGA_SEQR_CLOCKING_MODE,
    K_VGA_SEQR_MAP_MASK,
    K_VGA_SEQR_CHARACTER_MAP_SELECT,
    K_VGA_SEQR_SEQUENCER_MEMORY_MODE,
};

void k_VGA_Seqr_enable_screen(bool enable);
uint8_t k_VGA_Seqr_read(k_VGA_Seqr_Register reg);
void k_VGA_Seqr_write(k_VGA_Seqr_Register reg, uint8_t data);
