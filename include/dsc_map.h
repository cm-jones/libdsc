// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_MAP_H
#define DSC_MAP_H

#include "dsc_data.h"  
#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_MAP_INITIAL_CAPACITY 16

#define DSC_MAP_LOAD_FACTOR 0.75

typedef struct DSCMap DSCMap;

/**
 * @brief Initialize a new map.
 * 
 * @param new_map Pointer to the map to initialize.
 * @param key_type The data type of the map keys.
 * @param value_type The data type of the map values.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_init(DSCMap *new_map, DSCType key_type, DSCType value_type);

/**
 * @brief Deinitialize a map, freeing all allocated memory.
 *
 * @param map Pointer to the map to deinitialize. 
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_deinit(DSCMap *map);

/**
 * @brief Get the current size of the map.
 *
 * @param map Pointer to the map.
 * @param result Pointer to store the size.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_size(const DSCMap *map, size_t *result);

/**
 * @brief Get the current capacity of the map.
 *
 * @param map Pointer to the map.
 * @param result Pointer to store the capacity. 
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_capacity(const DSCMap *map, size_t *result);

/**
 * @brief Check if the map is empty.
 *
 * @param map Pointer to the map.
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_empty(const DSCMap *map, bool *result);

/**
 * @brief Get the value associated with the specified key.
 *
 * @param map Pointer to the map.
 * @param key Pointer to the key data.
 * @param result Pointer to store the value data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_get(const DSCMap *map, void *key, void *result);

/**
 * @brief Check if the map contains the specified key.
 *
 * @param map Pointer to the map.
 * @param key Pointer to the key data. 
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_contains(const DSCMap *map, void *key, bool *result);

/**
 * @brief Insert a key-value pair into the map.
 *
 * @param map Pointer to the map.
 * @param key Pointer to the key data.
 * @param value Pointer to the value data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_insert(DSCMap *map, void *key, void *value);

/**
 * @brief Erase the entry with the specified key from the map.
 *
 * @param map Pointer to the map.
 * @param key Pointer to the key data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_map_erase(DSCMap *map, void *key);

/**
 * @brief Clear all entries from the map.
 *
 * @param map Pointer to the map.
 * @return DSCError code indicating success or failure. 
 */
DSCError dsc_map_clear(DSCMap *map);

#endif // DSC_MAP_H
