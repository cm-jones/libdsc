// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/list.h"

#include <stdlib.h>
#include <string.h>

static list_node_t *create_node(void const *element, size_t element_size) {
    list_node_t *node = malloc(sizeof(list_node_t));
    if (!node) {
        return NULL;
    }

    node->data = malloc(element_size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, element, element_size);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

dsc_list_t *list_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    dsc_list_t *list = malloc(sizeof(dsc_list_t));
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

void list_destroy(dsc_list_t *list) {
    if (!list) {
        return;
    }

    list_clear(list);
    free(list);
}

size_t list_size(dsc_list_t const *list) { return list ? list->size : 0; }

bool list_empty(dsc_list_t const *list) { return !list || list->size == 0; }

dsc_error_t list_push_front(dsc_list_t *list, void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    list_node_t *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    ++(list->size);

    return DSC_SUCCESS;
}

dsc_error_t list_push_back(dsc_list_t *list, void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    list_node_t *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    ++(list->size);

    return DSC_SUCCESS;
}

dsc_error_t list_pop_front(dsc_list_t *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    list_node_t *old_head = list->head;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = old_head->next;
        list->head->prev = NULL;
    }

    free(old_head->data);
    free(old_head);
    list->size--;

    return DSC_SUCCESS;
}

dsc_error_t list_pop_back(dsc_list_t *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    list_node_t *old_tail = list->tail;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = old_tail->prev;
        list->tail->next = NULL;
    }

    free(old_tail->data);
    free(old_tail);
    list->size--;

    return DSC_SUCCESS;
}

void *list_front(dsc_list_t const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->head->data;
}

void *list_back(dsc_list_t const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->tail->data;
}

dsc_error_t list_insert(dsc_list_t *list, list_node_t *pos,
                        void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos) {
        return list_push_front(list, element);
    }

    list_node_t *node = create_node(element, list->element_size);
    if (!node) {
        return DSC_ERROR_MEMORY;
    }

    node->next = pos;
    node->prev = pos->prev;

    if (pos->prev) {
        pos->prev->next = node;
    } else {
        list->head = node;
    }
    pos->prev = node;

    ++(list->size);
    return DSC_SUCCESS;
}

dsc_error_t list_erase(dsc_list_t *list, list_node_t *pos) {
    if (!list || !pos) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (pos == list->head) {
        return list_pop_front(list);
    }

    if (pos == list->tail) {
        return list_pop_back(list);
    }

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    free(pos->data);
    free(pos);
    list->size--;

    return DSC_SUCCESS;
}

void list_clear(dsc_list_t *list) {
    if (!list) {
        return;
    }

    list_node_t *current = list->head;
    while (current) {
        list_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

list_node_t *list_begin(dsc_list_t const *list) {
    return list ? list->head : NULL;
}

list_node_t *list_end(dsc_list_t const *list) {
    (void)list;
    return NULL;
}

list_node_t *list_rbegin(dsc_list_t const *list) {
    return list ? list->tail : NULL;
}

list_node_t *list_rend(dsc_list_t const *list) {
    (void)list;
    return NULL;
}
