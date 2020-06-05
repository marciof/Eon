#pragma once
#include <stdbool.h>

#define K_BIT(pos) \
    (1 << (pos))

#define K_BIT_CLEAR(value, bit_flag) \
    ((value) & (~0 ^ (bit_flag)))

#define K_BIT_IS_SET(value, bit_flag) \
    (((value) & (bit_flag)) != 0 ? true : false)

/**
 * @see https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html#Common-Type-Attributes
 */
#define K_BIT_PACKED(type) \
    type __attribute__((__packed__))

/**
 * @see https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 */
#define K_BIT_SECTION(name, declaration) \
    declaration __attribute__((section(name)))

#if defined(__GNUC__) || defined(__clang__)
#define K_BIT_UNUSED(param) \
    param __attribute__((unused))
#else
#define K_BIT_UNUSED(param) param
#endif
