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

#include <stdlib.h>
#include <stdio.h>

#include "../include/dsc_list.h"

struct dsc_list_t *dsc_list_create()
{
    struct dsc_list_t *new_list = malloc(sizeof *new_list);
    if (new_list == NULL) {
        return NULL;
    }

    new_list->head = NULL;

    return new_list;
}

enum dsc_error_t dsc_list_destroy(struct dsc_list_t *list)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        free(list);
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *curr = list->head;

    while (curr != NULL) {
        free(prev);
        prev = curr;
        curr = curr->next;
    }

    free(list);
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_prepend(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_node->next = list->head;
    list->head = new_node;

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_append(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    if (list->head == NULL) {
        list->head = new_node;
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        walk = walk->next;
    }

    walk->next = new_node;
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_insert(struct dsc_list_t *list, int value, int position)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    if (position == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (position != 0) {
        if (walk == NULL) {
            dsc_node_destroy(new_node);
            return DSC_ERROR_INDEX_OUT_OF_BOUNDS;
        }
        prev = walk;
        walk = walk->next;
        position--;
    }

    prev->next = new_node;
    new_node->next = walk;
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_insert_before(struct dsc_list_t *list,
                                        struct dsc_node_t *next_node,
                                        int value)
{
    if (list == NULL || next_node == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    if (list->head == next_node) {
        new_node->next = list->head;
        list->head = new_node;
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *prev = list->head;

    while (prev->next != next_node) {
        if (prev->next == NULL) {
            dsc_node_destroy(new_node);
            return DSC_ERROR_VALUE_NOT_FOUND;
        }
        prev = prev->next;
    }

    prev->next = new_node;
    new_node->next = next_node;

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_insert_after(struct dsc_list_t *list,
                                       struct dsc_node_t *prev_node,
                                       int value)
{
    if (list == NULL || prev_node == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_node->next = prev_node->next;
    prev_node->next = new_node;
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_delete_head(struct dsc_list_t *list)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    struct dsc_node_t *old_head = list->head;
    list->head = old_head->next;
    dsc_node_destroy(old_head);

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_delete_tail(struct dsc_list_t *list)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    if (list->head->next == NULL) {
        dsc_node_destroy(list->head);
        list->head = NULL;
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        prev = walk;
        walk = walk->next;
    }

    prev->next = NULL;
    dsc_node_destroy(walk);

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_delete_at_position(struct dsc_list_t *list,
                                             int position)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    if (position == 0) {
        struct dsc_node_t *old_head = list->head;
        list->head = list->head->next;
        dsc_node_destroy(old_head);
        return DSC_ERROR_NONE;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (position != 0) {
        if (walk == NULL) {
            return DSC_ERROR_INDEX_OUT_OF_BOUNDS;
        }
        prev = walk;
        walk = walk->next;
        position--;
    }

    if (walk == NULL) {
        return DSC_ERROR_INDEX_OUT_OF_BOUNDS;
    }

    prev->next = walk->next;
    dsc_node_destroy(walk);

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_delete_value(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    if (list->head->value == value) {
        return dsc_list_delete_head(list);
    }

    struct dsc_node_t *prev = list->head;
    struct dsc_node_t *walk = list->head->next;

    while (walk != NULL) {
        if (walk->value == value) {
            prev->next = walk->next;
            dsc_node_destroy(walk);
            return DSC_ERROR_NONE;
        }
        prev = walk;
        walk = walk->next;
    }

    return DSC_ERROR_VALUE_NOT_FOUND;
}

enum dsc_error_t dsc_list_delete_all(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        if (walk->value == value) {
            if (prev == NULL) {
                list->head = walk->next;
            } else {
                prev->next = walk->next;
            }
            struct dsc_node_t *temp = walk;
            walk = walk->next;
            dsc_node_destroy(temp);
        } else {
            prev = walk;
            walk = walk->next;
        }
    }

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_print(const struct dsc_list_t *list)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        printf("List is empty.\n");
        return DSC_ERROR_EMPTY_LIST;
    }

    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        printf("%d ", walk->value);
        walk = walk->next;
    }
    printf("\n");

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_list_reverse(struct dsc_list_t *list)
{
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->head == NULL) {
        return DSC_ERROR_EMPTY_LIST;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *walk = list->head;
    struct dsc_node_t *next = list->head->next;

    while (walk != NULL) {
        walk->next = prev;
        prev = walk;
        walk = next;
        next = next ? next->next : NULL;
    }

    list->head = prev;

    return DSC_ERROR_NONE;
}

struct dsc_node_t *dsc_list_search(const struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return NULL;
    }

    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        if (walk->value == value) {
            return walk;
        }

        walk = walk->next;
    }

    return NULL;
}

unsigned int dsc_list_count(const struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        return 0;
    }

    int count = 0;
    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        if (walk->value == value) {
            count++;
        }

        walk = walk->next;
    }

    return count;
}

bool dsc_list_is_empty(const struct dsc_list_t *list)
{
    if (list == NULL) {
        return false;
    }

    return list->head == NULL;
}

int dsc_list_get_length(const struct dsc_list_t *list)
{
    if (list == NULL) {
        return -1;
    }

    int length = 0;
    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        length++;
        walk = walk->next;
    }

    return length;
}

struct dsc_node_t *dsc_list_get_nth_node(const struct dsc_list_t *list,
                                         int position)
{
    if (list == NULL) {
        return NULL;
    }

    if (position < 0) {
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

struct dsc_node_t *dsc_list_get_head(const struct dsc_list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    return list->head;
}

struct dsc_node_t *dsc_list_get_tail(const struct dsc_list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    if (list->head == NULL) {
        return NULL;
    }

    struct dsc_node_t *walk = list->head;

    while (walk->next != NULL) {
        walk = walk->next;
    }

    return walk;
}

struct dsc_node_t *dsc_node_create(int value)
{
    struct dsc_node_t *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

void dsc_node_destroy(struct dsc_node_t *node)
{
    if (node != NULL) {
        free(node);
    }
}
