/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/dsc_queue.h"

/* Represents a queue */

struct DSCQueue {
    void **data;     /* Array of data stored in the queue */
    size_t front;    /* Index of the front element */
    size_t rear;     /* Index of the rear element */
    size_t size;     /* The number of elements currently in the queue */
    size_t capacity; /* The current capacity of the queue */
    DSCType type;    /* The type of the elements in the queue */
    DSCError error;  /* The most recent error code */
};

/* Helper function for resizing a DSCQueue when its size is equal to or greater than its capacity */

static bool dsc_queue_resize(DSCQueue queue, size_t new_capacity) {
    void **new_data = realloc(queue->data, new_capacity * dsc_sizeof(queue->type));
    if (!new_data) {
        return false;
    }

    // Rearrange elements in case of circular buffer
    if (queue->front > queue->rear) {
        size_t count = queue->capacity - queue->front;
        memmove(new_data + new_capacity - count, queue->data + queue->front, count * dsc_sizeof(queue->type));
        queue->front = new_capacity - count;
    }

    queue->data = new_data;
    queue->capacity = new_capacity;
    return true;
}

DSCQueue dsc_queue_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCQueue new_queue = malloc(sizeof *new_queue);
    if (!new_queue) {
        return NULL;
    }

    new_queue->front = 0;
    new_queue->rear = 0;
    new_queue->size = 0;
    new_queue->capacity = DSC_QUEUE_INITIAL_CAPACITY;
    new_queue->type = type;

    new_queue->data = malloc(new_queue->capacity * dsc_sizeof(type));
    if (!new_queue->data) {
        free(new_queue);
        return NULL;
    }

    return new_queue;
}

bool dsc_queue_deinit(DSCQueue queue) {
    if (!queue) {
        return false;
    }

    // Free the elements in the queue
    for (size_t i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity) {
        free(queue->data[i]);
    }

    free(queue->data);
    free(queue);
    return true;
}

/* Capacity */

bool dsc_queue_is_empty(const DSCQueue queue) {
    if (!queue) {
        return true;
    }

    return queue->size == 0;
}

int dsc_queue_size(const DSCQueue queue) {
    if (!queue) {
        return -1;
    }

    return queue->size;
}

/* Element access */

void *dsc_queue_front(const DSCQueue queue) {
    if (!queue || dsc_queue_is_empty(queue)) {
        return NULL;
    }

    return queue->data[queue->front];
}

void *dsc_queue_back(const DSCQueue queue) {
    if (!queue || dsc_queue_is_empty(queue)) {
        return NULL;
    }

    return queue->data[(queue->rear - 1 + queue->capacity) % queue->capacity];
}

/* Modifiers */

bool dsc_queue_push(DSCQueue queue, void *data) {
    if (!queue) {
        return false;
    }

    // Check if the type of the new element matches the type of the queue
    if (dsc_typeof(data) != queue->type) {
        queue->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    // Resize the queue if the size reaches the capacity
    if (queue->size == queue->capacity) {
        size_t new_capacity = queue->capacity * 2;
        if (!dsc_queue_resize(queue, new_capacity)) {
            return false;
        }
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
    return true;
}

void *dsc_queue_pop(DSCQueue queue) {
    if (!queue || dsc_queue_is_empty(queue)) {
        return NULL;
    }

    void *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

DSCError dsc_error_get(const DSCQueue queue) {
    return queue->error;
}
