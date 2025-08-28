// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/list.h"

#include <stdlib.h>
#include <string.h>

static DSCListNode *create_node(void const *element, size_t element_size) {
    DSCListNode *node = malloc(sizeof(DSCListNode));
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

DSCList *list_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    DSCList *list = malloc(sizeof(DSCList));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->element_size = element_size;

    return list;
}

void list_destroy(DSCList *list) {
    if (list == NULL) {
        return;
    }

    list_clear(list);
    free(list);
}

size_t list_size(const DSCList *list) {
    return list ? list->size : 0;
}

bool list_empty(const DSCList *list) {
    return !list || list->size == 0;
}

DSCError list_push_front(DSCList *list, const void *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCListNode *node = create_node(element, list->element_size);
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

    return DSC_ERROR_OK;
}

DSCError list_push_back(DSCList *list, const void *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCListNode *node = create_node(element, list->element_size);
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

    return DSC_ERROR_OK;
}

DSCError list_pop_front(DSCList *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    DSCListNode *old_head = list->head;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = old_head->next;
        list->head->prev = NULL;
    }

    free(old_head->data);
    free(old_head);
    --(list->size);

    return DSC_ERROR_OK;
}

DSCError list_pop_back(DSCList *list) {
    if (!list) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (list->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    DSCListNode *old_tail = list->tail;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = old_tail->prev;
        list->tail->next = NULL;
    }

    free(old_tail->data);
    free(old_tail);
    --(list->size);

    return DSC_ERROR_OK;
}

void *list_front(DSCList const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->head->data;
}

void *list_back(DSCList const *list) {
    if (!list || list->size == 0) {
        return NULL;
    }

    return list->tail->data;
}

DSCError list_insert(DSCList *list, DSCListNode *pos, void const *element) {
    if (!list || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (!pos) {
        return list_push_front(list, element);
    }

    DSCListNode *node = create_node(element, list->element_size);
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
    return DSC_ERROR_OK;
}

DSCError list_erase(DSCList *list, DSCListNode *pos) {
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
    --(list->size);

    return DSC_ERROR_OK;
}

void list_clear(DSCList *list) {
    if (!list) {
        return;
    }

    DSCListNode *current = list->head;
    while (current) {
        DSCListNode *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

DSCListNode *list_begin(DSCList const *list) {
    return list ? list->head : NULL;
}

DSCListNode *list_end(DSCList const *list) {
    (void) list;
    return NULL;
}

DSCListNode *list_rbegin(DSCList const *list) {
    return list ? list->tail : NULL;
}

DSCListNode *list_rend(DSCList const *list) {
    (void) list;
    return NULL;
}
