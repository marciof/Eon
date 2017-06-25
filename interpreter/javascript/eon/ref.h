#pragma once
#include <stddef.h>

#define EON_REF_INC(object) \
    (++(object)->ref_count, \
    (object))

#define EON_REF_DEC(object) \
    ((void) (((object) != NULL) && (--(object)->ref_count == 0) \
        ? ((object)->free((object)), NULL) \
        : NULL))

#define EON_REF_FIELDS \
    struct { \
        size_t ref_count; \
        void (*free)(void* object); \
    }

#define EON_REF_INIT(object, free_fn) \
    ((object)->ref_count = 1, \
    (object)->free = free_fn, \
    (object))
