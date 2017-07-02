#pragma once
#include <stdbool.h>

#define E_BIT(pos) \
    (1 << (pos))

#define E_BIT_CLEAR(value, bit_flag) \
    ((value) & (~0 ^ (bit_flag)))

#define E_BIT_IS_SET(value, bit_flag) \
    (((value) & (bit_flag)) != 0 ? true : false)

#define E_BIT_ATTR_PACKED(type) \
    type __attribute__((__packed__))
