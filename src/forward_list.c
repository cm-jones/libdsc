// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/forward_list.h"

#include <stdlib.h>
#include <string.h>

static forward_list_node_t *create_node(void const *element,
                                        size_t element_size) {
    forward_list_node_t *node = malloc(sizeof(forward_list_node_t));
    if (!node) {
        return NULL;
    }

    node->data = malloc(element_size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, element, element_size);
    node->next = NULL;
    return node;
}

dsc_forward_list *forward_list_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    dsc_forward_list *list = malloc(sizeof(dsc_forward_list));
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

void forward_list_destroy(dsc_forward_list *list) {
    if (!list) {
        return;
    }

    forward_list_clear(list);
    free(list);
}

size_t forward_list_size(dsc_forward_list const *list) {
    return list ? list->size : 0;
}

bool forward_list_empty(dsc_forward_list const *list) {
    return !list || list->size == 0;
}

dsc_error forward_list_push_front(dsc_forward_list *list,
                                    void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    forward_list_node_t *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    node->next = list->head;
    list->head = node;
    ++(list->size);

    return DSC_ERROR_OK;
}

dsc_error forward_list_pop_front(dsc_forward_list *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    forward_list_node_t *old_head = list->head;
    list->head = old_head->next;
    free(old_head->data);
    free(old_head);
    list->size--;

    return DSC_ERROR_OK;
}

void *forward_list_front(dsc_forward_list const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->head->data;
}

dsc_error forward_list_insert_after(dsc_forward_list *list,
                                      forward_list_node_t *pos,
                                      void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size > 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    forward_list_node_t *node = create_node(element, list->element_size);
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

dsc_error forward_list_erase_after(dsc_forward_list *list,
                                     forward_list_node_t *pos) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size > 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos && list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    forward_list_node_t *to_delete;
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

void forward_list_clear(dsc_forward_list *list) {
    if (!list) {
        return;
    }

    forward_list_node_t *current = list->head;
    while (current) {
        forward_list_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}

forward_list_node_t *forward_list_begin(dsc_forward_list const *list) {
    return list ? list->head : NULL;
}

forward_list_node_t *forward_list_end(dsc_forward_list const *list) {
    (void)list;
    return NULL;
}
