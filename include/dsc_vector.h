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
 * @param vector The vector to query.
 * @param result A pointer to store the size in.
 * @return DSC_ERROR_OK on success, an error code otherwise. 
 */
DSCError dsc_vector_size(const DSCVector *vector, size_t *result);

/**
 * @brief Get the current capacity of the vector.
 *
 * @param vector The vector to query.
 * @param result A pointer to store the capacity in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_capacity(const DSCVector *vector, size_t *result);

/**
 * @brief Check if the vector is currently empty.
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
 * @param vector The vector to resize.
 * @param new_capacity The new capacity for the vector. Must be greater than
 *                     the current size.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_resize(DSCVector *vector, size_t new_capacity);

/**
 * @brief Get the element at the given index.
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
 * @param vector The vector to access.
 * @param result A pointer to store the retrieved element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_front(const DSCVector *vector, void *result);

/**
 * @brief Get the last element in the vector.
 *
 * @param vector The vector to access.
 * @param result A pointer to store the retrieved element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_back(const DSCVector *vector, void *result);

/**
 * @brief Add an element to the end of the vector.
 *
 * @param vector The vector to modify.
 * @param data A pointer to the element to add.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_push_back(DSCVector *vector, void *data);

/**
 * @brief Remove the last element from the vector and return it.
 *
 * @param vector The vector to modify.
 * @param result A pointer to store the removed element in.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_pop_back(DSCVector *vector, void *result);

/**
 * @brief Insert an element into the vector at the given index.
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
 * @param vector The vector to modify.
 * @param index The index of the element to erase. Must be less than the
 *              current size.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_erase(DSCVector *vector, size_t index);

/**
 * @brief Remove all elements from the vector.
 *
 * @param vector The vector to clear.
 * @return DSC_ERROR_OK on success, an error code otherwise.
 */
DSCError dsc_vector_clear(DSCVector *vector);

#endif // DSC_VECTOR_H
