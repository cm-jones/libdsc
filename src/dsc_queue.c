// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/dsc_queue.h"

struct DSCQueue {
    DSCData data;    // The data stored in the queue
    size_t front;    // Index of the front element
    size_t rear;     // Index of the rear element
    size_t size;     // The number of elements currently in the queue
    size_t capacity; // The current capacity of the queue
    DSCType type;    // The type of the elements in the queue
};

// Helper function to copy strings safely
static void dsc_str_cpy(char *dest, const char *src) {
    size_t len = strlen(src);
    memcpy(dest, src, len + 1);
}

static bool dsc_queue_resize(DSCQueue *queue, size_t new_capacity) {
    size_t old_capacity = queue->capacity;

    switch (queue->type) {
        case DSC_TYPE_CHAR: {
            queue->data.c_ptr = realloc(queue->data.c_ptr, new_capacity * sizeof(char));
            if (queue->data.c_ptr == NULL) {
                return false;
            }
            break;
        }
        
        case DSC_TYPE_INT: {
            queue->data.i_ptr = realloc(queue->data.i_ptr, new_capacity * sizeof(int));
            if (queue->data.i_ptr == NULL) {
                return false;
            }
            break;
        }

        case DSC_TYPE_FLOAT: {
            queue->data.f_ptr = realloc(queue->data.f_ptr, new_capacity * sizeof(float));
            if (queue->data.f_ptr == NULL) {
                return false;
            }
            break;
        }

        case DSC_TYPE_DOUBLE: {
            queue->data.d_ptr = realloc(queue->data.d_ptr, new_capacity * sizeof(double));
            if (queue->data.d_ptr == NULL) {
                return false;
            }
            break;
        }

        case DSC_TYPE_STRING: {
            queue->data.s_ptr = realloc(queue->data.s_ptr, new_capacity * sizeof(char *));
            if (queue->data.s_ptr == NULL) {
                return false;
            }
            break;
        }

        case DSC_TYPE_BOOL: {
            queue->data.b_ptr = realloc(queue->data.b_ptr, new_capacity * sizeof(bool));
            if (queue->data.b_ptr == NULL) {
                return false;
            }
            break;
        }
        default:
            return false;
    }

    // Rearrange elements in case of circular buffer
    if (queue->front > queue->rear) {
        size_t count = old_capacity - queue->front;

        switch (queue->type) {
            case DSC_TYPE_CHAR: {
                memmove(queue->data.c_ptr + new_capacity - count, queue->data.c_ptr + queue->front, count * sizeof(char));
                break;
            }

            case DSC_TYPE_INT: {
                memmove(queue->data.i_ptr + new_capacity - count, queue->data.i_ptr + queue->front, count * sizeof(int));
                break;
            }

            case DSC_TYPE_FLOAT: {
                memmove(queue->data.f_ptr + new_capacity - count, queue->data.f_ptr + queue->front, count * sizeof(float));
                break;
            }

            case DSC_TYPE_DOUBLE: {
                memmove(queue->data.d_ptr + new_capacity - count, queue->data.d_ptr + queue->front, count * sizeof(double));
                break;
            }

            case DSC_TYPE_STRING: {
                memmove(queue->data.s_ptr + new_capacity - count, queue->data.s_ptr + queue->front, count * sizeof(char *));
                break;
            }

            case DSC_TYPE_BOOL: {
                memmove(queue->data.b_ptr + new_capacity - count, queue->data.b_ptr + queue->front, count * sizeof(bool));
                break;
            }

            default: {
                return false;
            }
        }
        
        queue->front = new_capacity - count;
    }

    queue->capacity = new_capacity;

    return true;
}

DSCError dsc_queue_init(DSCQueue *new_queue, DSCType type) {
    if (new_queue == NULL || dsc_type_invalid(type)) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    new_queue->front = 0;
    new_queue->rear = 0;
    new_queue->size = 0;
    new_queue->capacity = DSC_QUEUE_INITIAL_CAPACITY;
    new_queue->type = type;

    switch (new_queue->type) {
        case DSC_TYPE_CHAR: {
            new_queue->data.c_ptr = malloc(new_queue->capacity * sizeof(char));
            if (new_queue->data.c_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }
        
        case DSC_TYPE_INT: {
            new_queue->data.i_ptr = malloc(new_queue->capacity * sizeof(int));
            if (new_queue->data.i_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        case DSC_TYPE_FLOAT: {
            new_queue->data.f_ptr = malloc(new_queue->capacity * sizeof(float));
            if (new_queue->data.f_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        case DSC_TYPE_DOUBLE: {
            new_queue->data.d_ptr = malloc(new_queue->capacity * sizeof(double));
            if (new_queue->data.d_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        case DSC_TYPE_STRING: {
            new_queue->data.s_ptr = malloc(new_queue->capacity * sizeof(char *));
            if (new_queue->data.s_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        case DSC_TYPE_BOOL: {
            new_queue->data.b_ptr = malloc(new_queue->capacity * sizeof(bool));
            if (new_queue->data.b_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    return DSC_ERROR_OK;
}

DSCError dsc_queue_deinit(DSCQueue *queue) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Initial loop was incomplete and unnecessary, string types are handled below

    switch (queue->type) {
        case DSC_TYPE_CHAR: {
            free(queue->data.c_ptr);
            break;
        }
        
        case DSC_TYPE_INT: {
            free(queue->data.i_ptr);
            break;
        }

        case DSC_TYPE_FLOAT: {
            free(queue->data.f_ptr);
            break;
        }

        case DSC_TYPE_DOUBLE: {
            free(queue->data.d_ptr);
            break;
        }

        case DSC_TYPE_STRING: {
            for (size_t i = queue->front; i != queue->rear; i = (i + 1) % queue->capacity) {
                free(queue->data.s_ptr[i]);
            }

            free(queue->data.s_ptr);
            break;
        }

        case DSC_TYPE_BOOL: {
            free(queue->data.b_ptr);
            break;
        }

        default: {
            return DSC_ERROR_INVALID_ARGUMENT;
        }
    }

    free(queue);

    return DSC_ERROR_OK;
}

DSCError dsc_queue_size(const DSCQueue *queue, size_t *size) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *size = queue->size;

    return DSC_ERROR_OK;
}

DSCError dsc_queue_capacity(const DSCQueue *queue, size_t *capacity) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *capacity = queue->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_queue_empty(const DSCQueue *queue, bool *is_empty) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *is_empty = queue->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_queue_front(const DSCQueue *queue, void *front) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    if (queue->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (queue->type) {
        case DSC_TYPE_CHAR: {
            *(char *) front = queue->data.c_ptr[queue->front];
            break;
        }
        
        case DSC_TYPE_INT: {
            *(int *) front = queue->data.i_ptr[queue->front];
            break;
        }

        case DSC_TYPE_FLOAT: {
            *(float *) front = queue->data.f_ptr[queue->front];
            break;
        }

        case DSC_TYPE_DOUBLE: {
            *(double *) front = queue->data.d_ptr[queue->front];
            break;
        }

        case DSC_TYPE_STRING: {
            const char *string = queue->data.s_ptr[queue->front];

            size_t string_size = strlen(string) + 1;
            size_t front_size = strlen((char *) front);

            if (string_size > front_size) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy((char *) front, string, front_size - 1);
            memset((char *) front + string_size, '\0', 1);
            break;
        }

        case DSC_TYPE_BOOL: {
            *(bool *) front = queue->data.b_ptr[queue->front];
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    return DSC_ERROR_OK;
}

DSCError dsc_queue_back(const DSCQueue *queue, void *back) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (queue->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    size_t back_index = (queue->rear - 1 + queue->capacity) % queue->capacity;

    switch (queue->type) {
        case DSC_TYPE_CHAR: {
            *(char *) back = queue->data.c_ptr[back_index];
            break;
        }

        case DSC_TYPE_INT: {
            *(int *) back = queue->data.i_ptr[back_index];
            break;
        }

        case DSC_TYPE_FLOAT: {
            *(float *) back = queue->data.f_ptr[back_index];
            break;
        }

        case DSC_TYPE_DOUBLE: {
            *(double *) back = queue->data.d_ptr[back_index];
            break;
        }

        case DSC_TYPE_STRING: {
            dsc_str_cpy((char *) back, queue->data.s_ptr[back_index]);
            break;
        }

        case DSC_TYPE_BOOL: {
            *(bool *) back = queue->data.b_ptr[back_index];
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    return DSC_ERROR_OK;
}

DSCError dsc_queue_push(DSCQueue *queue, void *data) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Resize the queue if the size reaches the capacity
    if (queue->size >= queue->capacity) {
        size_t new_capacity = queue->capacity * 1.5;
        if (!dsc_queue_resize(queue, new_capacity)) {
            return DSC_ERROR_OUT_OF_MEMORY;
        }
    }

    switch (queue->type) {
        case DSC_TYPE_CHAR: {
            queue->data.c_ptr[queue->rear] = *(char *) data;
            break;
        }
        
        case DSC_TYPE_INT: {
            queue->data.i_ptr[queue->rear] = *(int *) data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            queue->data.f_ptr[queue->rear] = *(float *) data;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            queue->data.d_ptr[queue->rear] = *(double *) data;
            break;
        }

        case DSC_TYPE_STRING: {
            size_t string_size = strlen(*(char **) data) + 1;
            queue->data.s_ptr[queue->size] = malloc(string_size);
            if (queue->data.s_ptr[queue->size] == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            dsc_str_cpy(queue->data.s_ptr[queue->size], *(char **) data);
            break;
        }

        case DSC_TYPE_BOOL: {
            queue->data.b_ptr[queue->rear] = *(bool *) data;
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_queue_pop(DSCQueue *queue, void *data) {
    if (queue == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (queue->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (queue->type) {
        case DSC_TYPE_BOOL:
            *(bool *) data = queue->data.b_ptr[queue->front];
            break;
        case DSC_TYPE_CHAR:
            *(char *) data = queue->data.c_ptr[queue->front];
            break;
        case DSC_TYPE_INT:
            *(int *) data = queue->data.i_ptr[queue->front];
            break;
        case DSC_TYPE_FLOAT:
            *(float *) data = queue->data.f_ptr[queue->front];
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) data = queue->data.d_ptr[queue->front];
            break;
        case DSC_TYPE_STRING:
            *(char **) data = queue->data.s_ptr[queue->front];
            free(queue->data.s_ptr[queue->front]);
            queue->data.s_ptr[queue->front] = NULL;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return DSC_ERROR_OK;
}
