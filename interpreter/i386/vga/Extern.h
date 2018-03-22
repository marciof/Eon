#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * External registers interface.
 */

void k_VGA_Extern_enable_color_mode(bool enable);
uint8_t k_VGA_Extern_read_input_status(uint8_t register_num);
