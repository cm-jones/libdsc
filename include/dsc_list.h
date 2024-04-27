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

#ifndef __DSC_LIST_H__
#define __DSC_LIST_H__

#include <stdbool.h>

#include "dsc_type.h"
#include "dsc_error.h"

typedef struct DSCList *DSCList;

/**
 * @brief Creates a new empty doubly linked list.
 *
 * @param type The type of the elements in the list.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation fails.
 */
DSCList dsc_list_init(DSCType type);

/**
 * @brief Destroys the list and frees its memory.
 *
 * @param list The list to destroy.
 *
 * @return true if the list was successfully destroyed, false otherwise.
 */
bool dsc_list_deinit(DSCList list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list The list to check.
 *
 * @return true if the list is empty, false otherwise.
 */
bool dsc_list_is_empty(const DSCList list);

/**
 * @brief Gets the number of elements in the list.
 *
 * @param list The list to get the size of.
 *
 * @return The number of elements in the list, or -1 if the list is NULL.
 */
int dsc_list_size(const DSCList list);

/**
 * @brief Gets the element at the front of the list.
 *
 * @param list The list to get the front element from.
 *
 * @return A pointer to the front element, or NULL if the list is empty or NULL.
 */
void *dsc_list_front(const DSCList list);

/**
 * @brief Gets the element at the back of the list.
 *
 * @param list The list to get the back element from.
 *
 * @return A pointer to the back element, or NULL if the list is empty or NULL.
 */
void *dsc_list_back(const DSCList list);

/**
 * @brief Gets the element at the specified position in the list.
 *
 * @param list The list to get the element from.
 * @param position The position of the element to get.
 *
 * @return A pointer to the element at the specified position, or NULL if the
 *         position is out of range or the list is empty or NULL.
 */
void *dsc_list_at(const DSCList list, size_t position);

/**
 * @brief Inserts an element at the front of the list.
 *
 * @param list The list to insert the element into.
 * @param data A pointer to the element to insert.
 *
 * @return true if the element was successfully inserted, false otherwise.
 */
bool dsc_list_push_front(DSCList list, void *data);

/**
 * @brief Removes the element at the front of the list.
 *
 * @param list The list to remove the front element from.
 *
 * @return A pointer to the removed element, or NULL if the list is empty or NULL.
 */
void *dsc_list_pop_front(DSCList list);

/**
 * @brief Inserts an element at the back of the list.
 *
 * @param list The list to insert the element into.
 * @param data A pointer to the element to insert.
 *
 * @return true if the element was successfully inserted, false otherwise.
 */
bool dsc_list_push_back(DSCList list, void *data);

/**
 * @brief Removes the element at the back of the list.
 *
 * @param list The list to remove the back element from.
 *
 * @return A pointer to the removed element, or NULL if the list is empty or NULL.
 */
void *dsc_list_pop_back(DSCList list);

/**
 * @brief Inserts an element at the specified position in the list.
 *
 * @param list The list to insert the element into.
 * @param data A pointer to the element to insert.
 * @param position The position at which to insert the element.
 *
 * @return true if the element was successfully inserted, false otherwise.
 */
bool dsc_list_insert(DSCList list, void *data, size_t position);

/**
 * @brief Removes the element at the specified position from the list.
 *
 * @param list The list to remove the element from.
 * @param position The position of the element to remove.
 *
 * @return true if the element was successfully removed, false otherwise.
 */
bool dsc_list_erase(DSCList list, size_t position);

/**
 * @brief Retrieves the last error code.
 *
 * @param list The list to get the error code from.
 *
 * @return The last error code.
 */
DSCError dsc_error_get(const DSCList list);

#endif // __DSC_LIST_H__
