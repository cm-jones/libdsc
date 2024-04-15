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

#include <stdlib.h>
#include <stdbool.h>

#include "include/list.h"

struct dsc_list_t *list_create()
{
    struct dsc_list_t *new_list = malloc(sizeof new_list);
    if (new_list == NULL) {
        new_list->error = ERROR_OUT_OF_MEMORY;
        return NULL;
    }

    new_list->head = NULL;
    new_list->error = ERROR_NONE;

    return new_list;
}

struct dsc_list_t *list_destroy(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    if (list->head == NULL) {
        free(list);
        return NULL;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *curr = list->head;

    while (curr != NULL) {
        free(prev);
        prev = curr;
        curr = curr->next;
    }

    free(list);
    return NULL;
}

struct dsc_list_t *list_prepend(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *new_node = node_create(value);
    if (new_node == NULL) {
        list->error = ERROR_OUT_OF_MEMORY;
        return list;
    }

    new_node->next = list->head;
    list->head = new_node;
    list->error = ERROR_NONE;

    return list;
}

struct dsc_list_t *list_append(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *new_node = node_create(value);
    if (new_node == NULL) {
        list->error = ERROR_OUT_OF_MEMORY;
        return list;
    }

    if (list->head == NULL) {
        list->head = new_node;
        return list;
    }

    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        walk = walk->next;
    }

    walk->next = new_node;
    return list;
}

struct dsc_list_t *list_insert(struct dsc_list_t *list, int value, int position)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *new_node = node_create(value);
    if (new_node == NULL) {
        list->error = ERROR_OUT_OF_MEMORY;
        return list;
    }

    if (position == 0) {
        new_node->next = list->head;
        list->head = new_node;
        list->error = ERROR_NONE;
        return;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (position != 0) {
        prev = walk;
        walk = walk->next;
        position--;
    }

    prev->next = new_node;
    new_node->next = walk;
}

struct dsc_list_t *list_insert_after(struct dsc_list_t *list, struct dsc_node_t *prev_node,
                       int value)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *new_node = node_create(value);
    if (new_node == NULL) {
        list->error = ERROR_OUT_OF_MEMORY;
        return list;
    }
}

struct dsc_list_t *list_insert_before(struct dsc_list_t *list,
                                      struct dsc_node_t *next_node,
                                      int value)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *new_node = node_create(value);
    if (new_node == NULL) {
        list->error = ERROR_OUT_OF_MEMORY;
        return list;
    }
}

struct dsc_list_t *list_delete_head(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    if (list->head == NULL) {
        list->head = ERROR_EMPTY_LIST;
        return list;
    }

    struct dsc_node_t *old_head = list->head;
    list->head = old_head->next;
    node_destroy(old_head);

    list->error = ERROR_NONE;

    return list;
}

struct dsc_list_t *list_delete_tail(struct dsc_list_t *list)
{
    if (list == NULL || list->head == NULL) {
        return;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        prev = walk;
        walk = walk->next;
    }

    prev->next = NULL;
    node_destroy(walk);
}

struct dsc_list_t *list_delete_at_position(struct dsc_list_t *list,
                                           int position)
{

}

struct dsc_list_t *list_delete_data(struct dsc_list_t *list, int value)
{
}

struct dsc_list_t *list_delete_all(struct dsc_list_t *list, int value)
{

}

struct dsc_list_t *list_print(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    if (list->head == NULL) {
        printf("List is empty.\n");
        list->error = ERROR_EMPTY_LIST;
        return list;
    }

    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        printf(walk->value);
        walk = walk->next;
    }

    list->error = ERROR_NONE;

    return list;
}

struct dsc_list_t *list_reverse(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    if (list->head == NULL) {
        list->error = ERROR_EMPTY_LIST;
        return list;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;
    struct dsc_node_t *next = list->head->next;

    while (walk != NULL) {
        // flip the current node's 'next' pointer
        walk->next = prev;

        prev = walk;
        walk = next;
        next = next->next;
    }

    list->head = prev;
    list->error = ERROR_NONE;

    return list;
}

struct dsc_node_t *list_search(struct dsc_list_t *list, int value,
                           int (*compare_func)(int value1, int value2))
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return list;
    }

    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        if (compare_func(walk->value, value)) {
            return walk;
        }

        walk = walk->next;
    }

    return NULL;
}

int list_count(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return -1;
    }

    int count = 0;
    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        if (compare_func(walk->value, value)) {
            count++;
        }

        walk = walk->next;
    }

    list->error = ERROR_NONE;

    return count;
}

bool list_is_empty(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return true;
    }

    if (list->head == NULL) {
        list->error = ERROR_EMPTY_LIST;
        return true;
    }

    return false;
}

int list_get_length(struct dsc_list_t *list)
{
    if (list == NULL) {
        list->error = ERROR_INVALID_ARGUMENT;
        return -1;
    }

    if (list->head == NULL) {
        list->error = ERROR_EMPTY_LIST;
        return 0;
    }

    int length = 0;
    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        length++;
        walk = walk->next;
    }

    list->error = ERROR_NONE;

    return length;
}

struct dsc_node_t *list_get_nth_node(struct dsc_list_t *list, int position)
{
    if (list == NULL || position < 0) {
        return NULL;
    }

    struct dsc_node_t *walk = list->head;

    while (position != 0) {
        if (walk == NULL) {
            return NULL;
        }

        walk = walk->next;
        position--;
    }

    return walk;
}

struct dsc_node_t *list_get_head(struct dsc_list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

struct dsc_node_t *list_get_tail(struct dsc_list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        walk = walk->next;
    }

    return walk;
}

struct dsc_node_t *node_create(int value)
{
    struct dsc_node_t *new_node = malloc(sizeof new_node);
    if (new_node == NULL) {
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

struct dsc_list_t *node_destroy(struct dsc_node_t *node)
{
    free(node);
}
