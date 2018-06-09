#pragma once
#include <stdint.h>
#include "Err.h"

enum k_System_Stop_Mode {K_SYSTEM_HALT, K_SYSTEM_RESET};

struct k_System {
    void (*stop)(
        struct k_System* system,
        struct k_Err* err,
        enum k_System_Stop_Mode mode);
    uint8_t val[];
};

extern struct k_System* k_System_get(void);
