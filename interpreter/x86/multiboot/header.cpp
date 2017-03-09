#include <multiboot/multiboot.h>
#include <stdint.h>

namespace eon {
namespace x86 {
namespace multiboot {
    // Multiboot Specification 0.7.
    extern "C" const multiboot_header _multiboot_header = {
        MULTIBOOT_HEADER_MAGIC,
        MULTIBOOT_MEMORY_INFO,
        static_cast<uint32_t>(-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_MEMORY_INFO)),
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };
}}}
