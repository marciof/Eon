/**
 * Timestamps aren't currently supported, and so it prints a monotonically
 * increasing fixed-upper-bound integer (may overflow and wrap-around).
 */

#pragma once
#include "../../core/Log.h"

void k_VGA_Log_init(struct k_Log* log);
