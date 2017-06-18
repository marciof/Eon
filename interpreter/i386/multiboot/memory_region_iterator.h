#pragma once
#include <multiboot/multiboot.h>
#include <stddef.h>
#include <stdint.h>

namespace eon {
namespace i386 {
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
