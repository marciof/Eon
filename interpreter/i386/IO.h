#pragma once
#include <stddef.h>
#include <stdint.h>

extern "C" uint8_t e_IO_read_byte(uint16_t port);
extern "C" uint32_t e_IO_read_dword(uint16_t port);
extern "C" uint16_t e_IO_read_word(uint16_t port);
extern "C" void e_IO_write_byte(uint16_t port, uint8_t data);
extern "C" void e_IO_write_dword(uint16_t port, uint32_t data);
extern "C" void e_IO_write_word(uint16_t port, uint16_t data);
