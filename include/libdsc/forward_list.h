// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_FORWARD_LIST_H_
#define DSC_FORWARD_LIST_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct forward_list_node {
    void *data;
    struct forward_list_node *next;
} forward_list_node_t;

typedef struct {
    forward_list_node_t *head;
    size_t size;
    size_t element_size;
} dsc_forward_list;

// Create a new forward list
dsc_forward_list *forward_list_create(size_t element_size);

// Destroy a forward list
void forward_list_destroy(dsc_forward_list *list);

// Get the number of elements in the list
size_t forward_list_size(dsc_forward_list const *list);

// Check if the list is empty
bool forward_list_empty(dsc_forward_list const *list);

// Insert an element at the front of the list
dsc_error forward_list_push_front(dsc_forward_list *list,
                                    void const *element);

// Remove the first element from the list
dsc_error forward_list_pop_front(dsc_forward_list *list);

// Get the first element of the list
void *forward_list_front(dsc_forward_list const *list);

// Insert an element after a given position
dsc_error forward_list_insert_after(dsc_forward_list *list,
                                      forward_list_node_t *pos,
                                      void const *element);

// Remove an element after a given position
dsc_error forward_list_erase_after(dsc_forward_list *list,
                                     forward_list_node_t *pos);

// Clear all elements from the list
void forward_list_clear(dsc_forward_list *list);

// Get the first node of the list
forward_list_node_t *forward_list_begin(dsc_forward_list const *list);

// Get the end marker of the list (NULL)
forward_list_node_t *forward_list_end(dsc_forward_list const *list);

#ifdef __cplusplus
}
#endif

#endif  // DSC_FORWARD_LIST_H_
