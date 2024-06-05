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

#include "../include/dsc_list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct DSCNode DSCNode;

struct DSCNode {
    DSCData data;   // The data stored in the node
    DSCNode *prev;  // The previous node in the list
    DSCNode *next;  // The next node in the list
};

struct DSCList {
    DSCNode *head;  // The first node in the list
    DSCNode *tail;  // The last node in the list
    size_t size;    // The number of nodes currently in the list
    DSCType type;   // The type of the data stored in the list
};

static DSCError dsc_node_init(DSCNode *new_node, void *value, DSCType type) {
    if (new_node == NULL || value == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (dsc_type_invalid(type)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    new_node = malloc(sizeof(DSCNode));

    if (new_node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    switch (type) {
        case DSC_TYPE_BOOL:
            new_node->data.b = *(bool *) value;
            break;

        case DSC_TYPE_CHAR:
            new_node->data.c = *(char *) value;
            break;

        case DSC_TYPE_INT:
            new_node->data.i = *(int *) value;
            break;

        case DSC_TYPE_FLOAT:
            new_node->data.f = *(float *) value;
            break;

        case DSC_TYPE_DOUBLE:
            new_node->data.d = *(double *) value;
            break;

        case DSC_TYPE_STRING: {
            const char *str = *(char **) value;
            size_t str_size = strlen(str) + 1;

            new_node->data.s = malloc(str_size);
            if (new_node->data.s == NULL) {
                free(new_node);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(new_node->data.s, value, str_size);
            new_node->data.s[str_size] = '\0';
            break;
        }

        default:
            free(new_node);
            return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_node->prev = NULL;
    new_node->next = NULL;

    return DSC_ERROR_OK;
}

static DSCError dsc_node_deinit(DSCNode *node, DSCType type) {
    if (node == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
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

DSCList *dsc_list_init(DSCType type) {
    if (dsc_type_invalid(type)) {
        return NULL;
    }

    DSCList *list = malloc(sizeof(DSCList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->type = type;

    return list;
}

DSCError dsc_list_deinit(DSCList *list) {
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCNode *curr = list->head;

    while (curr) {
        DSCNode *next = curr->next;
        dsc_node_deinit(curr, list->type);
        curr = next;
    }

    free(list);
    list = NULL;

    return DSC_ERROR_OK;
}

DSCError dsc_list_size(const DSCList *list, size_t *result) {
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = list->size;

    return DSC_ERROR_OK;
}

DSCError dsc_list_empty(const DSCList *list, bool *result) {
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = list->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_list_front(const DSCList *list, void *front) {
    if (list == NULL || front == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_BOOL:
            *(bool *) front = list->head->data.b;
            break;

        case DSC_TYPE_CHAR:
            *(char *) front = list->head->data.c;
            break;

        case DSC_TYPE_INT:
            *(int *) front = list->head->data.i;
            break;

        case DSC_TYPE_FLOAT:
            *(float *) front = list->head->data.f;
            break;

        case DSC_TYPE_DOUBLE:
            *(double *) front = list->head->data.d;
            break;

        case DSC_TYPE_STRING: {
            const char *s = list->head->data.s;
            size_t size = strlen(s);

            char *temp = malloc(size + 1);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, s, size);
            temp[size] = '\0';

            *(char **) front = temp;

            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_list_back(const DSCList *list, void *back) {
    if (list == NULL || back == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_BOOL:
            *(bool *) back = list->tail->data.b;
            break;

        case DSC_TYPE_CHAR:
            *(char *) back = list->tail->data.c;
            break;

        case DSC_TYPE_INT:
            *(int *) back = list->tail->data.i;
            break;

        case DSC_TYPE_FLOAT:
            *(float *) back = list->tail->data.f;
            break;

        case DSC_TYPE_DOUBLE:
            *(double *) back = list->tail->data.d;
            break;

        case DSC_TYPE_STRING: {
            const char *s = list->tail->data.s;
            size_t size = strlen(s);

            char *temp = malloc(size + 1);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, s, size);
            temp[size] = '\0';

            *(char **) back = temp;

            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_list_at(const DSCList *list, size_t position, void *result) {
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
    DSCNode *curr = list->head;

    while (curr) {
        if (index == position) {
            switch (list->type) {
                case DSC_TYPE_BOOL:
                    *(bool *) result = curr->data.b;
                    break;

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

                case DSC_TYPE_STRING: {
                    const char *s = curr->data.s;
                    size_t size = strlen(s);

                    char *temp = malloc(size + 1);
                    if (temp == NULL) {
                        return DSC_ERROR_OUT_OF_MEMORY;
                    }

                    strncpy(temp, s, size);
                    temp[size] = '\0';

                    *(char **) result = temp;

                    break;
                }

                default:
                    return DSC_ERROR_INVALID_TYPE;
            }

            return DSC_ERROR_OK;
        }

        index++;
        curr = curr->next;
    }

    // Position is >= list->size, should never reach here
    return DSC_ERROR_OUT_OF_RANGE;
}

DSCError dsc_list_push_front(DSCList *list, void *to_push) {
    if (list == NULL || to_push == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCNode *new_head = NULL;
    DSCError errno = dsc_node_init(new_head, to_push, list->type);
    if (errno != DSC_ERROR_OK) {
        return errno;
    }

    if (list->size == 0) {
        list->head = new_head;
        list->tail = new_head;
        list->size++;
        return DSC_ERROR_OK;
    }

    // Link the new head to the old head
    new_head->next = list->head;
    list->head->prev = new_head;

    // Update the head of the list
    list->head = new_head;
    list->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_list_pop_front(DSCList *list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_BOOL:
            *(bool *) result = list->head->data.b;
            break;

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

        case DSC_TYPE_STRING: {
            const char *s = list->head->data.s;
            size_t size = strlen(s);

            char *temp = malloc(size + 1);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, s, size);
            temp[size] = '\0';

            *(char **) result = temp;

            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    DSCNode *old_head = list->head;
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

DSCError dsc_list_push_back(DSCList *list, void *to_push) {
    if (list == NULL || to_push == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCNode *new_tail = NULL;
    DSCError errno = dsc_node_init(new_tail, to_push, list->type);
    if (errno != DSC_ERROR_OK) {
        return errno;
    }

    if (list->size == 0) {
        list->head = new_tail;
        list->tail = new_tail;
        list->size++;

        return DSC_ERROR_OK;
    }

    list->tail->next = new_tail;
    new_tail->prev = list->tail;

    list->tail = new_tail;
    list->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_list_pop_back(DSCList *list, void *result) {
    if (list == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (list->type) {
        case DSC_TYPE_BOOL:
            *(bool *) result = list->tail->data.b;
            break;

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

        case DSC_TYPE_STRING: {
            const char *s = list->tail->data.s;
            size_t size = strlen(s);

            char *temp = malloc(size + 1);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, s, size);
            temp[size] = '\0';

            *(char **) result = temp;

            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    DSCNode *old_tail = list->tail;

    list->tail = old_tail->prev;
    list->tail->next = NULL;

    dsc_node_deinit(old_tail, list->type);

    list->size--;

    return DSC_ERROR_OK;
}

DSCError dsc_list_insert(DSCList *list, void *data, size_t position) {
    if (list == NULL) {
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

    DSCNode *new_node = NULL;
    DSCError errno = dsc_node_init(new_node, data, list->type);
    if (errno != DSC_ERROR_OK) {
        return errno;
    }

    size_t index = 0;
    DSCNode *curr = list->head;

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

DSCError dsc_list_erase(DSCList *list, size_t position) {
    if (list == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
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
    DSCNode *curr = list->head;

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
