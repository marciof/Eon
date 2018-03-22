#pragma once
#include <multiboot/multiboot.h>
#include "../core/Log.h"

/**
 * Multiboot Specification 0.7
 * @see http://www.gnu.org/software/grub/manual/multiboot/
 */

struct multiboot_info* k_Multiboot_get_info();
void k_Multiboot_log_info(struct multiboot_info* info, struct k_Log* log);
