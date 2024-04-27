/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_UTILS_H__
#define __DSC_UTILS_H__

#include <stdint.h>
#include <stddef.h>

#include "dsc_type.h"

/**
 * @brief Compares two values of the specified type.
 *
 * This function compares two values of the specified type and returns an integer
 * indicating their relationship. The function supports comparison of various
 * data types defined in the DSCType enum.
 *
 * @param a Pointer to the first value.
 * @param b Pointer to the second value.
 * @param type The DSCType value representing the type of the values being compared.
 * @return An integer indicating the relationship between the values:
 *         - A negative value if a < b
 *         - Zero if a == b
 *         - A positive value if a > b
 *
 * @note The behavior is undefined if the pointers a and b do not point to valid
 *       values of the specified type. It is the caller's responsibility to ensure
 *       that the pointers are valid and the type matches the actual data type.
 */
int dsc_compare(void *a, void *b, DSCType type);

/**
 * @brief Calculates the hash value for a given key and capacity.
 *
 * This function uses a simple modulo-based hash function to calculate the hash
 * value for a given key and capacity.
 *
 * @param key The key to calculate the hash value for.
 * @param capacity The capacity of the hash set or map.
 * @return The calculated hash value.
 */
uint32_t dsc_hash(void *key, DSCType key_type, size_t capacity);

#endif // __DSC_UTILS_H__
