#include <multiboot/multiboot.h>

// Multiboot Specification 0.7.
const struct multiboot_header eon_multiboot_header = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_MEMORY_INFO,
    (multiboot_uint32_t) (-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_MEMORY_INFO)),
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
