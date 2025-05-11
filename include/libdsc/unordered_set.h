// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UNORDERED_SET_H_
#define DSC_UNORDERED_SET_H_

#include "libdsc/common.h"

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* elements;
    size_t* hashes;
    size_t size;
    size_t capacity;
    size_t element_size;
    size_t (*hash_fn)(const void*);
    int (*compare_fn)(const void*, const void*);
} dsc_unordered_set_t;

// Create a new unordered set
dsc_unordered_set_t* unordered_set_create(size_t element_size,
                                      size_t (*hash_fn)(const void*),
                                      int (*compare_fn)(const void*,
                                                        const void*));

// Destroy an unordered set
void unordered_set_destroy(dsc_unordered_set_t* set);

// Get the size of the set
size_t unordered_set_size(const dsc_unordered_set_t* set);

// Check if the set is empty
bool unordered_set_empty(const dsc_unordered_set_t* set);

// Insert an element
dsc_error_t unordered_set_insert(dsc_unordered_set_t* set, const void* element);

// Find an element
void* unordered_set_find(dsc_unordered_set_t* set, const void* element);

// Remove an element
dsc_error_t unordered_set_erase(dsc_unordered_set_t* set, const void* element);

// Clear all elements
void unordered_set_clear(dsc_unordered_set_t* set);

// Reserve space for n elements
dsc_error_t unordered_set_reserve(dsc_unordered_set_t* set, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_UNORDERED_SET_H_
