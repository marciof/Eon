#include "Any.h"

union e_Any e_Any_ptr(void* ptr) {
    union e_Any any;
    any.ptr = ptr;
    return any;
}

union e_Any e_Any_val(intptr_t val) {
    union e_Any any;
    any.val = val;
    return any;
}
