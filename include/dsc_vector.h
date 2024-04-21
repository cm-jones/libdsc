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

/* Forward declaration of the vector structure */
typedef struct dsc_vector_t dsc_vector_t;

/**
 * @brief Creates a new empty vector.
 *
 * @return A pointer to the newly created vector, or NULL if memory allocation fails.
 */
struct dsc_vector_t *dsc_vector_create();

/**
 * @brief Destroys the vector and frees its memory.
 *
 * @param vector The vector to destroy.
 */
void dsc_vector_free(struct dsc_vector_t *vector);

/**
 * @brief Inserts an element at the end of the vector.
 *
 * @param vector The vector to push the element into.
 * @param value The value to push.
 */
void dsc_vector_push_back(struct dsc_vector_t *vector, int value);

/**
 * @brief Removes the last element from the vector.
 *
 * @param vector The vector to pop from.
 */
void dsc_vector_pop_back(struct dsc_vector_t *vector);

/**
 * @brief Inserts an element at the specified position in the vector.
 *
 * @param vector The vector to insert the element into.
 * @param position The position at which to insert the element.
 * @param value The value to insert.
 *
 * @return The position of the inserted element.
 */
size_t dsc_vector_insert(struct dsc_vector_t *vector, size_t position, int value);

/**
 * @brief Removes the element at the specified position from the vector.
 *
 * @param vector The vector to erase the element from.
 * @param position The position of the element to erase.
 */
void dsc_vector_erase(struct dsc_vector_t *vector, size_t position);

/**
 * @brief Retrieves the value of the element at the specified index.
 *
 * @param vector The vector to get the element from.
 * @param index The index of the element to retrieve.
 *
 * @return The value of the element at the specified index, or 0 if the index is out of bounds.
 */
int dsc_vector_at(const struct dsc_vector_t *vector, size_t index);

/**
 * @brief Checks if the vector is empty.
 *
 * @param vector The vector to check.
 *
 * @return true if the vector is empty, false otherwise.
 */
bool dsc_vector_empty(const struct dsc_vector_t *vector);

/**
 * @brief Gets the number of elements in the vector.
 *
 * @param vector The vector to get the size of.
 *
 * @return The number of elements in the vector, -1 if the vector is NULL.
 */
int dsc_vector_size(const struct dsc_vector_t *vector);

/**
 * @brief Gets the maximum number of elements the vector can hold before needing to allocate more memory.
 *
 * @param vector The vector to get the capacity of.
 *
 * @return The maximum number of elements the vector can hold.
 */
size_t dsc_vector_capacity(const struct dsc_vector_t *vector);

/**
 * @brief Reserves memory for the vector to hold at least the specified number of elements.
 *
 * @param vector The vector to reserve memory for.
 * @param new_capacity The minimum capacity to reserve.
 */
void dsc_vector_reserve(struct dsc_vector_t *vector, size_t new_capacity);

#endif /* __DSC_VECTOR_H__ */
