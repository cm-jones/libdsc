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
#include "../include/dsc_error.h"

struct dsc_list_t *dsc_list_create()
{
    struct dsc_list_t *new_list = malloc(sizeof *new_list);
    if (new_list == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_list->head = NULL;

    return new_list;
}

void dsc_list_destroy(struct dsc_list_t *list)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    struct dsc_node_t *prev = NULL;
    struct dsc_node_t *curr = list->head;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        dsc_node_destroy(prev);
    }

    free(list);
}

void dsc_list_push_front(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    new_node->next = list->head;
    list->head = new_node;
}

void dsc_list_insert_after(struct dsc_list_t *list, struct dsc_node_t *prev_node, int value)
{
    if (list == NULL || prev_node == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    struct dsc_node_t *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void dsc_list_pop_front(struct dsc_list_t *list)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_last_error(DSC_ERROR_EMPTY_LIST);
        return;
    }

    struct dsc_node_t *old_head = list->head;
    list->head = old_head->next;
    dsc_node_destroy(old_head);
}

void dsc_list_remove(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_last_error(DSC_ERROR_EMPTY_LIST);
        return;
    }

    if (list->head->value == value) {
        dsc_list_pop_front(list);
        return;
    }

    struct dsc_node_t *prev = list->head;
    struct dsc_node_t *walk = list->head->next;

    while (walk != NULL) {
        if (walk->value == value) {
            prev->next = walk->next;
            dsc_node_destroy(walk);
            return;
        }
        prev = walk;
        walk = walk->next;
    }

    dsc_set_last_error(DSC_ERROR_VALUE_NOT_FOUND);
}

void dsc_list_remove_all(struct dsc_list_t *list, int value)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_last_error(DSC_ERROR_EMPTY_LIST);
        return;
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
}

int dsc_list_front(const struct dsc_list_t *list)
{
    if (list == NULL || list->head == NULL) {
        dsc_set_last_error(DSC_ERROR_EMPTY_LIST);
        return 0;
    }

    return list->head->value;
}

bool dsc_list_empty(const struct dsc_list_t *list)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    return list->head == NULL;
}

void dsc_list_print(const struct dsc_list_t *list)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        printf("List is empty.\n");
        dsc_set_last_error(DSC_ERROR_EMPTY_LIST);
        return;
    }

    struct dsc_node_t *walk = list->head;

    while (walk != NULL) {
        printf("%d ", walk->value);
        walk = walk->next;
    }
    printf("\n");
}

struct dsc_node_t *dsc_list_get_head(const struct dsc_list_t *list)
{
    if (list == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return NULL;
    }

    return list->head;
}

struct dsc_node_t *dsc_node_create(int value)
{
    struct dsc_node_t *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
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
