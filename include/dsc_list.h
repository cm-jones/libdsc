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

/* Forward declaration of the node structure. */
typedef struct DSCNode DSCNode;

/* Forward declaration of the list structure. */
typedef struct DSCList DSCList;

/**
 * @brief Creates a new list.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation
 * fails.
 */
DSCList *dsc_list_create(void);

/**
 * @brief Destroys the list and frees its memory.
 *
 * @param list The list to destroy.
 */
void dsc_list_destroy(DSCList *list);

/**
 * @brief Inserts a value at the beginning of the list.
 *
 * @param list The list to insert the value into.
 * @param value The value to insert.
 */
void dsc_list_push_front(DSCList *list, int value);

/**
 * @brief Inserts a value at the end of the list.
 *
 * @param list The list to insert the value into.
 * @param value The value to insert.
 */
void dsc_list_push_back(DSCList *list, int value);

/**
 * @brief Inserts a value after a specific node in the list.
 *
 * @param list The list to insert the value into.
 * @param prev_node The node after which to insert the value.
 * @param value The value to insert.
 */
void dsc_list_insert_after(DSCList *list, DSCNode *prev_node, int value);

/**
 * @brief Removes the first node from the list.
 *
 * @param list The list to remove the first node from.
 */
void dsc_list_pop_front(DSCList *list);

/**
 * @brief Removes the first occurrence of a value from the list.
 *
 * @param list The list to remove the value from.
 * @param value The value to remove.
 */
void dsc_list_remove(DSCList *list, int value);

/**
 * @brief Removes all occurrences of a value from the list.
 *
 * @param list The list to remove the values from.
 * @param value The value to remove.
 */
void dsc_list_remove_all(DSCList *list, int value);

/**
 * @brief Retrieves the value of the first element in the list.
 *
 * @param list The list to get the front element from.
 * @return The value of the front element, or 0 if the list is empty or NULL.
 */
int dsc_list_front(const DSCList *list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list The list to check.
 * @return true if the list is empty or NULL, false otherwise.
 */
bool dsc_list_empty(const DSCList *list);

/**
 * @brief Prints the values of the list.
 *
 * @param list The list to print.
 */
void dsc_list_print(const DSCList *list);

/**
 * @brief Gets the head node of the list.
 *
 * @param list The list to get the head from.
 * @return A pointer to the head node of the list, or NULL if the list is empty
 * or NULL.
 */
struct DSCNode *dsc_list_get_head(const DSCList *list);

#endif // __DSC_LIST_H__
