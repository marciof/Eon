#pragma once
#include <stddef.h>

#define K_REF_INC(object) \
    (++(object)->ref.count, \
    (object))

#define K_REF_DEC(object) \
    ((void) (((object) != NULL) && (--(object)->ref.count == 0) \
        ? ((object)->ref.free((object)), NULL) \
        : NULL))

#define K_REF_FIELD \
    struct k_Ref ref

#define K_REF_INIT(object, free_fn) \
    ((object)->ref.count = 0, \
    (object)->ref.free = (free_fn), \
    K_REF_INC((object)))

struct k_Ref {
    size_t count;
    void (*free)(void* object);
};
