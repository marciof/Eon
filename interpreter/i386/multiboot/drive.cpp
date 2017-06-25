#include "../../core/log.h"
#include "drive.h"

namespace eon {
namespace i386 {
namespace multiboot {
    void Drive::log() {
        e_Log::get()->info(
            "Drive: nr={iu}; mode={iu}; cylinders={iu}; "
            "heads={iu}; sectors={iu}; ports={iuh}",
            this->number, this->access_mode, this->cylinders,
            this->heads, this->sectors, this->ports);
    }

    Drive_Iterator::Drive_Iterator(Drive* array, size_t size_bytes):
        _array(array), _position(0), _size_bytes(size_bytes) {
    }

    bool Drive_Iterator::has_next() {
        return this->_position < this->_size_bytes;
    }
    
    Drive* Drive_Iterator::next() {
        uint8_t* address = reinterpret_cast<uint8_t*>(_array) + _position;
        Drive* drive = reinterpret_cast<Drive*>(address);
        
        _position += drive->size;
        return drive;
    }
}}}
