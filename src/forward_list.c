// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/forward_list.h"

#include <stdlib.h>
#include <string.h>

static DSCForwardListNode *create_node(void const *element,
                                        size_t element_size)
{
    DSCForwardListNode *node = malloc(sizeof(DSCForwardListNode));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(element_size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->data, element, element_size);
    node->next = NULL;

    return node;
}

DSCForwardList *forward_list_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    DSCForwardList *list = malloc(sizeof(DSCForwardList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

void forward_list_destroy(DSCForwardList *list)
{
    if (list == NULL) {
        return;
    }

    forward_list_clear(list);
    free(list);
}

size_t forward_list_size(DSCForwardList const *list) {
    return list ? list->size : 0;
}

bool forward_list_empty(DSCForwardList const *list) {
    return !list || list->size == 0;
}

DSCError forward_list_push_front(DSCForwardList *list, void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCForwardListNode *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    node->next = list->head;
    list->head = node;
    ++(list->size);

    return DSC_ERROR_OK;
}

DSCError forward_list_pop_front(DSCForwardList *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    DSCForwardListNode *old_head = list->head;
    list->head = old_head->next;
    free(old_head->data);
    free(old_head);
    list->size--;

    return DSC_ERROR_OK;
}

void *forward_list_front(DSCForwardList const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->head->data;
}

DSCError forward_list_insert_after(DSCForwardList *list,
                                    DSCForwardListNode *pos,
                                    void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size > 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCForwardListNode *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    if (!pos) {
        node->next = list->head;
        list->head = node;
    } else {
        node->next = pos->next;
        pos->next = node;
    }
    ++(list->size);

    return DSC_ERROR_OK;
}

DSCError forward_list_erase_after(DSCForwardList *list,
                                   DSCForwardListNode *pos) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size > 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    DSCForwardListNode *to_delete;
    if (!pos) {
        to_delete = list->head;
        list->head = to_delete->next;
    } else {
        if (!pos->next) {
            return DSC_ERROR_INVALID_ARGUMENT;
        }
        to_delete = pos->next;
        pos->next = to_delete->next;
    }

    free(to_delete->data);
    free(to_delete);
    list->size--;

    return DSC_ERROR_OK;
}

void forward_list_clear(DSCForwardList *list) {
    if (!list) {
        return;
    }

    DSCForwardListNode *current = list->head;
    while (current) {
        DSCForwardListNode *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}

DSCForwardListNode *forward_list_begin(DSCForwardList const *list) {
    return list ? list->head : NULL;
}

DSCForwardListNode *forward_list_end(DSCForwardList const *list) {
    (void)list;
    return NULL;
}
