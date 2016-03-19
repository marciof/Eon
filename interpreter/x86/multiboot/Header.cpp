#include <stdint.h>
#include "../../core/util.h"

// TODO: Figure out why this is needed, or switch to Multiboot 2?
typedef uint16_t grub_uint16_t;
typedef uint32_t grub_uint32_t;
#define GRUB_PACKED __attribute__ ((packed))
#include <multiboot.h>


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
