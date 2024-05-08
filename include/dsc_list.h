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

#include <stddef.h>
#include <stdbool.h>

#include "dsc_type.h"
#include "dsc_error.h"

/**
* @brief Represents a doubly linked list.
*/
typedef struct DSCList *DSCList;

/**
* @brief Initializes a new empty doubly linked list.
*
* @param new_list Pointer to the list to be initialized.
* @param type The type of the elements in the list.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_TYPE if the type is
*         invalid, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails.
*/
DSCError dsc_list_init(DSCList *new_list, DSCType type);

/**
* @brief Deinitializes the list and frees its memory.
*
* @param list The list to destroy.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list is
*         NULL.
*/
DSCError dsc_list_deinit(DSCList list);

/**
* @brief Checks if the list is empty.
*
* @param list The list to check.
* @param result Pointer to a bool that will be set to true if the list is
*               empty, false otherwise.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL.
*/
DSCError dsc_list_is_empty(const DSCList list, bool *result);

/**
* @brief Gets the number of elements in the list.
*
* @param list The list to get the size of.
* @param result Pointer to a size_t that will be set to the size of the list.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL.
*/
DSCError dsc_list_size(const DSCList list, size_t *result);

/**
* @brief Gets the element at the front of the list.
*
* @param list The list to get the front element from.
* @param result Pointer to a location where the front element will be copied.
* @param result_size The size of the result buffer.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_MEMORY if the result buffer is too small,
*         DSC_ERROR_INVALID_TYPE if the type of the element does not match
*         the type of the list.
*/
DSCError dsc_list_front(const DSCList list, void *result, size_t result_size);

/**
* @brief Gets the element at the back of the list.
*
* @param list The list to get the back element from.
* @param result Pointer to a location where the back element will be copied.
* @param result_size The size of the result buffer.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_MEMORY if the result buffer is too small,
*         DSC_ERROR_INVALID_TYPE if the type of the element does not match
*         the type of the list.
*/
DSCError dsc_list_back(const DSCList list, void *result, size_t result_size);

/**
* @brief Gets the element at the specified position in the list.
*
* @param list The list to get the element from.
* @param position The position of the element to get.
* @param result Pointer to a location where the element will be copied.
* @param result_size The size of the result buffer.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_RANGE if the position is out of range,
*         DSC_ERROR_OUT_OF_MEMORY if the result buffer is too small,
*         DSC_ERROR_INVALID_TYPE if the type of the element does not match
*         the type of the list.
*/
DSCError dsc_list_at(const DSCList list, size_t position, void *result,
                    size_t result_size);

/**
* @brief Inserts an element at the front of the list.
*
* @param list The list to insert the element into.
* @param data Pointer to the element to insert.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         data is NULL, DSC_ERROR_INVALID_TYPE if the type of the element does
*         not match the type of the list, DSC_ERROR_OUT_OF_MEMORY if memory
*         allocation fails.
*/
DSCError dsc_list_push_front(DSCList list, void *data);

/**
* @brief Removes the element at the front of the list.
*
* @param list The list to remove the front element from.
* @param result Pointer to a location where the removed element will be copied.
* @param result_size The size of the result buffer.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_MEMORY if the result buffer is too small,
*         DSC_ERROR_INVALID_TYPE if the type of the element does not match
*         the type of the list.
*/
DSCError dsc_list_pop_front(DSCList list, void *result, size_t result_size);

/**
* @brief Inserts an element at the back of the list.
*
* @param list The list to insert the element into.
* @param data Pointer to the element to insert.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         data is NULL, DSC_ERROR_INVALID_TYPE if the type of the element does
*         not match the type of the list, DSC_ERROR_OUT_OF_MEMORY if memory
*         allocation fails.
*/
DSCError dsc_list_push_back(DSCList list, void *data);

/**
* @brief Removes the element at the back of the list.
*
* @param list The list to remove the back element from.
* @param result Pointer to a location where the removed element will be copied.
* @param result_size The size of the result buffer.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         result is NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_MEMORY if the result buffer is too small,
*         DSC_ERROR_INVALID_TYPE if the type of the element does not match
*         the type of the list.
*/
DSCError dsc_list_pop_back(DSCList list, void *result, size_t result_size);

/**
* @brief Inserts an element at the specified position in the list.
*
* @param list The list to insert the element into.
* @param data Pointer to the element to insert.
* @param position The position at which to insert the element.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list or
*         data is NULL, DSC_ERROR_INVALID_TYPE if the type of the element does
*         not match the type of the list, DSC_ERROR_OUT_OF_RANGE if the
*         position is out of range, DSC_ERROR_OUT_OF_MEMORY if memory
*         allocation fails.
*/
DSCError dsc_list_insert(DSCList list, void *data, size_t position);

/**
* @brief Removes the element at the specified position from the list.
*
* @param list The list to remove the element from.
* @param position The position of the element to remove.
* @return DSC_ERROR_OK on success, DSC_ERROR_INVALID_ARGUMENT if the list is
*         NULL, DSC_ERROR_EMPTY_CONTAINER if the list is empty,
*         DSC_ERROR_OUT_OF_RANGE if the position is out of range.
*/
DSCError dsc_list_erase(DSCList list, size_t position);

#endif // __DSC_LIST_H__
