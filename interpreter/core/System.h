#pragma once

enum e_System_Stop_Mode {E_SYSTEM_HALT, E_SYSTEM_RESET};

struct e_System {};

extern struct e_System* e_System_get();
extern void e_System_stop(
    struct e_System* system, enum e_System_Stop_Mode mode = E_SYSTEM_HALT);
