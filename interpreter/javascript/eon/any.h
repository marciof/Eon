#pragma once
#include <stdint.h>

union eon_any {
    void* ptr;
    intptr_t val;
};

union eon_any eon_any_ptr(void* ptr);
union eon_any eon_any_val(intptr_t val);
