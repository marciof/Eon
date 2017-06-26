#include "../../core/Log.h"
#include "Drive.h"

void e_Multiboot_Drive::log() {
    e_Log_get()->info(
        "Drive: nr={iu}; mode={iu}; cylinders={iu}; "
        "heads={iu}; sectors={iu}; ports={iuh}",
        this->number, this->access_mode, this->cylinders,
        this->heads, this->sectors, this->ports);
}

e_Multiboot_Drive_Iterator::e_Multiboot_Drive_Iterator(e_Multiboot_Drive* array, size_t size_bytes):
    _array(array), _position(0), _size_bytes(size_bytes) {
}

bool e_Multiboot_Drive_Iterator::has_next() {
    return this->_position < this->_size_bytes;
}

e_Multiboot_Drive* e_Multiboot_Drive_Iterator::next() {
    uint8_t* address = reinterpret_cast<uint8_t*>(_array) + _position;
    e_Multiboot_Drive* drive = reinterpret_cast<e_Multiboot_Drive*>(address);

    _position += drive->size;
    return drive;
}
