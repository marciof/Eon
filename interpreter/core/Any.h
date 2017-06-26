#pragma once
#include <stdint.h>

union e_Any {
    void* ptr;
    unsigned long val;
};

#ifdef __cplusplus
extern "C" {
#endif

union e_Any e_Any_ptr(void* ptr);
union e_Any e_Any_val(unsigned long val);

#ifdef __cplusplus
}
#endif
