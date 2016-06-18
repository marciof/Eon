#pragma once
#include <stdint.h>
#include "../../core/util.h"

// TODO: Figure out why this is needed, or switch to Multiboot 2?
typedef uint16_t grub_uint16_t;
typedef uint32_t grub_uint32_t;
#define GRUB_PACKED __attribute__ ((packed))
#include <multiboot.h>


namespace eon {
namespace x86 {
namespace multiboot {

    // http://www.gnu.org/software/grub/manual/multiboot/
    struct Information: public multiboot_info {
    public:
        static Information* get();
        void log();

    private:
        void log_boot_device();
        void log_boot_modules();
        void log_drives();
        void log_memory_map();
        void log_symbol_table();
        void log_vbe();
    };
}}}
