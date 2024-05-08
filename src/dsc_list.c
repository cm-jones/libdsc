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
#include <string.h>

#include "../include/dsc_list.h"

typedef struct DSCNode *DSCNode;

struct DSCNode {
    DSCData data; // The data stored in the node
    DSCNode prev; // The previous node in the list
    DSCNode next; // The next node in the list
};

struct DSCList {
    DSCNode head; // The first node in the list
    DSCNode tail; // The last node in the list
    size_t size;  // The number of elements currently in the list
    DSCType type; // The type of the list elements
};

static DSCNode dsc_node_init(void *data, DSCType type) {
    DSCNode new_node = malloc(sizeof(DSCNode));
    if (new_node == NULL) {
        return NULL;
    }

    switch (type) {
        case DSC_TYPE_CHAR:
            new_node->data.c = *(char *) data;
            break;
        case DSC_TYPE_INT:
            new_node->data.i = *(int *) data;
            break;
        case DSC_TYPE_FLOAT:
            new_node->data.f = *(float *) data;
            break;
        case DSC_TYPE_DOUBLE:
            new_node->data.d = *(double *) data;
            break;
        case DSC_TYPE_STRING:
            size_t data_size = strlen(data) + 1;

            new_node->data.s = malloc(data_size);
            if (new_node->data.s == NULL) {
                free(new_node);
                return NULL;
            }

            strncpy(new_node->data.s, data, data_size - 1);
            memset(new_node->data.s + data_size - 1, '\0', 1);
            break;
        case DSC_TYPE_BOOL:
            new_node->data.b = *(bool *) data;
            break;
        default:
            free(new_node);
            return NULL;
    }

    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

static DSCError dsc_node_deinit(DSCNode node, DSCType type) {
    if (node == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (type == DSC_TYPE_STRING) {
        free(node->data.s);
        node->data.s = NULL;
    }

    node->prev = NULL;
    node->next = NULL;

    free(node);
    node = NULL;

    return DSC_ERROR_OK;
}

DSCError dsc_list_init(DSCList new_list, DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    new_list = malloc(sizeof(DSCList));
    if (new_list == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;
    new_list->type = type;

    return DSC_ERROR_OK;
}

DSCError dsc_list_deinit(DSCList list) {
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCNode curr = list->head;
    while (curr) {
        DSCNode next = curr->next;
        dsc_node_deinit(curr, list->type);
        curr = next;
    }

    free(list);
    list = NULL;

    return DSC_ERROR_OK;
}

DSCError dsc_list_size(const DSCList list, size_t *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = list->size;

    return DSC_ERROR_OK;
}

DSCError dsc_list_is_empty(const DSCList list, bool *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = list->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_list_front(const DSCList list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_CHAR:
            *(char *) result = list->head->data.c;
            break;
        case DSC_TYPE_INT: 
            *(int *) result = list->head->data.i;
            break;
        case DSC_TYPE_FLOAT:
            *(float *) result = list->head->data.f;
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) result = list->head->data.d;
            break;
        case DSC_TYPE_STRING:
            size_t result_size = strlen(list->head->data.s) + 1;
            strncpy(result, list->head->data.s, result_size - 1);
            memset(result + result_size - 1, '\0', 1);
            break;
        case DSC_TYPE_BOOL:
            *(bool *) result = list->head->data.b;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_list_back(const DSCList list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_CHAR:
            *(char *) result = list->tail->data.c;
            break;
        case DSC_TYPE_INT:
            *(int *) result = list->tail->data.i;
            break;
        case DSC_TYPE_FLOAT:
            *(float *) result = list->tail->data.f;
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) result = list->tail->data.d;
            break;
        case DSC_TYPE_STRING:
            size_t result_size = strlen(list->tail->data.s) + 1;
            strncpy(result, list->tail->data.s, result_size - 1);
            memset(result + result_size - 1, '\0', 1);
            break;
        case DSC_TYPE_BOOL:
            *(bool *) result = list->tail->data.b;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_list_at(const DSCList list, size_t position, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    if (position >= list->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    size_t index = 0;
    DSCNode curr = list->head;

    while (curr) {
        if (index == position) {
            switch (list->type) {
                case DSC_TYPE_CHAR:
                    *(char *) result = curr->data.c;
                    break;
                case DSC_TYPE_INT:
                    *(int *) result = curr->data.i;
                    break;
                case DSC_TYPE_FLOAT:
                    *(float *) result = curr->data.f;
                    break;
                case DSC_TYPE_DOUBLE:
                    *(double *) result = curr->data.d;
                    break;
                case DSC_TYPE_STRING:
                    size_t result_size = strlen(curr->data.s) + 1;
                    strncpy(result, curr->data.s, result_size - 1);
                    memset(result + result_size - 1, '\0', 1);
                    break;
                case DSC_TYPE_BOOL:
                    *(bool *) result = curr->data.b;
                    break;
                default:
                    return DSC_ERROR_INVALID_TYPE;
            }
        }

        index++;
        curr = curr->next;
    }

    // Position is >= list->size, so invalid. Should never reach here.
    return DSC_ERROR_OUT_OF_RANGE;
}

DSCError dsc_list_push_front(DSCList list, void *data) {
    if (list == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (dsc_size_of(list->type) != sizeof(*data)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    DSCNode new_head = dsc_node_init(data, list->type);
    if (new_head == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    if (list->size == 0) {
        list->head = new_head;
        list->tail = new_head;
    } else {
        new_head->next = list->head;
        list->head->prev = new_head;
        list->head = new_head;
    }

    list->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_list_pop_front(DSCList list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    DSCNode old_head = list->head;

    switch (list->type) {
        case DSC_TYPE_CHAR:
            *(char *) result = old_head->data.c;
            break;
        case DSC_TYPE_INT:
            *(int *) result = old_head->data.i;
            break;
        case DSC_TYPE_FLOAT:
            *(float *) result = old_head->data.f;
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) result = old_head->data.d;
            break;
        case DSC_TYPE_STRING:
            size_t result_size = strlen(old_head->data.s) + 1;
            strncpy(result, old_head->data.s, result_size - 1);
            memset(result + result_size - 1, '\0', 1);
            break;
        case DSC_TYPE_BOOL:
            *(bool *) result = old_head->data.b;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    list->head = old_head->next;

    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    dsc_node_deinit(old_head, list->type);
    list->size--;

    return DSC_ERROR_OK;
}

DSCError dsc_list_push_back(DSCList list, void *data) {
    if (list == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (dsc_size_of(list->type) != sizeof(*data)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    DSCNode new_tail = dsc_node_init(data, list->type);
    if (new_tail == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_tail->prev = list->tail;

    if (list->size <= 1) {
        list->head = new_tail;
    } else {
        list->tail->next = new_tail;
    }

    list->tail = new_tail;
    list->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_list_pop_back(DSCList list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    DSCNode old_tail = list->tail;
    
    switch (list->type) {
        case DSC_TYPE_CHAR:
            *(char *) result = old_tail->data.c;
            break;
        case DSC_TYPE_INT:
            *(int *) result = old_tail->data.i;
            break;
        case DSC_TYPE_FLOAT:
            *(float *) result = old_tail->data.f;
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) result = old_tail->data.d;
            break;
        case DSC_TYPE_STRING:
            size_t result_size = strlen(old_tail->data.s) + 1;
            strncpy(result, old_tail->data.s, result_size - 1);
            memset(result + result_size - 1, '\0', 1);
            break;
        case DSC_TYPE_BOOL:
            *(bool *) result = old_tail->data.b;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    list->tail = old_tail->prev;

    if (list->size > 1) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    dsc_node_deinit(old_tail, list->type);
    list->size--;

    return DSC_ERROR_OK;
}

DSCError dsc_list_insert(DSCList list, void *data, size_t position) {
    if (list == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (dsc_size_of(list->type) != sizeof(*data)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    if (position > list->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    if (position == 0) {
        return dsc_list_push_front(list, data);
    }

    if (position == list->size) {
        return dsc_list_push_back(list, data);
    }
    
    DSCNode new_node = dsc_node_init(data, list->type);
    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
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

            return DSC_ERROR_OK;
        }

        index++;
        curr = curr->next;
    }

    // Should never reach here
    return DSC_ERROR_OUT_OF_RANGE;
}

DSCError dsc_list_erase(DSCList list, size_t position) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (dsc_list_is_empty(list, NULL) == DSC_ERROR_OK) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    if (position >= list->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    // Special case: erase the first element
    if (position == 0) {
        return dsc_list_pop_front(list, NULL);
    }

    // Special case: erase the last element
    if (position == list->size - 1) {
        return dsc_list_pop_back(list, NULL);
    }

    size_t index = 0;
    DSCNode curr = list->head;

    while (curr) {
        if (index == position) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            dsc_node_deinit(curr, list->type);
            list->size--;

            return DSC_ERROR_OK;
        }

        index++;
        curr = curr->next;
    }

    // Should never reach here
    return DSC_ERROR_OUT_OF_RANGE;
}
