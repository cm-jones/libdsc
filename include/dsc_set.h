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

/* Forward declaration of the set entry structure */
typedef struct dsc_set_entry_t dsc_set_entry_t;

/* Forward declaration of the set structure */
typedef struct DSCSet DSCSet;

/**
 * @brief Creates a new hash set.
 *
 * @return A pointer to the newly created hash set, or NULL if memory allocation fails.
 */
DSCSet *dsc_set_create(void);

/**
 * @brief Destroys the hash set and frees its memory.
 *
 * @param set The hash set to destroy.
 */
void dsc_set_free(DSCSet *set);

/**
 * @brief Inserts an element into the hash set.
 *
 * @param set The hash set to insert the element into.
 * @param value The value to insert.
 * @return true if the element was inserted successfully, false if the element already exists.
 */
bool dsc_set_insert(DSCSet *set, int value);

/**
 * @brief Erases an element from the hash set.
 *
 * @param set The hash set to erase the element from.
 * @param value The value to erase.
 * @return true if the element was erased successfully, false if the element was not found.
 */
bool dsc_set_erase(DSCSet *set, int value);

/**
 * @brief Checks if an element exists in the hash set.
 *
 * @param set The hash set to check.
 * @param value The value to check for.
 * @return true if the element exists, false otherwise.
 */
bool dsc_set_contains(const DSCSet *set, int value);

/**
 * @brief Gets the size of the hash set.
 *
 * @param set The hash set to get the size of.
 * @return The size of the hash set, -1 if the set is NULL.
 */
int dsc_set_size(const DSCSet *set);

/**
 * @brief Checks if the hash set is empty.
 *
 * @param set The hash set to check.
 * @return true if the hash set is empty, false otherwise.
 */
bool dsc_set_empty(const DSCSet *set);

/**
 * @brief Clears all elements from the hash set.
 *
 * @param set The hash set to clear.
 */
void dsc_set_clear(DSCSet *set);

#endif // __DSC_SET_H__
