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

#ifndef __DSC_MAP_H__
#define __DSC_MAP_H__

#include <stdbool.h>
#include <stddef.h>

#include "dsc_type.h"
#include "dsc_error.h"

/**
 * @def DSC_MAP_INITIAL_CAPACITY
 * @brief The initial capacity of the hash map.
 */
#define DSC_MAP_INITIAL_CAPACITY 16

/**
 * @def DSC_MAP_LOAD_FACTOR
 * @brief The load factor threshold for resizing the hash map.
 */
#define DSC_MAP_LOAD_FACTOR 0.75

/* Forward declaration of the map structure */

typedef struct DSCMap *DSCMap;

/**
 * @brief Initializes a new DSCMap with the specified key and value types.
 * @param key_type The type of the keys in the map.
 * @param value_type The type of the values in the map.
 * @return A pointer to the newly created DSCMap, or NULL if an error occurred.
 */
DSCMap dsc_map_init(DSCType key_type, DSCType value_type);

/**
 * @brief Frees the memory allocated for the DSCMap.
 * @param map The DSCMap to free.
 * @return true if the operation was successful, false otherwise.
 */
bool dsc_map_deinit(DSCMap map);

/**
 * @brief Checks if the DSCMap is empty.
 * @param map The DSCMap to check.
 * @return true if the map is empty, false otherwise.
 */
bool dsc_map_is_empty(const DSCMap map);

/**
 * @brief Returns the number of elements in the DSCMap.
 * @param map The DSCMap to get the size of.
 * @return The number of elements in the map, or -1 if an error occurred.
 */
int dsc_map_size(const DSCMap map);

/**
 * @brief Retrieves the value associated with the specified key from the DSCMap.
 * @param map The DSCMap to retrieve the value from.
 * @param key The key to retrieve the associated value of.
 * @return The value associated with the key, or NULL if the key was not found or an error occurred.
 */
void *dsc_map_get(const DSCMap map, void *key);

/**
 * @brief Checks if the DSCMap contains the specified key.
 * @param map The DSCMap to check.
 * @param key The key to look for.
 * @return true if the key was found, false otherwise.
 */
bool dsc_map_contains(const DSCMap map, void *key);

/**
 * @brief Inserts a new key-value pair into the DSCMap.
 * @param map The DSCMap to insert the key-value pair into.
 * @param key The key of the new entry.
 * @param value The value associated with the key.
 * @return true if the operation was successful, false otherwise.
 */
bool dsc_map_insert(DSCMap map, void *key, void *value);

/**
 * @brief Erases the entry with the specified key from the DSCMap.
 * @param map The DSCMap to erase the entry from.
 * @param key The key of the entry to erase.
 * @return true if the operation was successful, false otherwise.
 */
bool dsc_map_erase(DSCMap map, void *key);

/**
 * @brief Erases all the entries from the DSCMap.
 * @param map The DSCMap to clear.
 * @return true if the operation was successful, false otherwise.
 */
bool dsc_map_clear(DSCMap map);

/**
 * @brief Retrieves the most recent error code from the DSCMap.
 * @param map The DSCMap to retrieve the error code from.
 * @return The most recent error code.
 */
DSCError dsc_map_error(const DSCMap map);

#endif // __DSC_MAP_H__
