// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_VECTOR_H_
#define DSC_VECTOR_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dsc_vector_t {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} dsc_vector_t;

/**
 * @brief Creates a new vector with the specified element size.
 * @param element_size Size of each element in the vector.
 * @return Pointer to the created vector, or NULL on failure.
 */
dsc_vector_t *vector_create(size_t element_size);

/**
 * @brief Destroys the vector and frees its memory.
 * @param vec Pointer to the vector to destroy.
 */
void vector_destroy(dsc_vector_t *vec);

/**
 * @brief Returns the number of elements in the vector.
 * @param vec Pointer to the vector.
 * @return Number of elements in the vector.
 */
size_t vector_size(dsc_vector_t const *vec);

// Check if the vector is empty
/**
 * @brief Checks if the vector is empty.
 * @param vec Pointer to the vector.
 * @return true if the vector is empty, false otherwise.
 */
bool vector_empty(dsc_vector_t const *vec);

// Get the capacity of the vector
size_t vector_capacity(dsc_vector_t const *vec);

// Reserve space for n elements
dsc_error_t vector_reserve(dsc_vector_t *vec, size_t n);

// Resize the vector to contain n elements
dsc_error_t vector_resize(dsc_vector_t *vec, size_t n);

// Add an element to the end of the vector
dsc_error_t vector_push_back(dsc_vector_t *vec, void const *element);

// Remove the last element
dsc_error_t vector_pop_back(dsc_vector_t *vec);

// Get a pointer to the element at index
void *vector_at(dsc_vector_t *vec, size_t index);

// Get a pointer to the first element
void *vector_front(dsc_vector_t *vec);

// Get a pointer to the last element
void *vector_back(dsc_vector_t *vec);

// Insert an element at the specified position
dsc_error_t vector_insert(dsc_vector_t *vec, size_t index, void const *element);

// Erase an element at the specified position
dsc_error_t vector_erase(dsc_vector_t *vec, size_t index);

// Clear all elements
void vector_clear(dsc_vector_t *vec);

// Shrink the capacity to fit the size
dsc_error_t vector_shrink_to_fit(dsc_vector_t *vec);

#ifdef __cplusplus
}
#endif

#endif  // DSC_VECTOR_H_
