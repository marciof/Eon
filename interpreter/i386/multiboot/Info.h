#pragma once
#include <multiboot/multiboot.h>
#include <stdint.h>
#include "../../core/Log.h"

// http://www.gnu.org/software/grub/manual/multiboot/
struct e_Multiboot_Info: public multiboot_info {
    void log_boot_device(struct e_Log* log);
    void log_boot_modules(struct e_Log* log);
    void log_drives(struct e_Log* log);
    void log_memory_map(struct e_Log* log);
    void log_symbol_table(struct e_Log* log);
    void log_vbe(struct e_Log* log);
};

struct e_Multiboot_Info* e_Multiboot_Info_get();
void e_Multiboot_Info_log(struct e_Multiboot_Info* info, struct e_Log* log);
