#pragma once
#include <stddef.h>
#include <stdint.h>

namespace eon {
namespace x86 {
namespace io {
    extern "C" uint8_t read_byte(uint16_t port);
    extern "C" uint32_t read_dword(uint16_t port);
    extern "C" uint16_t read_word(uint16_t port);
    extern "C" void write_byte(uint16_t port, uint8_t data);
    extern "C" void write_dword(uint16_t port, uint32_t data);
    extern "C" void write_word(uint16_t port, uint16_t data);
}}}
