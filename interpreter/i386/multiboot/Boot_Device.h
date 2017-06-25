#pragma once
#include <stdint.h>
#include "Drive.h"
#include "../Bit.h"

namespace eon {
namespace i386 {
namespace multiboot {
    E_BIT_ATTR_PACKED(struct Boot_Device {
        // Partition numbers start at zero.
        enum {
            UNUSED_PARTITION = 0xFF
        };

        uint8_t sub_sub_partition;
        uint8_t sub_partition;
        uint8_t top_level_partition;
        BIOS_Drive_Number drive_number;
        
        void log();
    });
}}}
