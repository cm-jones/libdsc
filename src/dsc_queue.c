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

#include "../include/dsc_queue.h"
#include "../include/dsc_error.h"

/* Represents a queue. */
struct dsc_queue_t {
    int *values;     /* Array of values stored in the queue. */
    size_t size;     /* The number of elements in the queue. */
    size_t capacity; /* The current capacity of the queue. */
};

static void dsc_queue_resize(dsc_queue_t *queue, size_t new_capacity) {
    /* Check for integer overflow. */
    if (new_capacity > SIZE_MAX / sizeof(int)) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    int *new_values = malloc(new_capacity * sizeof(int));
    if (new_values == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    if (queue->values != NULL) {
        memcpy(new_values, queue->values, queue->size * sizeof(int));
        free(queue->values);
    }

    queue->values = new_values;
    queue->capacity = new_capacity;
}

dsc_queue_t *dsc_queue_create() {
    dsc_queue_t *new_queue = malloc(sizeof *new_queue);
    if (new_queue == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_queue->size = 0;
    new_queue->capacity = DSC_QUEUE_INITIAL_CAPACITY;
    dsc_queue_resize(new_queue, new_queue->capacity);

    if (new_queue->values == NULL) {
        free(new_queue);
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return new_queue;
}

void dsc_queue_free(dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    free(queue->values);
    free(queue);

    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_queue_push(dsc_queue_t *queue, int value) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Resize the queue if the size exceeds the capacity. */
    if (queue->size >= queue->capacity) {
        size_t new_capacity = queue->capacity * 1.5;
        dsc_queue_resize(queue, new_capacity);
        if (queue->values == NULL) {
            dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
            return;
        }
    }

    queue->values[queue->size] = value;
    queue->size++;
    dsc_set_error(DSC_ERROR_NONE);
}

void dsc_queue_pop(dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (dsc_queue_empty(queue)) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return;
    }

    /* Shift elements to the left */
    for (size_t i = 0; i < queue->size - 1; ++i) {
        queue->values[i] = queue->values[i + 1];
    }

    queue->size--;
    dsc_set_error(DSC_ERROR_NONE);
}

int dsc_queue_front(const dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    if (dsc_queue_empty(queue)) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return queue->values[0];
}

int dsc_queue_back(const dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    if (dsc_queue_empty(queue)) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return queue->values[queue->size - 1];
}

bool dsc_queue_empty(const dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return true;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return queue->size == 0;
}

size_t dsc_queue_size(const dsc_queue_t *queue) {
    if (queue == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return queue->size;
}