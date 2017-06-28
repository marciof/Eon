#pragma once
#include <multiboot/multiboot.h>
#include <stdint.h>
#include "../../core/Log.h"

// http://www.gnu.org/software/grub/manual/multiboot/
struct e_Multiboot_Info: public multiboot_info {};

struct e_Multiboot_Info* e_Multiboot_Info_get();
void e_Multiboot_Info_log(struct e_Multiboot_Info* info, struct e_Log* log);
