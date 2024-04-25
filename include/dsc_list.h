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
#include <stddef.h>

// Forward declaration of the list structure
typedef struct DSCList *DSCList;

/**
 * @brief Creates a new list.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation fails.
 */
DSCList dsc_list_init(void);

/**
 * @brief Destroys the list and frees its memory.
 *
 * @param list The list to destroy.
 * @return true if the list was destroyed successfully, false otherwise.
 */
bool dsc_list_deinit(DSCList list);

/**
 * @brief Inserts a value at the beginning of the list.
 *
 * @param list The list to insert the value into.
 * @param value The value to insert.
 * @return true if the value was inserted successfully, false otherwise.
 */
bool dsc_list_push_front(DSCList list, int value);

/**
 * @brief Inserts a value at the end of the list.
 *
 * @param list The list to insert the value into.
 * @param value The value to insert.
 * @return true if the value was inserted successfully, false otherwise.
 */
bool dsc_list_push_back(DSCList list, int value);

/**
 * @brief Inserts a value at a specific position in the list.
 *
 * @param list The list to insert the value into.
 * @param value The value to insert.
 * @param position The position at which to insert the value.
 * @return true if the value was inserted successfully, false otherwise.
 */
bool dsc_list_insert(DSCList list, int value, int position);

/**
 * @brief Removes the first node from the list.
 *
 * @param list The list to remove the first node from.
 * @return The popped value, -1 on failure.
 */
int dsc_list_pop_front(DSCList list);

/**
 * @brief Removes the first occurrence of a value from the list.
 *
 * @param list The list to remove the value from.
 * @param value The value to remove.
 * @return true if the value was removed successfully, false otherwise.
 */
bool dsc_list_remove(DSCList list, int value);

/**
 * @brief Removes all occurrences of a value from the list.
 *
 * @param list The list to remove the values from.
 * @param value The value to remove.
 * @return true if the values were removed successfully, false otherwise.
 */
bool dsc_list_remove_all(DSCList list, int value);

/**
 * @brief Retrieves the value of the first element in the list.
 *
 * @param list The list to get the first element from.
 * @return The value of the front element, or -1 if the list is empty or NULL.
 */
int dsc_list_get_head(const DSCList list);

/**
 * @brief Retrieves the value of the last element in the list.
 *
 * @param list The list to get the last element from.
 * @return The value of the last element, or -1 if the list is empty or NULL.
 */
int dsc_list_get_tail(const DSCList list);

/**
 * @brief Gets the size of the list.
 *
 * @param list The list to get the size of.
 * @return The size of the list, or -1 if the list is NULL.
 */
int dsc_list_size(const DSCList list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list The list to check.
 * @return true if the list is empty or NULL, false otherwise.
 */
bool dsc_list_is_empty(const DSCList list);

#endif // __DSC_LIST_H__
