// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_QUEUE_H_
#define DSC_QUEUE_H_

#include <stdbool.h>
#include <stddef.h>

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* elements;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    size_t element_size;
} dsc_queue_t;

// Create a new queue
dsc_queue_t* queue_create(size_t element_size);

// Destroy a queue
void queue_destroy(dsc_queue_t* queue);

// Get the size of the queue
size_t queue_size(const dsc_queue_t* queue);

// Check if the queue is empty
bool queue_empty(const dsc_queue_t* queue);

// Push an element to the back of the queue
dsc_error_t queue_push(dsc_queue_t* queue, const void* element);

// Pop an element from the front of the queue
dsc_error_t queue_pop(dsc_queue_t* queue);

// Get the front element
void* queue_front(const dsc_queue_t* queue);

// Get the back element
void* queue_back(const dsc_queue_t* queue);

// Clear all elements
void queue_clear(dsc_queue_t* queue);

// Reserve space for n elements
dsc_error_t queue_reserve(dsc_queue_t* queue, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_QUEUE_H_
