// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file dsc_vector.h
 * @brief Dynamic array implementation.
 */

#ifndef DSC_VECTOR_H
#define DSC_VECTOR_H

#include "dsc_data.h"
#include "dsc_type.h"
#include "dsc_error.h"

/**
 * @brief A dynamic array of elements.
 *
 * A DSCVector is a dynamic array that can grow or shrink as needed. It 
 * stores elements of a single type, specified when the vector is initialized.
 */
typedef struct DSCVector DSCVector;

/**
 * @brief The initial capacity of a newly initialized vector.
 */
#define DSC_VECTOR_INITIAL_CAPACITY 16

/**
 * @brief Initialize a new vector with the given element type.
 *
 * @param vector The vector to initialize.
 * @param type The type of elements the vector will contain.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_init(DSCVector *vector, DSCType type);

/**
 * @brief Deinitialize a vector, freeing all allocated memory.
 *
 * @param vector The vector to deinitialize.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_deinit(DSCVector *vector);

/**
 * @brief Get the current size of the vector.
 *
 * The size of the vector is the number of elements currently stored in it.
 *
 * @param vector The vector to query.
 * @param result A pointer to store the size in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_size(const DSCVector *vector, size_t *result);

/**
 * @brief Get the current capacity of the vector.
 *
 * The capacity of the vector is the number of elements it can store before 
 * it needs to resize its internal memory.
 *
 * @param vector The vector to query.
 * @param result A pointer to store the capacity in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_capacity(const DSCVector *vector, size_t *result);

/**
 * @brief Check if the vector is currently empty.
 *
 * A vector is considered empty if its size is 0.
 * 
 * @param vector The vector to query.
 * @param result A pointer to store the result in. Will be true if the vector
 *               is empty, false otherwise.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_empty(const DSCVector *vector, bool *result);

/**
 * @brief Resize the capacity of the vector.
 *
 * This function will resize the vector's internal memory to the given capacity.
 * If the new capacity is smaller than the vector's current size, the vector
 * will be truncated and elements will be lost.
 *
 * @param vector The vector to resize.
 * @param new_capacity The new capacity for the vector. Must be greater than
 *                     the current size.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_resize(DSCVector *vector, size_t new_capacity);

/**
 * @brief Get the element at the given index.
 *
 * This function retrieves the element at the specified index in the vector.
 * The index must be less than the vector's current size.
 *
 * @param vector The vector to access.
 * @param index The index of the element to retrieve. Must be less than the 
 *              current size.
 * @param result A pointer to store the retrieved element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_at(const DSCVector *vector, size_t index, void *result);

/**
 * @brief Get the first element in the vector.
 *
 * This is equivalent to calling dsc_vector_at with an index of 0.
 * 
 * @param vector The vector to access.
 * @param result A pointer to store the retrieved element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_front(const DSCVector *vector, void *result);

/**
 * @brief Get the last element in the vector.
 *
 * This is equivalent to calling dsc_vector_at with an index of size - 1.
 *
 * @param vector The vector to access.
 * @param result A pointer to store the retrieved element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_back(const DSCVector *vector, void *result);

/**
 * @brief Add an element to the end of the vector.
 *
 * This function appends the given element to the end of the vector,
 * increasing its size by 1. If the new size exceeds the vector's current
 * capacity, the vector will be automatically resized.
 *
 * @param vector The vector to modify.
 * @param data A pointer to the element to add.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_push_back(DSCVector *vector, void *data);

/**
 * @brief Remove the last element from the vector and return it.
 *
 * This function removes the last element from the vector, decreasing its size
 * by 1, and returns the removed element through the result pointer.
 *
 * @param vector The vector to modify.
 * @param result A pointer to store the removed element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_pop_back(DSCVector *vector, void *result);

/**
 * @brief Insert an element into the vector at the given index.
 *
 * This function inserts the given element into the vector at the specified
 * index, shifting all subsequent elements one position to the right. The index
 * must be less than or equal to the vector's current size.
 *
 * @param vector The vector to modify.
 * @param data A pointer to the element to insert.
 * @param index The index to insert the element at. Must be less than or equal
 *              to the current size.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_insert(DSCVector *vector, void *data, size_t index);

/**
 * @brief Erase the element at the given index.
 *
 * This function removes the element at the specified index from the vector,
 * shifting all subsequent elements one position to the left. The index must
 * be less than the vector's current size.
 *
 * @param vector The vector to modify.
 * @param index The index of the element to erase. Must be less than the
 *              current size.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_erase(DSCVector *vector, size_t index);

/**
 * @brief Remove all elements from the vector.
 *
 * This function removes all elements from the vector, setting its size to 0.
 * The vector's capacity is not changed.
 *
 * @param vector The vector to clear.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_clear(DSCVector *vector);

#endif // DSC_VECTOR_H
