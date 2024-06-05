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

#ifndef DSC_LIST_H
#define DSC_LIST_H

#include "dsc_data.h"
#include "dsc_type.h"
#include "dsc_error.h"

typedef struct DSCList DSCList;

/**
 * @brief Initialize a new list.
 *
 * @param type The data type stored in the list.
 * @return A pointer to the new list, or NULL on failure.
 */
DSCList *dsc_list_init(DSCType type);

/**
 * @brief Deinitialize a list, freeing all allocated memory.
 *
 * @param list Pointer to the list to deinitialize.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_deinit(DSCList *list);

/**
 * @brief Get the current size of the list.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the size.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_size(const DSCList *list, size_t *result);

/**
 * @brief Check if the list is empty.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_empty(const DSCList *list, bool *result);

/**
 * @brief Get the element at the front of the list.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_front(const DSCList *list, void *result);

/**
 * @brief Get the element at the back of the list.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_back(const DSCList *list, void *result);

/**
 * @brief Get the element at the specified index.
 *
 * @param list Pointer to the list.
 * @param index The index of the element.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_at(const DSCList *list, size_t index, void *result);

/**
 * @brief Push an element onto the front of the list.
 *
 * @param list Pointer to the list.
 * @param data Pointer to the element data to push.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_push_front(DSCList *list, void *data);

/**
 * @brief Pop an element from the front of the list.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the popped element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_pop_front(DSCList *list, void *result);

/**
 * @brief Push an element onto the back of the list.
 *
 * @param list Pointer to the list.
 * @param data Pointer to the element data to push.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_push_back(DSCList *list, void *data);

/**
 * @brief Pop an element from the back of the list.
 *
 * @param list Pointer to the list.
 * @param result Pointer to store the popped element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_pop_back(DSCList *list, void *result);

/**
 * @brief Insert an element at the specified index.
 *
 * @param list Pointer to the list.
 * @param data Pointer to the element data to insert.
 * @param index The index at which to insert the element.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_insert(DSCList *list, void *data, size_t index);

/**
 * @brief Erase the element at the specified index.
 *
 * @param list Pointer to the list.
 * @param index The index of the element to erase.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_list_erase(DSCList *list, size_t index);

#endif // DSC_LIST_H
