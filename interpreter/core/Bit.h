#pragma once
#include <stdbool.h>

#define K_BIT(pos) \
    (1 << (pos))

#define K_BIT_CLEAR(value, bit_flag) \
    ((value) & (~0 ^ (bit_flag)))

#define K_BIT_IS_SET(value, bit_flag) \
    (((value) & (bit_flag)) != 0 ? true : false)

#define K_BIT_ATTR_PACKED(type) \
    type __attribute__((__packed__))

#define K_BIT_ATTR_SECTION(name, declaration) \
    declaration __attribute__((section(name)))

#define K_BIT_ATTR_UNUSED(param) \
    param __attribute__((unused))
