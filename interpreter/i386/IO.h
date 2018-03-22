#pragma once
#include <stddef.h>
#include <stdint.h>

extern uint8_t k_IO_read_byte(uint16_t port);
extern uint32_t k_IO_read_dword(uint16_t port);
extern uint16_t k_IO_read_word(uint16_t port);
extern void k_IO_write_byte(uint16_t port, uint8_t data);
extern void k_IO_write_dword(uint16_t port, uint32_t data);
extern void k_IO_write_word(uint16_t port, uint16_t data);
