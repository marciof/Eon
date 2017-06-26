#include "Memory_Region.h"

e_Multiboot_Memory_Region_Iterator::e_Multiboot_Memory_Region_Iterator(
    multiboot_mmap_entry* array, size_t size_bytes) :
    _array(array), _position(0), _size_bytes(size_bytes) {
}

bool e_Multiboot_Memory_Region_Iterator::has_next() {
    return this->_position < this->_size_bytes;
}

multiboot_mmap_entry* e_Multiboot_Memory_Region_Iterator::next() {
    uint8_t* address = reinterpret_cast<uint8_t*>(_array) + _position;
    multiboot_mmap_entry* region
        = reinterpret_cast<multiboot_mmap_entry*>(address);

    _position += sizeof(region->size) + region->size;
    return region;
}
