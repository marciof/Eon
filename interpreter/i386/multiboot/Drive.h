#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../Bit.h"

typedef uint8_t e_Multiboot_Drive_Access_Mode;
enum {
    // Traditional Cylinder/Head/Sector addressing mode.
    E_MULTIBOOT_DRIVE_CHS_MODE = 0,

    // Logical Block Addressing mode.
    E_MULTIBOOT_DRIVE_LBA_MODE = 1
};

// As read by the BIOS INT 13h disk interface.
typedef uint8_t e_Multiboot_Drive_BIOS_Nr;
enum {
    E_MULTIBOOT_DRIVE_FIRST_DISKETTE_DRIVE = 0,
    E_MULTIBOOT_DRIVE_FIRST_HARD_DISK_DRIVE = 0x80
};

E_BIT_ATTR_PACKED(struct e_Multiboot_Drive {
    // Size doesn't equal `10 + 2 * nr. ports` due to alignment.
    uint32_t size;

    e_Multiboot_Drive_BIOS_Nr number;
    e_Multiboot_Drive_Access_Mode access_mode;
    uint16_t cylinders;
    uint8_t heads;
    uint8_t sectors;

    // Array (ending in NULL) of I/O ports used for the drive in the BIOS
    // code. This array may contain any number of I/O ports that are not
    // related to the drive actually (such as DMA controllers' ports).
    uint16_t* ports;

    void log();
});

class e_Multiboot_Drive_Iterator {
public:
    e_Multiboot_Drive_Iterator(e_Multiboot_Drive* array, size_t size_bytes);
    bool has_next();
    e_Multiboot_Drive* next();

private:
    e_Multiboot_Drive* _array;
    size_t _position;
    size_t _size_bytes;
};
