#pragma once
#include <stddef.h>
#include <stdint.h>

// TODO: Figure out why this is needed, or switch to Multiboot 2?
typedef uint16_t grub_uint16_t;
typedef uint32_t grub_uint32_t;
#define GRUB_PACKED __attribute__ ((packed))
#include <multiboot.h>


namespace eon {
namespace x86 {
namespace multiboot {
    class Memory_Region_Iterator {
    public:
        Memory_Region_Iterator(multiboot_mmap_entry* array, size_t size_bytes);
        bool has_next();
        multiboot_mmap_entry* next();

    private:
        multiboot_mmap_entry* _array;
        size_t _position;
        size_t _size_bytes;
    };
}}}
