/*
 * This file is part of Data Structures for C.
 *
 * Data Structures for C is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Data Structures for C is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Data Structures for C. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_LIST_H__
#define __DSC_LIST_H__

#include <stdbool.h>

#include "dsc_error.h"

struct dsc_node_t {
    int value;
    struct dsc_node_t *next;
};

struct dsc_list_t {
    struct dsc_node_t *head;
    enum dsc_error_t error;
};

/**
 * @brief Creates a new empty linked list.
 * 
 * @return Pointer to the newly created linked list. Null on failure.
 */
struct dsc_list_t *dsc_list_create();

struct dsc_list_t *dsc_list_create_with_error(enum dsc_error_t error);

/**
 * @brief Destroys a linked list and frees the memory allocated for it.
 * 
 * @param list Pointer to the linked list to be destroyed.
 */
struct dsc_list_t *dsc_list_destroy(struct dsc_list_t *list);

// Insertion functions
/**
 * @brief Inserts a new node with the given data at the beginning of the list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be inserted.
 */
struct dsc_list_t *dsc_list_prepend(struct dsc_list_t *list, int value);

/**
 * @brief Inserts a new node with the given data at the end of the list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be inserted.
 */
struct dsc_list_t *dsc_list_append(struct dsc_list_t *list, int value);

/**
 * @brief Inserts a new node with the given data at the specified position in the list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be inserted.
 * @param position Position where the data should be inserted (0-indexed).
 */
struct dsc_list_t *dsc_list_insert(struct dsc_list_t *list, int value,
                                   int position);

/**
 * @brief Inserts a new node with the given data after the specified node in the list.
 * 
 * @param list Pointer to the linked list.
 * @param prev_node Pointer to the node after which the new node should be inserted.
 * @param data Pointer to the data to be inserted.
 */
struct dsc_list_t *dsc_list_insert_after(struct dsc_list_t *list,
                                         struct dsc_node_t *prev_node,
                                         int value);

/**
 * @brief Inserts a new node with the given data before the specified node in the list.
 * 
 * @param list Pointer to the linked list.
 * @param next_node Pointer to the node before which the new node should be inserted.
 * @param data Pointer to the data to be inserted.
 */
struct dsc_list_t *dsc_list_insert_before(struct dsc_list_t *list,
                                          struct dsc_node_t *next_node,
                                          int value);

// Deletion functions
/**
 * @brief Deletes the first node from the beginning of the list.
 * 
 * @param list Pointer to the linked list.
 */
struct dsc_list_t *dsc_list_delete_head(struct dsc_list_t *list);

/**
 * @brief Deletes the last node from the end of the list.
 * 
 * @param list Pointer to the linked list.
 */
struct dsc_list_t *dsc_list_delete_tail(struct dsc_list_t *list);

/**
 * @brief Deletes the node at the specified position in the list.
 * 
 * @param list Pointer to the linked list.
 * @param position Position of the node to be deleted (0-indexed).
 */
struct dsc_list_t *dsc_list_delete_at_position(struct dsc_list_t *list,
                                               int position);

/**
 * @brief Deletes the first occurrence of the given data from the list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be deleted.
 */
struct dsc_list_t *dsc_list_delete_value(struct dsc_list_t *list, int value);

/**
 * @brief Deletes all occurrences of the given data from the list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be deleted.
 */
struct dsc_list_t *dsc_list_delete_all(struct dsc_list_t *list, int value);

/**
 * @brief Prints the elements of the linked list.
 * 
 * @param list Pointer to the linked list.
 * @param print_func Pointer to the function used to print each data element.
 */
struct dsc_list_t *dsc_list_print(struct dsc_list_t *list);

/**
 * @brief Reverses the order of elements in the linked list.
 * 
 * @param list Pointer to the linked list.
 */
struct dsc_list_t *dsc_list_reverse(struct dsc_list_t *list);

/**
 * @brief Searches for the first occurrence of the given data in the linked list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to search for.
 * @return Pointer to the node containing the data, or NULL if not found.
 */
struct dsc_node_t *dsc_list_search(struct dsc_list_t *list, int value);

/**
 * @brief Counts the number of occurrences of the given data in the linked list.
 * 
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to count occurrences of.
 * @return Number of occurrences of the data in the list.
 */
int dsc_list_count(struct dsc_list_t *list, int value);

// Utility functions
/**
 * @brief Checks if the linked list is empty.
 * 
 * @param list Pointer to the linked list.
 * @return 1 if the list is empty, 0 otherwise.
 */
bool dsc_list_is_empty(struct dsc_list_t *list);

/**
 * @brief Returns the number of elements in the linked list.
 * 
 * @param list Pointer to the linked list.
 * @return Number of elements in the list.
 */
int dsc_list_get_length(struct dsc_list_t *list);

/**
 * @brief Returns the node at the specified position in the linked list.
 * 
 * @param list Pointer to the linked list.
 * @param position Position of the node to retrieve (0-indexed).
 * @return Pointer to the node at the specified position, or NULL if position is invalid.
 */
struct dsc_node_t *dsc_list_get_nth_node(struct dsc_list_t *list, int position);

/**
 * @brief Returns the head node of the linked list.
 * 
 * @param list Pointer to the linked list.
 * @return Pointer to the head node.
 */
struct dsc_node_t *dsc_list_get_head(struct dsc_list_t *list);

/**
 * @brief Returns the tail node of the linked list.
 * 
 * @param list Pointer to the linked list.
 * @return Pointer to the tail node.
 */
struct dsc_node_t *dsc_list_get_tail(struct dsc_list_t *list);

// Memory management functions
/**
 * @brief Initializes a new node with the given data.
 * 
 * @param data Pointer to the data to be stored in the node.
 * @return Pointer to the newly initialized node.
 */
struct dsc_node_t *dsc_node_create(int value);

/**
 * @brief Frees the memory allocated for a node.
 * 
 * @param node Pointer to the node to be freed.
 */
void dsc_node_destroy(struct dsc_node_t *node);

#endif // __DSC_LIST_H__
