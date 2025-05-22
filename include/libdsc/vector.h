// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file vector.h
 * @brief Dynamic array implementation similar to std::vector
 * 
 * This header provides a generic dynamic array (vector) implementation for C.
 * The vector automatically manages memory allocation and provides efficient
 * random access to elements.
 * 
 * @example
 * ```c
 * #include <libdsc/vector.h>
 * 
 * // Create a vector of integers
 * dsc_vector *vec = vector_create(sizeof(int));
 * 
 * // Add elements
 * int value = 42;
 * vector_push_back(vec, &value);
 * 
 * // Access elements
 * int *first = (int*)vector_at(vec, 0);
 * 
 * // Clean up
 * vector_destroy(vec);
 * ```
 * 
 * @author libdsc contributors
 * @version 0.1.0
 * @since 0.1.0
 */

#ifndef DSC_VECTOR_H_
#define DSC_VECTOR_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dynamic array structure
 * 
 * A generic dynamic array that can store elements of any type.
 * The vector automatically manages memory allocation and provides
 * efficient random access to elements.
 * 
 * @note This structure should be treated as opaque. Use the provided
 *       functions to interact with the vector.
 */
typedef struct dsc_vector {
    void *data;           /**< Pointer to the data buffer */
    size_t size;          /**< Number of elements currently stored */
    size_t capacity;      /**< Total capacity of the data buffer */
    size_t element_size;  /**< Size of each element in bytes */
} dsc_vector;

/**
 * @brief Creates a new vector with the specified element size
 * 
 * Allocates and initializes a new vector that can store elements of the
 * specified size. The vector starts with an initial capacity and will
 * automatically grow as needed.
 * 
 * @param element_size Size of each element in bytes (must be > 0)
 * @return Pointer to the newly created vector, or NULL on failure
 * 
 * @note The caller is responsible for calling vector_destroy() to free
 *       the allocated memory.
 * 
 * @example
 * ```c
 * // Create a vector of integers
 * dsc_vector *int_vec = vector_create(sizeof(int));
 * 
 * // Create a vector of custom structs
 * typedef struct { int x, y; } point_t;
 * dsc_vector *point_vec = vector_create(sizeof(point_t));
 * ```
 * 
 * @see vector_destroy()
 */
dsc_vector *vector_create(size_t element_size);

/**
 * @brief Destroys the vector and frees its memory
 * 
 * Deallocates all memory associated with the vector, including the data
 * buffer and the vector structure itself. After calling this function,
 * the vector pointer becomes invalid and should not be used.
 * 
 * @param vec Pointer to the vector to destroy (can be NULL)
 * 
 * @note This function is safe to call with a NULL pointer.
 * @note This function does not call destructors for stored elements.
 *       If elements require cleanup, iterate through the vector and
 *       clean up each element before calling this function.
 * 
 * @see vector_create()
 */
void vector_destroy(dsc_vector *vec);

/**
 * @brief Returns the number of elements in the vector
 * 
 * @param vec Pointer to the vector (can be NULL)
 * @return Number of elements currently stored in the vector, or 0 if vec is NULL
 * 
 * @note This operation is O(1).
 * 
 * @example
 * ```c
 * dsc_vector *vec = vector_create(sizeof(int));
 * printf("Size: %zu\n", vector_size(vec)); // Output: Size: 0
 * ```
 */
size_t vector_size(dsc_vector const *vec);

/**
 * @brief Checks if the vector is empty
 * 
 * @param vec Pointer to the vector (can be NULL)
 * @return true if the vector is empty or NULL, false otherwise
 * 
 * @note This operation is O(1).
 * @note Equivalent to `vector_size(vec) == 0`
 */
bool vector_empty(dsc_vector const *vec);

/**
 * @brief Returns the current capacity of the vector
 * 
 * The capacity is the total number of elements that can be stored
 * without requiring reallocation.
 * 
 * @param vec Pointer to the vector (can be NULL)
 * @return Current capacity of the vector, or 0 if vec is NULL
 * 
 * @note This operation is O(1).
 * @note Capacity is always >= size
 */
size_t vector_capacity(dsc_vector const *vec);

/**
 * @brief Reserves space for at least n elements
 * 
 * Ensures that the vector can hold at least n elements without
 * requiring reallocation. If n is less than or equal to the current
 * capacity, this function has no effect.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param n Minimum capacity to reserve
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully reserved space
 * @retval DSC_ERROR_INVALID_ARGUMENT vec is NULL
 * @retval DSC_ERROR_MEMORY Memory allocation failed
 * 
 * @note This function never reduces the capacity
 * @note Use this function to avoid multiple reallocations when the
 *       final size is known in advance
 */
dsc_error vector_reserve(dsc_vector *vec, size_t n);

/**
 * @brief Resizes the vector to contain n elements
 * 
 * If n is greater than the current size, the vector is expanded and
 * new elements are uninitialized. If n is less than the current size,
 * the vector is truncated.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param n New size of the vector
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully resized
 * @retval DSC_ERROR_INVALID_ARGUMENT vec is NULL
 * @retval DSC_ERROR_MEMORY Memory allocation failed (when expanding)
 * 
 * @warning New elements are uninitialized when expanding
 */
dsc_error vector_resize(dsc_vector *vec, size_t n);

/**
 * @brief Adds an element to the end of the vector
 * 
 * Appends a copy of the given element to the end of the vector.
 * The vector will automatically grow if necessary.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param element Pointer to the element to add (must not be NULL)
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully added element
 * @retval DSC_ERROR_INVALID_ARGUMENT vec or element is NULL
 * @retval DSC_ERROR_MEMORY Memory allocation failed during growth
 * 
 * @note The element is copied into the vector
 * @note This operation is amortized O(1)
 * 
 * @example
 * ```c
 * int value = 42;
 * dsc_error err = vector_push_back(vec, &value);
 * if (err != DSC_ERROR_OK) {
 *     // Handle error
 * }
 * ```
 */
dsc_error vector_push_back(dsc_vector *vec, void const *element);

/**
 * @brief Removes the last element from the vector
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully removed element
 * @retval DSC_ERROR_INVALID_ARGUMENT vec is NULL
 * @retval DSC_ERROR_EMPTY Vector is empty
 * 
 * @note This operation is O(1)
 * @note The capacity is not reduced
 */
dsc_error vector_pop_back(dsc_vector *vec);

/**
 * @brief Returns a pointer to the element at the specified index
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param index Index of the element to access
 * @return Pointer to the element, or NULL if index is out of bounds or vec is NULL
 * 
 * @note This operation is O(1)
 * @note The returned pointer may become invalid after operations that
 *       modify the vector's capacity (push_back, insert, reserve, etc.)
 * 
 * @example
 * ```c
 * int *element = (int*)vector_at(vec, 0);
 * if (element) {
 *     printf("First element: %d\n", *element);
 * }
 * ```
 */
void *vector_at(dsc_vector *vec, size_t index);

/**
 * @brief Returns a pointer to the first element
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @return Pointer to the first element, or NULL if vector is empty or NULL
 * 
 * @note This operation is O(1)
 * @note Equivalent to `vector_at(vec, 0)`
 */
void *vector_front(dsc_vector *vec);

/**
 * @brief Returns a pointer to the last element
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @return Pointer to the last element, or NULL if vector is empty or NULL
 * 
 * @note This operation is O(1)
 * @note Equivalent to `vector_at(vec, vector_size(vec) - 1)`
 */
void *vector_back(dsc_vector *vec);

/**
 * @brief Inserts an element at the specified position
 * 
 * Inserts a copy of the element at the given index, shifting existing
 * elements to the right. The vector will automatically grow if necessary.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param index Position to insert at (must be <= vector_size(vec))
 * @param element Pointer to the element to insert (must not be NULL)
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully inserted element
 * @retval DSC_ERROR_INVALID_ARGUMENT vec or element is NULL
 * @retval DSC_ERROR_NOT_FOUND index is out of bounds
 * @retval DSC_ERROR_MEMORY Memory allocation failed during growth
 * 
 * @note This operation is O(n) where n is the number of elements after index
 * @note To append to the end, use vector_push_back() which is more efficient
 */
dsc_error vector_insert(dsc_vector *vec, size_t index, void const *element);

/**
 * @brief Removes the element at the specified position
 * 
 * Removes the element at the given index, shifting subsequent elements
 * to the left.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @param index Index of the element to remove
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully removed element
 * @retval DSC_ERROR_INVALID_ARGUMENT vec is NULL
 * @retval DSC_ERROR_NOT_FOUND index is out of bounds
 * 
 * @note This operation is O(n) where n is the number of elements after index
 * @note The capacity is not reduced
 */
dsc_error vector_erase(dsc_vector *vec, size_t index);

/**
 * @brief Removes all elements from the vector
 * 
 * Removes all elements from the vector, making it empty. The capacity
 * is not changed.
 * 
 * @param vec Pointer to the vector (can be NULL)
 * 
 * @note This operation is O(1)
 * @note This function is safe to call with a NULL pointer
 * @note To also reduce capacity, call vector_shrink_to_fit() afterwards
 */
void vector_clear(dsc_vector *vec);

/**
 * @brief Reduces the capacity to match the size
 * 
 * Requests that the vector reduce its capacity to match its size.
 * This can free unused memory.
 * 
 * @param vec Pointer to the vector (must not be NULL)
 * @return DSC_ERROR_OK on success, error code on failure
 * @retval DSC_ERROR_OK Successfully reduced capacity
 * @retval DSC_ERROR_INVALID_ARGUMENT vec is NULL
 * @retval DSC_ERROR_MEMORY Memory reallocation failed
 * 
 * @note This operation may invalidate pointers to elements
 * @note This is a request; the implementation may choose not to reduce capacity
 */
dsc_error vector_shrink_to_fit(dsc_vector *vec);

#ifdef __cplusplus
}
#endif

#endif  // DSC_VECTOR_H_
