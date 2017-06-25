#pragma once
#include <stdint.h>

union e_Any {
    void* ptr;
    intptr_t val;
};

union e_Any e_Any_ptr(void* ptr);
union e_Any e_Any_val(intptr_t val);
