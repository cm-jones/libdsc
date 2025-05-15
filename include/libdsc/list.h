// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_LIST_H_
#define DSC_LIST_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_node {
    void *data;
    struct list_node *prev;
    struct list_node *next;
} list_node_t;

typedef struct {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
    size_t element_size;
} dsc_list;

// Create a new list
dsc_list *list_create(size_t element_size);

// Destroy a list
void list_destroy(dsc_list *list);

// Get the number of elements in the list
size_t list_size(dsc_list const *list);

// Check if the list is empty
bool list_empty(dsc_list const *list);

// Insert an element at the front of the list
dsc_error list_push_front(dsc_list *list, void const *element);

// Insert an element at the back of the list
dsc_error list_push_back(dsc_list *list, void const *element);

// Remove the first element from the list
dsc_error list_pop_front(dsc_list *list);

// Remove the last element from the list
dsc_error list_pop_back(dsc_list *list);

// Get the first element of the list
void *list_front(dsc_list const *list);

// Get the last element of the list
void *list_back(dsc_list const *list);

// Insert an element before a given position
dsc_error list_insert(dsc_list *list, list_node_t *pos,
                        void const *element);

// Remove an element at a given position
dsc_error list_erase(dsc_list *list, list_node_t *pos);

// Clear all elements from the list
void list_clear(dsc_list *list);

// Get the first node of the list
list_node_t *list_begin(dsc_list const *list);

// Get the end marker of the list (NULL)
list_node_t *list_end(dsc_list const *list);

// Get the last node of the list
list_node_t *list_rbegin(dsc_list const *list);

// Get the reverse end marker of the list (NULL)
list_node_t *list_rend(dsc_list const *list);

#ifdef __cplusplus
}
#endif

#endif  // DSC_LIST_H_
