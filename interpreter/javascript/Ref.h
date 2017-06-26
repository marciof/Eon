#pragma once
#include <stddef.h>

#define E_REF_INC(object) \
    (++(object)->ref.count, \
    (object))

#define E_REF_DEC(object) \
    ((void) (((object) != NULL) && (--(object)->ref.count == 0) \
        ? ((object)->ref.free((object)), NULL) \
        : NULL))

#define E_REF_FIELD \
    struct e_Ref ref

#define E_REF_INIT(object, free_fn) \
    ((object)->ref.count = 0, \
    (object)->ref.free = free_fn, \
    E_REF_INC((object)))

struct e_Ref {
    size_t count;
    void (*free)(void* object);
};
