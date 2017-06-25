#include "any.h"

union eon_any eon_any_ptr(void* ptr) {
    union eon_any any;
    any.ptr = ptr;
    return any;
}

union eon_any eon_any_val(intptr_t val) {
    union eon_any any;
    any.val = val;
    return any;
}
