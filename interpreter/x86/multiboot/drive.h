#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../../core/util.h"

namespace eon {
namespace x86 {
namespace multiboot {

    typedef uint8_t Drive_Access_Mode;
    enum {
        // Traditional Cylinder/Head/Sector addressing mode.
        CHS_MODE = 0,

        // Logical Block Addressing mode.
        LBA_MODE = 1
    };

    // As read by the BIOS INT 13h disk interface.
    typedef uint8_t BIOS_Drive_Number;
    enum {
        FIRST_DISKETTE_DRIVE = 0,
        FIRST_HARD_DISK_DRIVE = 0x80
    };

    PACKED(struct Drive {
        // Size doesn't equal `10 + 2 * nr. ports` due to alignment.
        uint32_t size;
        
        BIOS_Drive_Number number;
        Drive_Access_Mode access_mode;
        uint16_t cylinders;
        uint8_t heads;
        uint8_t sectors;
        
        // Array (ending in NULL) of I/O ports used for the drive in the BIOS
        // code. This array may contain any number of I/O ports that are not
        // related to the drive actually (such as DMA controllers' ports).
        uint16_t* ports;
        
        void log();
    });

    class Drive_Iterator {
    public:
        Drive_Iterator(Drive* array, size_t size_bytes);
        bool has_next();
        Drive* next();

    private:
        Drive* _array;
        size_t _position;
        size_t _size_bytes;
    };
}}}
