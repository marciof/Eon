#pragma once
#include <multiboot/multiboot.h>
#include <stdint.h>

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
