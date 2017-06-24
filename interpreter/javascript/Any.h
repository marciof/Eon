#pragma once
#include <stdint.h>

union Any {
    void* ptr;
    intptr_t val;
};

union Any Any_ptr(void* ptr);
union Any Any_val(intptr_t val);
