/**
 * Multiboot Specification 0.7
 * @see http://www.gnu.org/software/grub/manual/multiboot/
 */

#pragma once
#include <multiboot/multiboot.h>
#include "../core/Log.h"

struct multiboot_info* k_Multiboot_get_info(struct k_Err* err);
void k_Multiboot_log_info(
    struct multiboot_info* info, struct k_Err* err, struct k_Log* log);
