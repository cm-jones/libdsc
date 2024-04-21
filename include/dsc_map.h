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

/* Forward declaration of the map entry structure */
typedef struct dsc_map_entry_t dsc_map_entry_t;

/* Forward declaration of the map structure */
typedef struct dsc_map_t dsc_map_t;

/**
 * @brief Creates a new empty map.
 *
 * @return A pointer to the newly created map, or NULL if memory allocation fails.
 */
dsc_map_t *dsc_map_create();

/**
 * @brief Destroys the map and frees its memory.
 *
 * @param map The map to destroy.
 */
void dsc_map_free(dsc_map_t *map);

/**
 * @brief Inserts a key-value pair into the map.
 *
 * @param map The map to insert the key-value pair into.
 * @param key The key to insert.
 * @param value The value to associate with the key.
 *
 * @return true if the key-value pair was inserted successfully, false if the key already exists.
 */
bool dsc_map_insert(dsc_map_t *map, int key, int value);

/**
 * @brief Erases the key-value pair with the given key from the map.
 *
 * @param map The map to erase the key-value pair from.
 * @param key The key to erase.
 *
 * @return true if the key-value pair was erased successfully, false if the key was not found.
 */
bool dsc_map_erase(dsc_map_t *map, int key);

/**
 * @brief Retrieves the value associated with the given key.
 *
 * @param map The map to retrieve the value from.
 * @param key The key to retrieve the value for.
 *
 * @return The value associated with the key, or 0 if the key is not found.
 */
int dsc_map_get(const dsc_map_t *map, int key);

/**
 * @brief Checks if the map contains the given key.
 *
 * @param map The map to check.
 * @param key The key to check for.
 *
 * @return true if the key exists in the map, false otherwise.
 */
bool dsc_map_contains(const dsc_map_t *map, int key);

/**
 * @brief Gets the number of key-value pairs in the map.
 *
 * @param map The map to get the size of.
 *
 * @return The number of key-value pairs in the map, -1 if the map is NULL.
 */
int dsc_map_size(const dsc_map_t *map);

/**
 * @brief Checks if the map is empty.
 *
 * @param map The map to check.
 *
 * @return true if the map is empty, false otherwise.
 */
bool dsc_map_empty(const dsc_map_t *map);

/**
 * @brief Clears all key-value pairs from the map.
 *
 * @param map The map to clear.
 */
void dsc_map_clear(dsc_map_t *map);

#endif /* __DSC_MAP_H__ */
