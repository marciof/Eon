#pragma once

#define CONCAT(x, y) x##y
#define CONCAT_EXPAND(x, y) CONCAT(x, y)

#define STATIC_ARRAY_LENGTH(array) \
    (sizeof(array) / sizeof((array)[0]))

#define PACKED(type) \
    type __attribute__((__packed__))

// http://www.pixelbeat.org/programming/gcc/static_assert.html
#define STATIC_ASSERT(expr, message) \
    enum {CONCAT_EXPAND(STATIC_ASSERTION_, __LINE__) = 1 / ((expr) ? 1 : 0)}
