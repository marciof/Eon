#pragma once

#define E_BIT_ATTR_PACKED(type) \
    type __attribute__((__packed__))

/**
 * Creates a bit.
 *
 * @param [in] position zero indexed position of the bit to create
 * @return new integer with the given bit set
 */
#define E_BIT(position) \
    (1 << (position))

#define E_FLAG_CLEAR(value, bit_flag) \
    ((value) & (~0 ^ (bit_flag)))

/**
 * Gets a bit.
 *
 * @param [in] integer integer from which to retrieve a bit
 * @param [in] position zero indexed position of the bit to retrieve
 * @return new integer with only the given bit set
 */
#define E_BIT_GET(integer, position) \
    ((integer) & E_BIT(position))

/**
 * Checks if a bit is set.
 *
 * @param [in] integer integer to be checked for
 * @param [in] position zero indexed position of the bit to check for
 * @return @c true if the given bit is set or @c false otherwise
 */
#define BIT_IS_SET(integer, position) \
    (E_BIT_GET(integer, position) != 0 ? true : false)

/**
 * Sets a bit.
 *
 * @param [in] integer integer on which to set a bit
 * @param [in] position zero indexed position of the bit to set
 * @return new integer with the given bit set
 */
#define E_BIT_SET(integer, position) \
    ((integer) | E_BIT(position))
