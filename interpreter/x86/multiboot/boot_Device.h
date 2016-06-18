#pragma once
#include <stdint.h>
#include "../../core/util.h"
#include "drive.h"

namespace eon {
namespace x86 {
namespace multiboot {
    PACKED(struct Boot_Device {
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
