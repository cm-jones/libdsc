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
#include <stddef.h>

/**
 * @def DSC_VECTOR_INITIAL_CAPACITY
 * @brief The initial capacity of the vector.
 */
#define DSC_VECTOR_INITIAL_CAPACITY 16

// Forward declaration of the vector structure
typedef struct DSCVector *DSCVector;

/**
 * @brief Creates a new empty vector.
 *
 * @return A pointer to the newly created vector, or NULL if memory allocation fails.
 */
DSCVector DSCVector_create(void);

/**
 * @brief Destroys the vector and frees its memory.
 *
 * @param vector The vector to destroy.
 * @return true if the vector was destroyed successfully, false otherwise.
 */
bool DSCVector_free(DSCVector vector);

/**
 * @brief Inserts an element at the end of the vector.
 *
 * @param vector The vector to push the element into.
 * @param value The value to push.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool DSCVector_push_back(DSCVector vector, int value);

/**
 * @brief Removes the last element from the vector.
 *
 * @param vector The vector to pop from.
 * @return true if the element was popped successfully, false otherwise.
 */
bool DSCVector_pop_back(DSCVector vector);

/**
 * @brief Inserts an element at the specified position in the vector.
 *
 * @param vector The vector to insert the element into.
 * @param value The value to insert.
 * @param position The position at which to insert the element.
 * @return true if the element was inserted successfully, false otherwise.
 */
bool DSCVector_insert(DSCVector vector, int value, int position);

/**
 * @brief Removes the element at the specified position from the vector.
 *
 * @param vector The vector to erase the element from.
 * @param position The position of the element to erase.
 * @return true if the element was removed successfully, false otherwise.
 */
bool DSCVector_erase(DSCVector vector, int position);

/**
 * @brief Retrieves the value of the element at the specified index.
 *
 * @param vector The vector to get the element from.
 * @param index The index of the element to retrieve.
 *
 * @return The value of the element at the specified index, or -1 if the vector is NULL or the index is out of bounds.
 */
int DSCVector_at(const DSCVector vector, int index);

/**
 * @brief Checks if the vector is empty.
 *
 * @param vector The vector to check.
 *
 * @return true if the vector is empty, false otherwise.
 */
bool DSCVector_is_empty(const DSCVector vector);

/**
 * @brief Gets the number of elements in the vector.
 *
 * @param vector The vector to get the size of.
 *
 * @return The number of elements in the vector, -1 if the vector is NULL.
 */
int DSCVector_size(const DSCVector vector);

/**
 * @brief Gets the maximum number of elements the vector can hold before needing to allocate more memory.
 *
 * @param vector The vector to get the capacity of.
 *
 * @return The maximum number of elements the vector can hold, or -1 if the vector is NULL.
 */
int DSCVector_capacity(const DSCVector vector);

/**
 * @brief Reserves memory for the vector to hold at least the specified number of elements.
 *
 * @param vector The vector to reserve memory for.
 * @param new_capacity The minimum capacity to reserve.
 * 
 * @return true if the operation was successful, false otherwise.
 */
bool DSCVector_reserve(DSCVector vector, int new_capacity);

#endif // __DSC_VECTOR_H__
