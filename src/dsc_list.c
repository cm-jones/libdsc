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

/* Represents a list node. */
struct DSCNode {
    int value;        /* The value stored in the node. */
    DSCNode *next; /* Pointer to the next node in the list. */
};
/* Represents a list. */
struct DSCList {
    DSCNode *head; /* Pointer to the first node in the list. */
};

static DSCNode *dsc_node_create(int value) {
    DSCNode *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;

    dsc_set_error(DSC_ERROR_NONE);
    return new_node;
}

static void dsc_node_destroy(DSCNode *node) {
    if (node != NULL) {
        free(node);
    }
}

DSCList *dsc_list_create(void) {
    DSCList *new_list = malloc(sizeof *new_list);
    if (new_list == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_list->head = NULL;

    dsc_set_error(DSC_ERROR_NONE);
    return new_list;
}

void dsc_list_destroy(DSCList *list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    DSCNode *prev = NULL;
    DSCNode *curr = list->head;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        dsc_node_destroy(prev);
    }

    free(list);
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_list_push_front(DSCList *list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    DSCNode *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    new_node->next = list->head;
    list->head = new_node;
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_list_push_back(struct DSCList *list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    DSCNode *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    DSCNode *curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_list_insert_after(DSCList *list, DSCNode *prev_node, int value) {
    if (list == NULL || prev_node == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    DSCNode *new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    new_node->next = prev_node->next;
    prev_node->next = new_node;
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_list_pop_front(DSCList *list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return;
    }

    DSCNode *old_head = list->head;
    list->head = old_head->next;
    dsc_node_destroy(old_head);
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_list_remove(DSCList *list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return;
    }

    if (list->head->value == value) {
        dsc_list_pop_front(list);
        dsc_set_error(DSC_ERROR_NONE);
        return;
    }

    DSCNode *prev = list->head;
    DSCNode *curr = list->head->next;

    while (curr != NULL) {
        if (curr->value == value) {
            prev->next = curr->next;
            dsc_node_destroy(curr);
            dsc_set_error(DSC_ERROR_NONE);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
}

void dsc_list_remove_all(DSCList *list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
        return;
    }

    DSCNode *prev = NULL;
    DSCNode *curr = list->head;

    while (curr != NULL) {
        if (curr->value == value) {
            if (prev == NULL) {
                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            DSCNode *temp = curr;
            curr = curr->next;
            dsc_node_destroy(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    dsc_set_error(DSC_ERROR_NONE);
}

int dsc_list_front(const DSCList *list) {
    if (list == NULL || list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return 0;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->head->value;
}

bool dsc_list_empty(const DSCList *list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->head == NULL;
}

void dsc_list_print(const DSCList *list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (list->head == NULL) {
        printf("List is empty.\n");
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return;
    }

    printf("[");

    DSCNode *curr = list->head;

    while (curr->next != NULL) {
        printf("%d, ", curr->value);
        curr = curr->next;
    }

    printf("%d]\n", curr->value);

    dsc_set_error(DSC_ERROR_NONE);
}

DSCNode *dsc_list_get_head(const DSCList *list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->head;
}
