#pragma once
#include <multiboot/multiboot.h>
#include <stdint.h>

// http://www.gnu.org/software/grub/manual/multiboot/
struct e_Multiboot_Info: public multiboot_info {
public:
    static e_Multiboot_Info* get();
    void log();

private:
    void log_boot_device();
    void log_boot_modules();
    void log_drives();
    void log_memory_map();
    void log_symbol_table();
    void log_vbe();
};
