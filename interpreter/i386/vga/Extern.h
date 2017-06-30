#pragma once
#include <stdbool.h>
#include <stdint.h>

/**
 * External registers interface.
 */

void e_VGA_Extern_enable_color_mode(bool enable);
uint8_t e_VGA_Extern_read_input_status(uint8_t register_num);
