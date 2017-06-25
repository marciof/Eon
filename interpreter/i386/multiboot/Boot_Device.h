#pragma once
#include <stdint.h>
#include "Drive.h"
#include "../Bit.h"

E_BIT_ATTR_PACKED(struct e_Multiboot_Boot_Device {
    // Partition numbers start at zero.
    enum {
        UNUSED_PARTITION = 0xFF
    };

    uint8_t sub_sub_partition;
    uint8_t sub_partition;
    uint8_t top_level_partition;
    eon::i386::multiboot::BIOS_Drive_Number drive_number;

    void log();
});
