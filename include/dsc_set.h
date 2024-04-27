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

#ifndef __DSC_SET_H__
#define __DSC_SET_H__

#include <stdbool.h>

#include "dsc_type.h"
#include "dsc_error.h"

/**
 * @def DSC_SET_INITIAL_CAPACITY
 * @brief The initial capacity of the hash set.
 */
#define DSC_SET_INITIAL_CAPACITY 16

/**
 * @def DSC_SET_LOAD_FACTOR
 * @brief The load factor threshold for resizing the hash set.
 */
#define DSC_SET_LOAD_FACTOR 0.75

/* Forward declaration of the set structure */
typedef struct DSCSet *DSCSet;

/**
 * @brief Initializes a new DSCSet with the specified element type.
 *
 * @param type The type of elements to be stored in the set.
 * @return A pointer to the newly created DSCSet, or NULL if initialization fails.
 */
DSCSet dsc_set_init(DSCType type);

/**
 * @brief Deinitializes and frees the memory allocated for the DSCSet.
 *
 * @param set The DSCSet to deinitialize.
 * @return true if deinitialization is successful, false otherwise.
 */
bool dsc_set_deinit(DSCSet set);

/**
 * @brief Checks if the DSCSet is empty.
 *
 * @param set The DSCSet to check.
 * @return true if the set is empty, false otherwise.
 */
bool dsc_set_is_empty(const DSCSet set);

/**
 * @brief Returns the number of elements in the DSCSet.
 *
 * @param set The DSCSet to get the size of.
 * @return The number of elements in the set, or -1 if the set is NULL.
 */
int dsc_set_size(const DSCSet set);

/**
 * @brief Returns the current capacity of the DSCSet.
 *
 * @param set The DSCSet to get the capacity of.
 * @return The capacity of the set, or -1 if the set is NULL.
 */
int dsc_set_capacity(const DSCSet set);

/**
 * @brief Returns the current load factor of the DSCSet.
 *
 * @param set The DSCSet to get the load factor of.
 * @return The current load factor of the set, or -1.0 if the set is NULL.
 */
double dsc_set_load_factor(const DSCSet set);

/**
 * @brief Checks if the DSCSet contains the specified element.
 *
 * @param set The DSCSet to search in.
 * @param data The element to search for.
 * @return true if the element is found in the set, false otherwise.
 */
bool dsc_set_contains(const DSCSet set, void *data);

/**
 * @brief Inserts an element into the DSCSet.
 *
 * @param set The DSCSet to insert the element into.
 * @param data The element to insert.
 * @return true if the insertion is successful, false otherwise.
 */
bool dsc_set_insert(DSCSet set, void *data);

/**
 * @brief Removes an element from the DSCSet.
 *
 * @param set The DSCSet to remove the element from.
 * @param data The element to remove.
 * @return true if the removal is successful, false otherwise.
 */
bool dsc_set_erase(DSCSet set, void *data);

/**
 * @brief Removes all elements from the DSCSet.
 *
 * @param set The DSCSet to clear.
 * @return The last error code.
 */
DSCError dsc_set_error(DSCSet set);

#endif // __DSC_SET_H__
