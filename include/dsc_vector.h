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

#ifndef __DSC_VECTOR_H__
#define __DSC_VECTOR_H__

#include <stdbool.h>

#include "../include/dsc_type.h"
#include "../include/dsc_error.h"

/**
 * @def DSC_VECTOR_INITIAL_CAPACITY
 * @brief The initial capacity of the vector.
 */
#define DSC_VECTOR_INITIAL_CAPACITY 16

/* Forward declaration of the vector structure */

typedef struct DSCVector *DSCVector;

/**
 * @brief Initializes a new DSCVector with the specified element type.
 *
 * @param type The type of elements to be stored in the vector.
 * @return A pointer to the newly created DSCVector, or NULL if initialization fails.
 */
DSCVector dsc_vector_init(DSCType type);

/**
 * @brief Deinitializes and frees the memory allocated for the DSCVector.
 *
 * @param vector The DSCVector to deinitialize.
 * @return true if deinitialization is successful, false otherwise.
 */
bool dsc_vector_deinit(DSCVector vector);

/* Capacity */

/**
 * @brief Checks if the DSCVector is empty.
 *
 * @param vector The DSCVector to check.
 * @return true if the vector is empty, false otherwise.
 */
bool dsc_vector_is_empty(const DSCVector vector);

/**
 * @brief Returns the number of elements in the DSCVector.
 *
 * @param vector The DSCVector to get the size of.
 * @return The number of elements in the vector, or -1 if the vector is NULL.
 */
int dsc_vector_size(const DSCVector vector);

/**
 * @brief Returns the current capacity of the DSCVector.
 *
 * @param vector The DSCVector to get the capacity of.
 * @return The current capacity of the vector, or -1 if the vector is NULL.
 */
int dsc_vector_capacity(const DSCVector vector);

/* Element access */

/**
 * @brief Returns the element at the specified index in the DSCVector.
 *
 * @param vector The DSCVector to access.
 * @param index The index of the element to retrieve.
 * @return A pointer to the element at the specified index, or NULL if the index is out of bounds or the vector is NULL.
 */
void *dsc_vector_at(const DSCVector vector, int index);

/**
 * @brief Returns the last element in the DSCVector.
 *
 * @param vector The DSCVector to access.
 * @return A pointer to the last element in the vector, or NULL if the vector is empty or NULL.
 */
void *dsc_vector_back(const DSCVector vector);

/* Modifiers */

/**
 * @brief Appends an element to the end of the DSCVector.
 *
 * @param vector The DSCVector to append the element to.
 * @param data The element to append.
 * @return true if the element is successfully appended, false otherwise.
 */
bool dsc_vector_push_back(DSCVector vector, void *data);

/**
 * @brief Removes the last element from the DSCVector and returns it.
 *
 * @param vector The DSCVector to remove the last element from.
 * @return A pointer to the removed element, or NULL if the vector is empty or NULL.
 */
void *dsc_vector_pop_back(DSCVector vector);

/**
 * @brief Inserts an element at the specified index in the DSCVector.
 *
 * @param vector The DSCVector to insert the element into.
 * @param data The element to insert.
 * @param index The index at which to insert the element.
 * @return true if the element is successfully inserted, false otherwise.
 */
bool dsc_vector_insert(DSCVector vector, void *data, int index);

/**
 * @brief Removes the element at the specified index from the DSCVector.
 *
 * @param vector The DSCVector to remove the element from.
 * @param index The index of the element to remove.
 * @return true if the element is successfully removed, false otherwise.
 */
bool dsc_vector_erase(DSCVector vector, int index);

/**
 * @brief Reserves the specified capacity for the DSCVector.
 *
 * @param vector The DSCVector to reserve capacity for.
 * @param new_capacity The new capacity to reserve.
 * @return true if the capacity is successfully reserved, false otherwise.
 */
bool dsc_vector_reserve(DSCVector vector, int new_capacity);

/**
 * @brief Shrinks the capacity of the DSCVector to fit its current size.
 *
 * @param vector The DSCVector to shrink.
 * @return true if the capacity is successfully shrunk, false otherwise.
 */
bool dsc_vector_shrink_to_fit(DSCVector vector);

/**
 * @brief Removes all elements from the DSCVector without deallocating the underlying memory.
 *
 * @param vector The DSCVector to clear.
 * @return true if the vector is successfully cleared, false otherwise.
 */
bool dsc_vector_clear(DSCVector vector);

/* Error handling */

/**
 * @brief Returns the most recent error code of the DSCVector.
 *
 * @param vector The DSCVector to get the error code from.
 * @return The most recent error code of the vector.
 */
DSCError dsc_vector_error(const DSCVector vector);

#endif // __DSC_VECTOR_H__
