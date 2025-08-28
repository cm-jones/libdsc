// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UNORDERED_MAP_H_
#define DSC_UNORDERED_MAP_H_

#include <stdbool.h>
#include <stddef.h>

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Hash table-based unordered map structure
///
/// A hash table that stores key-value pairs with O(1) average time
/// complexity for insertions, lookups, and deletions. Uses open
/// addressing with linear probing for collision resolution.
///
/// @note This structure should be treated as opaque.
typedef struct {
    void *keys;                                    ///< Array of keys
    void *values;                                  ///< Array of values
    size_t *hashes;                                ///< Array of hash values
    size_t size;                                   ///< Number of key-value pairs
    size_t capacity;                               ///< Total capacity
    size_t key_size;                               ///< Size of each key in bytes
    size_t value_size;                             ///< Size of each value in bytes
    size_t (*hash_fn)(void const *);               ///< Hash function for keys
    int (*compare_fn)(void const *, void const *); ///< Comparison function for keys
} DSCUnorderedMap;

/// @brief Creates a new unordered map
///
/// Allocates and initializes a new unordered map that can store key-value
/// pairs of the specified sizes using the provided hash and comparison functions.
///
/// @param key_size Size of each key in bytes (must be > 0)
/// @param value_size Size of each value in bytes (must be > 0)
/// @param hash_fn Hash function for keys (must not be NULL)
/// @param compare_fn Comparison function for keys (must not be NULL)
/// @return Pointer to the newly created map, or NULL on failure
/// @note The caller is responsible for calling unordered_map_destroy()
DSCUnorderedMap *unordered_map_create(size_t key_size, size_t value_size,
                                       size_t (*hash_fn)(void const *),
                                       int (*compare_fn)(void const *,
                                                         void const *));

/// @brief Destroys the unordered map and frees its memory
///
/// Deallocates all memory associated with the map, including the data
/// buffers and the map structure itself.
///
/// @param map Pointer to the map to destroy (can be NULL)
/// @note This function is safe to call with a NULL pointer
void unordered_map_destroy(DSCUnorderedMap *map);

/// @brief Returns the number of key-value pairs in the map
///
/// @param map Pointer to the map (can be NULL)
/// @return Number of key-value pairs currently stored, or 0 if map is NULL
/// @note This operation is O(1)
size_t unordered_map_size(DSCUnorderedMap const *map);

/// @brief Checks if the map is empty
///
/// @param map Pointer to the map (can be NULL)
/// @return true if the map is empty or NULL, false otherwise
/// @note This operation is O(1)
bool unordered_map_empty(DSCUnorderedMap const *map);

/// @brief Inserts or updates a key-value pair
///
/// Inserts a new key-value pair into the map. If the key already exists,
/// updates the associated value.
///
/// @param map Pointer to the map (must not be NULL)
/// @param key Pointer to the key to insert (must not be NULL)
/// @param value Pointer to the value to associate with the key (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully inserted or updated
/// @retval DSC_ERROR_INVALID_ARGUMENT map, key, or value is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed during growth
/// @note Average time complexity is O(1)
DSCError unordered_map_insert(DSCUnorderedMap *map, void const *key,
                               void const *value);

/// @brief Finds a value by key
///
/// Searches for the specified key and returns a pointer to its associated value.
///
/// @param map Pointer to the map (must not be NULL)
/// @param key Pointer to the key to search for (must not be NULL)
/// @return Pointer to the value if found, NULL if key not found or parameters are invalid
/// @note Average time complexity is O(1)
/// @note The returned pointer may become invalid after operations that
///       modify the map's capacity (insert, reserve, etc.)
void *unordered_map_find(DSCUnorderedMap *map, void const *key);

/// @brief Removes a key-value pair from the map
///
/// Removes the key-value pair with the specified key from the map.
///
/// @param map Pointer to the map (must not be NULL)
/// @param key Pointer to the key to remove (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed key-value pair
/// @retval DSC_ERROR_INVALID_ARGUMENT map or key is NULL
/// @retval DSC_ERROR_NOT_FOUND Key not found in map
/// @note Average time complexity is O(1)
DSCError unordered_map_erase(DSCUnorderedMap *map, void const *key);

/// @brief Removes all key-value pairs from the map
///
/// Removes all elements from the map, making it empty. The capacity
/// is not changed.
///
/// @param map Pointer to the map (can be NULL)
/// @note This function is safe to call with a NULL pointer
/// @note This operation is O(1)
void unordered_map_clear(DSCUnorderedMap *map);

/// @brief Reserves space for at least n key-value pairs
///
/// Ensures that the map can hold at least n key-value pairs without
/// requiring reallocation. If n is less than or equal to the current
/// capacity, this function has no effect.
///
/// @param map Pointer to the map (must not be NULL)
/// @param n Minimum capacity to reserve
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully reserved space
/// @retval DSC_ERROR_INVALID_ARGUMENT map is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This function never reduces the capacity
DSCError unordered_map_reserve(DSCUnorderedMap *map, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_UNORDERED_MAP_H_
