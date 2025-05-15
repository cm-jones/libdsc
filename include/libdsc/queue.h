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
    void *elements;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    size_t element_size;
} dsc_queue;

/**
 * @brief Create a new queue.
 * @param element_size Size of each element in the queue.
 * @return Pointer to the created queue.
 */
dsc_queue *queue_create(size_t element_size);

// Destroy a queue
/**
 * @brief Destroy a queue.
 * @param queue Pointer to the queue to destroy.
 * @note This function frees the memory allocated for the queue and its
 * elements.
 */
void queue_destroy(dsc_queue *queue);

// Get the size of the queue
size_t queue_size(dsc_queue const *queue);

// Check if the queue is empty
bool queue_empty(dsc_queue const *queue);

// Push an element to the back of the queue
dsc_error queue_push(dsc_queue *queue, void const *element);

// Pop an element from the front of the queue
dsc_error queue_pop(dsc_queue *queue);

// Get the front element
void *queue_front(dsc_queue const *queue);

// Get the back element
void *queue_back(dsc_queue const *queue);

// Clear all elements
void queue_clear(dsc_queue *queue);

// Reserve space for n elements
dsc_error queue_reserve(dsc_queue *queue, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_QUEUE_H_
