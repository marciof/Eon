#pragma once
#include <stdint.h>
#include "Err.h"

struct k_System {
    void (*reset)(struct k_System* system, struct k_Err* err);
    void (*stop)(struct k_System* system, struct k_Err* err);
    uint8_t val[];
};

extern struct k_System* k_System_get(void);
