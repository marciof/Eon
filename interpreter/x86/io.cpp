#include "../core/util.h"
#include "../core/Log.h"
#include "io.h"

#define BYTE_COUNT_ERROR "Invalid number of bytes"

extern "C" uint8_t read_byte(uint16_t port);
extern "C" uint32_t read_dword(uint16_t port);
extern "C" uint16_t read_word(uint16_t port);
extern "C" void write_byte(uint16_t port, uint8_t data);
extern "C" void write_dword(uint16_t port, uint32_t data);
extern "C" void write_word(uint16_t port, uint16_t data);

namespace eon {
namespace x86 {
namespace io {
    void read(size_t port, size_t bytes, uint8_t* data) {
        switch (bytes) {
        case 1:
            *data = read_byte(port);
            break;
        case 2:
            *reinterpret_cast<uint16_t*>(data) = read_word(port);
            break;
        case 4:
            *reinterpret_cast<uint32_t*>(data) = read_dword(port);
            break;
        default:
            core::Log::get()->error(BYTE_COUNT_ERROR ": Read {iu} B.", bytes);
            break;
        }
    }

    void write(size_t port, size_t bytes, uint8_t* data) {
        switch (bytes) {
        case 1:
            write_byte(port, *data);
            break;
        case 2:
            write_word(port, *reinterpret_cast<uint16_t*>(data));
            break;
        case 4:
            write_dword(port, *reinterpret_cast<uint32_t*>(data));
            break;
        default:
            core::Log::get()->error(BYTE_COUNT_ERROR ": Write {iu} B.", bytes);
            break;
        }
    }
}}}
