// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/queue.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static dsc_error grow(dsc_queue *queue) {
    size_t new_capacity = queue->capacity * 2;
    void *new_elements = malloc(new_capacity * queue->element_size);

    if (!new_elements) return DSC_ERROR_MEMORY;

    // Copy elements from front to back
    if (queue->front <= queue->back) {
        memcpy(new_elements,
               (char *)queue->elements + queue->front * queue->element_size,
               queue->size * queue->element_size);
    } else {
        // Copy elements from front to end
        size_t first_part = queue->capacity - queue->front;
        memcpy(new_elements,
               (char *)queue->elements + queue->front * queue->element_size,
               first_part * queue->element_size);

        // Copy elements from start to back
        memcpy((char *)new_elements + first_part * queue->element_size,
               queue->elements, queue->back * queue->element_size);
    }

    free(queue->elements);
    queue->elements = new_elements;
    queue->capacity = new_capacity;
    queue->front = 0;
    queue->back = queue->size;

    return DSC_ERROR_OK;
}

dsc_queue *queue_create(size_t element_size) {
    dsc_queue *queue = malloc(sizeof(dsc_queue));
    if (!queue) return NULL;

    queue->capacity = INITIAL_CAPACITY;
    queue->size = 0;
    queue->front = 0;
    queue->back = 0;
    queue->element_size = element_size;

    queue->elements = malloc(queue->capacity * element_size);
    if (!queue->elements) {
        free(queue);
        return NULL;
    }

    return queue;
}

void queue_destroy(dsc_queue *queue) {
    if (!queue) return;
    free(queue->elements);
    free(queue);
}

size_t queue_size(dsc_queue const *queue) { return queue ? queue->size : 0; }

bool queue_empty(dsc_queue const *queue) {
    return !queue || queue->size == 0;
}

dsc_error queue_push(dsc_queue *queue, void const *element) {
    if (!queue || !element) return DSC_ERROR_INVALID_ARGUMENT;

    if (queue->size == queue->capacity) {
        dsc_error err = grow(queue);
        if (err != DSC_ERROR_OK) return err;
    }

    memcpy((char *)queue->elements + queue->back * queue->element_size, element,
           queue->element_size);

    queue->back = (queue->back + 1) % queue->capacity;
    ++(queue->size);

    return DSC_ERROR_OK;
}

dsc_error queue_pop(dsc_queue *queue) {
    if (!queue) return DSC_ERROR_INVALID_ARGUMENT;
    if (queue->size == 0) return DSC_ERROR_EMPTY;

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return DSC_ERROR_OK;
}

void *queue_front(dsc_queue const *queue) {
    if (!queue || queue->size == 0) return NULL;
    return (char *)queue->elements + queue->front * queue->element_size;
}

void *queue_back(dsc_queue const *queue) {
    if (!queue || queue->size == 0) return NULL;
    size_t back = (queue->back + queue->capacity - 1) % queue->capacity;
    return (char *)queue->elements + back * queue->element_size;
}

void queue_clear(dsc_queue *queue) {
    if (!queue) return;
    queue->front = 0;
    queue->back = 0;
    queue->size = 0;
}

dsc_error queue_reserve(dsc_queue *queue, size_t n) {
    if (!queue) return DSC_ERROR_INVALID_ARGUMENT;
    if (n <= queue->capacity) return DSC_ERROR_OK;

    void *new_elements = malloc(n * queue->element_size);
    if (!new_elements) return DSC_ERROR_MEMORY;

    // Copy elements from front to back
    if (queue->front <= queue->back) {
        memcpy(new_elements,
               (char *)queue->elements + queue->front * queue->element_size,
               queue->size * queue->element_size);
    } else {
        // Copy elements from front to end
        size_t first_part = queue->capacity - queue->front;
        memcpy(new_elements,
               (char *)queue->elements + queue->front * queue->element_size,
               first_part * queue->element_size);

        // Copy elements from start to back
        memcpy((char *)new_elements + first_part * queue->element_size,
               queue->elements, queue->back * queue->element_size);
    }

    free(queue->elements);
    queue->elements = new_elements;
    queue->capacity = n;
    queue->front = 0;
    queue->back = queue->size;

    return DSC_ERROR_OK;
}
