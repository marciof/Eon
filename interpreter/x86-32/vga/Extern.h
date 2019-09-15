/**
 * External registers interface.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

void k_VGA_Extern_enable_color_mode(bool enable);
uint8_t k_VGA_Extern_read_input_status_reg_0(void);
uint8_t k_VGA_Extern_read_input_status_reg_1(void);
