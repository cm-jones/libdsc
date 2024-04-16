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

#include "dsc_error.h"

/**
 * @struct dsc_node_t
 * @brief Represents a node in the linked list.
 *
 * @param value The value stored in the node.
 * @param next Pointer to the next node in the list.
 */
struct dsc_node_t {
    int value;
    struct dsc_node_t *next;
};

/**
 * @struct dsc_list_t
 * @brief Represents a linked list.
 *
 * @param head Pointer to the head node of the list.
 */
struct dsc_list_t {
    struct dsc_node_t *head;
};

/**
 * @brief Creates a new linked list.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation
 * fails.
 */
struct dsc_list_t *dsc_list_create();

/**
 * @brief Destroys the linked list and frees its memory.
 *
 * @param list The linked list to destroy.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL.
 */
enum dsc_error_t dsc_list_destroy(struct dsc_list_t *list);

/**
 * @brief Prepends a value to the linked list.
 *
 * @param list The linked list to prepend the value to.
 * @param value The value to prepend.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails.
 */
enum dsc_error_t dsc_list_prepend(struct dsc_list_t *list, int value);

/**
 * @brief Appends a value to the linked list.
 *
 * @param list The linked list to append the value to.
 * @param value The value to append.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails.
 */
enum dsc_error_t dsc_list_append(struct dsc_list_t *list, int value);

/**
 * @brief Inserts a value at a specific position in the linked list.
 *
 * @param list The linked list to insert the value into.
 * @param value The value to insert.
 * @param position The position at which to insert the value.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails,
 * DSC_ERROR_INDEX_OUT_OF_BOUNDS if the position is out of bounds.
 */
enum dsc_error_t dsc_list_insert(struct dsc_list_t *list, int value, int position);

/**
 * @brief Inserts a value before a specific node in the linked list.
 *
 * @param list The linked list to insert the value into.
 * @param next_node The node before which to insert the value.
 * @param value The value to insert.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list or
 * next_node is NULL, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails,
 * DSC_ERROR_VALUE_NOT_FOUND if the next_node is not found in the list.
 */
enum dsc_error_t dsc_list_insert_before(struct dsc_list_t *list, struct dsc_node_t *next_node, int value);

/**
 * @brief Inserts a value after a specific node in the linked list.
 *
 * @param list The linked list to insert the value into.
 * @param prev_node The node after which to insert the value.
 * @param value The value to insert.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list or
 * prev_node is NULL, DSC_ERROR_OUT_OF_MEMORY if memory allocation fails.
 */
enum dsc_error_t dsc_list_insert_after(struct dsc_list_t *list, struct dsc_node_t *prev_node, int value);

/**
 * @brief Deletes the head node of the linked list.
 *
 * @param list The linked list to delete the head from.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty.
 */
enum dsc_error_t dsc_list_delete_head(struct dsc_list_t *list);

/**
 * @brief Deletes the tail node of the linked list.
 *
 * @param list The linked list to delete the tail from.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty.
 */
enum dsc_error_t dsc_list_delete_tail(struct dsc_list_t *list);

/**
 * @brief Deletes the node at a specific position in the linked list.
 *
 * @param list The linked list to delete the node from.
 * @param position The position of the node to delete.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty
 * DSC_ERROR_INDEX_OUT_OF_BOUNDS if the position is out of bounds.
 */
enum dsc_error_t dsc_list_delete_at_position(struct dsc_list_t *list, int position);

/**
 * @brief Deletes the first occurrence of a value from the linked list.
 *
 * @param list The linked list to delete the value from.
 * @param value The value to delete.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty, SC_ERROR_VALUE_NOT_FOUND if
 * the value is not found in the list.
 */
enum dsc_error_t dsc_list_delete_value(struct dsc_list_t *list, int value);

/**
 * @brief Deletes all occurrences of a value from the linked list.
 *
 * @param list The linked list to delete the values from.
 * @param value The value to delete.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty.
 */
enum dsc_error_t dsc_list_delete_all(struct dsc_list_t *list, int value);

/**
 * @brief Prints the values of the linked list.
 *
 * @param list The linked list to print.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty.
 */
enum dsc_error_t dsc_list_print(const struct dsc_list_t *list);

/**
 * @brief Reverses the linked list.
 *
 * @param list The linked list to reverse.
 * @return DSC_ERROR_NONE on success, DSC_ERROR_INVALID_ARGUMENT if the list is
 * NULL, DSC_ERROR_EMPTY_LIST if the list is empty.
 */
enum dsc_error_t dsc_list_reverse(struct dsc_list_t *list);

/**
 * @brief Searches for a value in the linked list.
 *
 * @param list The linked list to search.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if not found or
 * if the list is NULL.
 */
struct dsc_node_t *dsc_list_search(const struct dsc_list_t *list, int value);

/**
 * @brief Counts the occurrences of a value in the linked list.
 *
 * @param list The linked list to count the occurrences in.
 * @param value The value to count.
 * @return The count of occurrences of the value in the list, or -1 if the list
 * is NULL.
 */
unsigned int dsc_list_count(const struct dsc_list_t *list, int value);

/**
 * @brief Checks if the linked list is empty.
 *
 * @param list The linked list to check.
 * @return true if the list is empty or NULL, false otherwise.
 */
bool dsc_list_is_empty(const struct dsc_list_t *list);

/**
 * @brief Gets the length of the linked list.
 *
 * @param list The linked list to get the length of.
 * @return The length of the linked list, or -1 if the list is NULL.
 */
int dsc_list_get_length(const struct dsc_list_t *list);

/**
 * @brief Gets the node at a specific position in the linked list.
 *
 * @param list The linked list to get the node from.
 * @param position The position of the node to get.
 * @return A pointer to the node at the specified position, or NULL if not
 * found or if the list is NULL.
 */
struct dsc_node_t *dsc_list_get_nth_node(const struct dsc_list_t *list,
                                         int position);

/**
 * @brief Gets the head node of the linked list.
 *
 * @param list The linked list to get the head from.
 * @return A pointer to the head node of the list, or NULL if the list is empty
 * or NULL.
 */
struct dsc_node_t *dsc_list_get_head(const struct dsc_list_t *list);

/**
 * @brief Gets the tail node of the linked list.
 *
 * @param list The linked list to get the tail from.
 * @return A pointer to the tail node of the list, or NULL if the list is empty
 * or NULL.
 */
struct dsc_node_t *dsc_list_get_tail(const struct dsc_list_t *list);

/**
 * @brief Creates a new node with the specified value.
 *
 * @param value The value to store in the node.
 * @return A pointer to the newly created node, or NULL if memory allocation
 * fails.
 */
static struct dsc_node_t *dsc_node_create(int value);

/**
 * @brief Destroys a node and frees its memory.
 *
 * @param node The node to destroy.
 */
static void dsc_node_destroy(struct dsc_node_t *node);

#endif // __DSC_LIST_H__
