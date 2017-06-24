#include "Any.h"

union Any Any_ptr(void* ptr) {
    union Any any;
    any.ptr = ptr;
    return any;
}

union Any Any_val(intptr_t val) {
    union Any any;
    any.val = val;
    return any;
}
