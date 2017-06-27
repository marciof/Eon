#pragma once

enum e_System_Stop_Mode {E_SYSTEM_HALT, E_SYSTEM_RESET};

struct e_System {
    void (*stop)(struct e_System* system, enum e_System_Stop_Mode mode);
};

extern struct e_System* e_System_get();
