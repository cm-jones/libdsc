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

struct DSCNode {
    int value;         // The value stored in the node
    DSCNode next;      // The next node in the list
};

struct DSCList {
    DSCNode head;      // The first node in the list
    unsigned int size; // The size of the list
};

static DSCNode dsc_node_create(int value) {
    DSCNode new_node = malloc(sizeof new_node);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;

    dsc_set_error(DSC_ERROR_NONE);
    return new_node;
}

static bool dsc_node_destroy(DSCNode node) {
    if (node == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }
    free(node);
    return true;
}

DSCList dsc_list_create(void) {
    DSCList new_list = malloc(sizeof new_list);
    if (new_list == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_list->head = NULL;
    new_list->size = 0;

    dsc_set_error(DSC_ERROR_NONE);
    return new_list;
}

bool dsc_list_destroy(DSCList list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    DSCNode prev = NULL;
    DSCNode curr = list->head;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        dsc_node_destroy(prev);
    }

    free(list);

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool dsc_list_push_front(DSCList list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    DSCNode new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    new_node->next = list->head;
    list->head = new_node;
    list->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool dsc_list_push_back(DSCList list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    DSCNode new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    if (list->head == NULL) {
        list->head = new_node;
        list->size++;

        dsc_set_error(DSC_ERROR_NONE);
        return true;
    }

    DSCNode curr = list->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
    list->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool dsc_list_insert(DSCList list, int value, int position) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (position < 0) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return false;
    }

    DSCNode new_node = dsc_node_create(value);
    if (new_node == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    DSCNode prev = NULL;
    DSCNode curr = list->head;

    while (position != 0) {
        if (curr == NULL) {
            dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
            return false;
        }

        prev = curr;
        curr = curr->next;
        position--;
    }

    prev->next = new_node;
    new_node->next = curr;
    list->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

int dsc_list_pop_front(DSCList list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return -1;
    }

    DSCNode old_head = list->head;
    int result = old_head->value;

    list->head = old_head->next;
    list->size--;
    dsc_node_destroy(old_head);

    dsc_set_error(DSC_ERROR_NONE);
    return result;
}

bool dsc_list_remove(DSCList list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return false;
    }

    if (list->head->value == value) {
        DSCNode old_head = list->head;

        list->head = old_head->next;
        list->size--;

        dsc_node_destroy(old_head);

        dsc_set_error(DSC_ERROR_NONE);
        return true;;
    }

    DSCNode prev = list->head;
    DSCNode curr = list->head->next;

    while (curr != NULL) {
        if (curr->value == value) {
            prev->next = curr->next;
            list->size--;

            dsc_node_destroy(curr);

            dsc_set_error(DSC_ERROR_NONE);
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
    return false;
}

bool dsc_list_remove_all(DSCList list, int value) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
        return false;
    }

    DSCNode prev = NULL;
    DSCNode curr = list->head;

    while (curr != NULL) {
        if (curr->value == value) {
            if (prev == NULL) {
                list->head = curr->next;
                list->size--;

                dsc_node_destroy(curr);
            } else {
                prev->next = curr->next;
                list->size--;

                dsc_node_destroy(curr);
            }

            curr = curr->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

int dsc_list_get_head(const DSCList list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return -1;
    }

    if (list->head == NULL) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->head->value;
}

int dsc_list_size(const DSCList list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->size;
}

bool dsc_list_is_empty(const DSCList list) {
    if (list == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return true;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return list->head == NULL;
}
