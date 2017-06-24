#pragma once
#include <stddef.h>

#define REF_INC(object) \
    (++(object)->ref_count, \
    (object))

#define REF_DEC(object) \
    ((void) (--(object)->ref_count == 0 \
        ? ((object)->free((object)), NULL) \
        : NULL))

#define REF_FIELDS \
    struct { \
        size_t ref_count; \
        void (*free)(void* object); \
    }

#define REF_INIT(object, free_fn) \
    ((object)->ref_count = 1, \
    (object)->free = free_fn, \
    (object))
