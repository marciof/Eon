#pragma once
#include <multiboot/multiboot.h>
#include "../../core/Log.h"

/**
 * @see http://www.gnu.org/software/grub/manual/multiboot/
 */

struct multiboot_info* e_Multiboot_Info_get();
void e_Multiboot_Info_log(struct multiboot_info* info, struct e_Log* log);
