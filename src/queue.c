// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/queue.h"

#include <stdlib.h>
#include <string.h>

#define DSC_QUEUE_INITIAL_CAPACITY 16

static DSCError grow(DSCQueue *queue) {
    size_t new_capacity;
    if (!dsc_safe_grow_capacity(queue->capacity, &new_capacity)) {
        return DSC_ERROR_OVERFLOW;
    }

    size_t new_size;
    if (!dsc_safe_multiply(new_capacity, queue->element_size, &new_size)) {
        return DSC_ERROR_OVERFLOW;
    }

    void *new_elements = dsc_malloc(new_size);

    if (!new_elements) return DSC_ERROR_MEMORY;

    // Copy elements from front to back
    if (queue->front <= queue->back) {
        size_t front_offset, copy_size;
        if (!dsc_safe_multiply(queue->front, queue->element_size,
                               &front_offset) ||
            !dsc_safe_multiply(queue->size, queue->element_size, &copy_size)) {
            dsc_free(new_elements);
            return DSC_ERROR_OVERFLOW;
        }
        memcpy(new_elements, (char *)queue->elements + front_offset, copy_size);
    } else {
        // Copy elements from front to end
        size_t first_part = queue->capacity - queue->front;
        size_t front_offset, first_part_size, first_part_offset, back_size;
        if (!dsc_safe_multiply(queue->front, queue->element_size,
                               &front_offset) ||
            !dsc_safe_multiply(first_part, queue->element_size,
                               &first_part_size) ||
            !dsc_safe_multiply(first_part, queue->element_size,
                               &first_part_offset) ||
            !dsc_safe_multiply(queue->back, queue->element_size, &back_size)) {
            dsc_free(new_elements);
            return DSC_ERROR_OVERFLOW;
        }
        memcpy(new_elements, (char *)queue->elements + front_offset,
               first_part_size);

        // Copy elements from start to back
        memcpy((char *)new_elements + first_part_offset, queue->elements,
               back_size);
    }

    dsc_free(queue->elements);
    queue->elements = new_elements;
    queue->capacity = new_capacity;
    queue->front = 0;
    queue->back = queue->size;

    return DSC_ERROR_OK;
}

DSCQueue *queue_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    DSCQueue *queue = dsc_malloc(sizeof(DSCQueue));
    if (!queue) return NULL;

    queue->capacity = DSC_QUEUE_INITIAL_CAPACITY;
    queue->size = 0;
    queue->front = 0;
    queue->back = 0;
    queue->element_size = element_size;

    size_t initial_size;
    if (!dsc_safe_multiply(queue->capacity, element_size, &initial_size)) {
        dsc_free(queue);
        return NULL;
    }

    queue->elements = dsc_malloc(initial_size);
    if (!queue->elements) {
        dsc_free(queue);
        return NULL;
    }

    return queue;
}

void queue_destroy(DSCQueue *queue) {
    if (!queue) return;
    dsc_free(queue->elements);
    dsc_free(queue);
}

size_t queue_size(DSCQueue const *queue) { return queue ? queue->size : 0; }

bool queue_empty(DSCQueue const *queue) { return !queue || queue->size == 0; }

DSCError queue_push(DSCQueue *queue, void const *element) {
    if (!queue || !element) return DSC_ERROR_INVALID_ARGUMENT;

    if (queue->size == queue->capacity) {
        DSCError err = grow(queue);
        if (err != DSC_ERROR_OK) return err;
    }

    size_t back_offset;
    if (!dsc_safe_multiply(queue->back, queue->element_size, &back_offset)) {
        return DSC_ERROR_OVERFLOW;
    }
    memcpy((char *)queue->elements + back_offset, element, queue->element_size);

    queue->back = (queue->back + 1) % queue->capacity;
    ++(queue->size);

    return DSC_ERROR_OK;
}

DSCError queue_pop(DSCQueue *queue) {
    if (!queue) return DSC_ERROR_INVALID_ARGUMENT;
    if (queue->size == 0) return DSC_ERROR_EMPTY;

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return DSC_ERROR_OK;
}

void *queue_front(DSCQueue const *queue) {
    if (!queue || queue->size == 0) return NULL;
    size_t front_offset;
    if (!dsc_safe_multiply(queue->front, queue->element_size, &front_offset)) {
        return NULL;
    }
    return (char *)queue->elements + front_offset;
}

void *queue_back(DSCQueue const *queue) {
    if (!queue || queue->size == 0) return NULL;
    size_t back = (queue->back + queue->capacity - 1) % queue->capacity;
    size_t back_offset;
    if (!dsc_safe_multiply(back, queue->element_size, &back_offset)) {
        return NULL;
    }
    return (char *)queue->elements + back_offset;
}

void queue_clear(DSCQueue *queue) {
    if (!queue) return;
    queue->front = 0;
    queue->back = 0;
    queue->size = 0;
}

DSCError queue_reserve(DSCQueue *queue, size_t n) {
    if (!queue) return DSC_ERROR_INVALID_ARGUMENT;
    if (n <= queue->capacity) return DSC_ERROR_OK;

    size_t new_size;
    if (!dsc_safe_multiply(n, queue->element_size, &new_size)) {
        return DSC_ERROR_OVERFLOW;
    }

    void *new_elements = dsc_malloc(new_size);
    if (!new_elements) return DSC_ERROR_MEMORY;

    // Copy elements from front to back
    if (queue->front <= queue->back) {
        size_t front_offset, copy_size;
        if (!dsc_safe_multiply(queue->front, queue->element_size,
                               &front_offset) ||
            !dsc_safe_multiply(queue->size, queue->element_size, &copy_size)) {
            dsc_free(new_elements);
            return DSC_ERROR_OVERFLOW;
        }
        memcpy(new_elements, (char *)queue->elements + front_offset, copy_size);
    } else {
        // Copy elements from front to end
        size_t first_part = queue->capacity - queue->front;
        size_t front_offset, first_part_size, first_part_offset, back_size;
        if (!dsc_safe_multiply(queue->front, queue->element_size,
                               &front_offset) ||
            !dsc_safe_multiply(first_part, queue->element_size,
                               &first_part_size) ||
            !dsc_safe_multiply(first_part, queue->element_size,
                               &first_part_offset) ||
            !dsc_safe_multiply(queue->back, queue->element_size, &back_size)) {
            dsc_free(new_elements);
            return DSC_ERROR_OVERFLOW;
        }
        memcpy(new_elements, (char *)queue->elements + front_offset,
               first_part_size);

        // Copy elements from start to back
        memcpy((char *)new_elements + first_part_offset, queue->elements,
               back_size);
    }

    dsc_free(queue->elements);
    queue->elements = new_elements;
    queue->capacity = n;
    queue->front = 0;
    queue->back = queue->size;

    return DSC_ERROR_OK;
}
