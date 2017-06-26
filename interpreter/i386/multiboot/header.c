#include <multiboot/multiboot.h>

// Multiboot Specification 0.7.
// FIXME: use macro for GCC extension
const struct multiboot_header e_multiboot_header __attribute__((section(".multiboot"))) = {
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
