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

#include "../include/dsc_list.h"

/* Represents a node in a doubly linked list */

typedef struct DSCNode *DSCNode;

struct DSCNode {
    void *data;   /* The data stored in the node */
    DSCNode prev; /* The previous node in the list */
    DSCNode next; /* The next node in the list */
};

/* Represents a doubly linked list */

struct DSCList {
    DSCNode head;   /* The first node in the list */
    DSCNode tail;   /* The last node in the list */
    size_t size;    /* The number of elements currently in the list */
    DSCType type;   /* The type of the list elements */
    DSCError error; /* The most recent error code */
};

/* Constructor and destructor for a DSCNode. Not exposed to the user. */

static DSCNode dsc_node_init(void *data) {
    DSCNode node = malloc(sizeof *node);
    if (!node) {
        return NULL;
    }
    
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

static bool dsc_node_deinit(DSCNode node) {
    if (!node) {
        return false;
    }

    free(node->data);

    node->prev = NULL;
    node->next = NULL;

    free(node);

    return true;
}

/* Constructor and destructor for a DSCList */

DSCList dsc_list_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCList new_list = malloc(sizeof *new_list);
    if (!new_list) {
        return NULL;
    }

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    new_list->type = type;
    new_list->error = DSC_ERROR_OK;

    return new_list;
}

bool dsc_list_deinit(DSCList list) {
    if (!list) {
        return false;
    }

    if (dsc_list_is_empty(list)) {
        list->head = NULL;
        list->tail = NULL;

        free(list);

        return true;
    }

    DSCNode curr = list->head;

    // Free all the nodes in the list
    while (curr) {
        DSCNode temp = curr;
        curr = curr->next;
        dsc_node_deinit(temp);
    }

    list->head = NULL;
    list->tail = NULL;

    free(list);

    return true;
}

/* Capacity */

bool dsc_list_is_empty(const DSCList list) {
    if (!list) {
        return false;
    }

    list->error = DSC_ERROR_OK;

    return list->size == 0;
}

int dsc_list_size(const DSCList list) {
    if (!list) {
        return -1;
    }

    list->error = DSC_ERROR_OK;

    return list->size;
}

/* Element access */

void *dsc_list_front(const DSCList list) {
    if (!list) {
        return NULL;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    list->error = DSC_ERROR_OK;

    return list->head->data;
}

void *dsc_list_back(const DSCList list) {
    if (!list) {
        return NULL;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    list->error = DSC_ERROR_OK;

    return list->tail->data;
}

void *dsc_list_at(const DSCList list, size_t position) {
    if (!list) {
        return NULL;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    if (position >= list->size) {
        list->error = DSC_ERROR_OUT_OF_RANGE;
        return NULL;
    }

    size_t index = 0;

    DSCNode curr = list->head;

    while (curr) {
        if (index == position) {
            list->error = DSC_ERROR_OK;
            return curr->data;
        }

        index++;
        curr = curr->next;
    }

    // Position is >= list->size, invalid
    list->error = DSC_ERROR_OUT_OF_RANGE;

    return NULL;
}

/* Modifiers */

bool dsc_list_push_front(DSCList list, void *data) {
    if (!list) {
        return false;
    }

    if (dsc_typeof(data) != list->type) {
        list->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    DSCNode new_head = dsc_node_init(data);
    if (!new_head) {
        list->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    new_head->next = list->head;

    if (list->head) {
        list->head->prev = new_head;
    } else {
        list->tail = new_head;
    }

    list->head = new_head;
    list->size++;

    list->error = DSC_ERROR_OK;

    return true;
}

void *dsc_list_pop_front(DSCList list) {
    if (!list) {
        return NULL;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    DSCNode old_head = list->head;
    void *data = old_head->data;

    list->head = old_head->next;

    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(old_head);
    list->size--;

    list->error = DSC_ERROR_OK;

    return data;
}

bool dsc_list_push_back(DSCList list, void *data) {
    if (!list) {
        return false;
    }

    if (dsc_typeof(data) != list->type) {
        list->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    DSCNode new_tail = dsc_node_init(data);
    if (!new_tail) {
        list->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    new_tail->prev = list->tail;

    if (list->tail) {
        list->tail->next = new_tail;
    } else {
        list->head = new_tail;
    }

    list->tail = new_tail;
    list->size++;

    list->error = DSC_ERROR_OK;

    return true;
}

void *dsc_list_pop_back(DSCList list) {
    if (!list) {
        return NULL;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    DSCNode old_tail = list->tail;
    void *data = old_tail->data;

    list->tail = old_tail->prev;

    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(old_tail);
    list->size--;

    list->error = DSC_ERROR_OK;

    return data;
}

bool dsc_list_insert(DSCList list, void *data, size_t position) {
    if (!list) {
        return false;
    }

    if (dsc_typeof(data) != list->type) {
        list->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    if (position > list->size) {
        list->error = DSC_ERROR_OUT_OF_RANGE;
        return false;
    }

    if (position == 0) {
        return dsc_list_push_front(list, data);
    }

    if (position == list->size) {
        return dsc_list_push_back(list, data);
    }

    DSCNode new_node = dsc_node_init(data);
    if (!new_node) {
        list->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    size_t index = 0;
    DSCNode curr = list->head;

    while (curr) {
        if (index == position) {
            new_node->prev = curr->prev;
            new_node->next = curr;

            curr->prev->next = new_node;
            curr->prev = new_node;

            list->size++;

            list->error = DSC_ERROR_OK;

            return true;
        }

        index++;
        curr = curr->next;
    }

    // Should never reach here
    return false;
}

bool dsc_list_erase(DSCList list, size_t position) {
    if (!list) {
        return false;
    }

    if (dsc_list_is_empty(list)) {
        list->error = DSC_ERROR_EMPTY_CONTAINER;
        return false;
    }

    if (position >= list->size) {
        list->error = DSC_ERROR_OUT_OF_RANGE;
        return false;
    }

    if (position == 0) {
        dsc_list_pop_front(list);
        return true;
    }

    if (position == list->size - 1) {
        dsc_list_pop_back(list);
        return true;
    }

    size_t index = 0;
    DSCNode curr = list->head;

    while (curr) {
        if (index == position) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            free(curr);
            list->size--;

            list->error = DSC_ERROR_OK;

            return true;
        }

        index++;
        curr = curr->next;
    }

    // Should never reach here
    return false;
}

DSCError dsc_error_get(const DSCList list) {
    return list->error;
}
