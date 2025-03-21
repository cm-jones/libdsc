// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UTILS
#define DSC_UTILS

#include <stddef.h>
#include <stdint.h>

#include "dsc_error.h"
#include "dsc_type.h"

/**
 * @brief Computes a hash value for the given key.
 *
 * @param key The key to compute the hash for.
 * @param key_type The type of the key.
 * @param capacity The capacity of the hash table.
 * @return A hash value in the range [0, capacity - 1].
 */
uint32_t dsc_hash(void *key, DSCType key_type, size_t capacity);

/**
 * @brief Returns the size in bytes of the specified data type.
 * 
 * @param type The type to get the size of.
 * @return The size in bytes of the specified type, or 0 if the type is invalid.
 */
size_t dsc_size_of(DSCType type);

/**
 * @brief Checks if the specified data type is valid.
 *
 * The dsc_type_is_valid function takes a DSCType value representing a data type
 * and returns a boolean value indicating whether the type is a valid type,
 * i.e., defined in the DSCType enum.
 *
 * @param type The DSCType value representing the data type.
 * @return true if the type is valid, false otherwise.
 */
bool dsc_type_is_valid(DSCType type);

#endif  // DSC_UTILS
