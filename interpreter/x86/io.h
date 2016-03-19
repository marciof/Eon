#pragma once
#include <stddef.h>
#include <stdint.h>

namespace eon {
namespace x86 {
namespace io {
    void read(size_t port, size_t bytes, uint8_t* data);
    void write(size_t port, size_t bytes, uint8_t* data);
}}}
