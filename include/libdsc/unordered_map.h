// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UNORDERED_MAP_H_
#define DSC_UNORDERED_MAP_H_

#include "libdsc/common.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* keys;
    void* values;
    size_t* hashes;
    size_t size;
    size_t capacity;
    size_t key_size;
    size_t value_size;
    size_t (*hash_fn)(const void*);
    int (*compare_fn)(const void*, const void*);
} dsc_unordered_map_t;

// Create a new unordered map
dsc_unordered_map_t* unordered_map_create(size_t key_size, size_t value_size,
                                      size_t (*hash_fn)(const void*),
                                      int (*compare_fn)(const void*,
                                                        const void*));

// Destroy an unordered map
void unordered_map_destroy(dsc_unordered_map_t* map);

// Get the size of the map
size_t unordered_map_size(const dsc_unordered_map_t* map);

// Check if the map is empty
bool unordered_map_empty(const dsc_unordered_map_t* map);

// Insert or update a key-value pair
dsc_error_t unordered_map_insert(dsc_unordered_map_t* map, const void* key,
                                  const void* value);

// Find a value by key
void* unordered_map_find(dsc_unordered_map_t* map, const void* key);

// Remove a key-value pair
dsc_error_t unordered_map_erase(dsc_unordered_map_t* map, const void* key);

// Clear all elements
void unordered_map_clear(dsc_unordered_map_t* map);

// Reserve space for n elements
dsc_error_t unordered_map_reserve(dsc_unordered_map_t* map, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_UNORDERED_MAP_H_
