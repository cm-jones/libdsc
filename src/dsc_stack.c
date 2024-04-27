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

#include "../include/dsc_stack.h"

/* Represents a stack */

struct DSCStack {
    void **data;     /* Array of elements (void pointers) stored in the stack */
    size_t size;     /* The number of elements currently in the stack */
    size_t capacity; /* The current capacity of the stack */
    DSCType type;    /* The type of the elements in the stack */
    DSCError error;  /* The most recent error code */
};

/* Helper function for resizing a DSCStack when its size is equal to or greater than its capacity */

static bool dsc_stack_resize(DSCStack stack, size_t new_capacity) {
    void **new_data = realloc(stack->data, new_capacity * dsc_sizeof(stack->type));
    if (!new_data) {
        return false;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;

    return true;
}

/* Constructor and destructor for a DSCStack */

DSCStack dsc_stack_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCStack new_stack = malloc(sizeof *new_stack);
    if (!new_stack) {
        return NULL;
    }

    new_stack->size = 0;
    new_stack->capacity = DSC_STACK_INITIAL_CAPACITY;
    new_stack->type = type;

    new_stack->data = malloc(new_stack->capacity * dsc_sizeof(new_stack->type));
    if (!new_stack->data) {
        free(new_stack);
        return NULL;
    }

    new_stack->error = DSC_ERROR_OK;

    return new_stack;
}

bool dsc_stack_deinit(DSCStack stack) {
    if (!stack) {
        return false;
    }

    free(stack->data);
    free(stack);

    return true;
}

/* Capacity */

bool dsc_stack_is_empty(const DSCStack stack) {
    if (!stack) {
        return false;
    }

    stack->error = DSC_ERROR_OK;

    return stack->size == 0;
}

int dsc_stack_size(const DSCStack stack) {
    if (!stack) {
        return -1;
    }

    stack->error = DSC_ERROR_OK;

    return stack->size;
}

int dsc_stack_capacity(const DSCStack stack) {
    if (!stack) {
        return -1;
    }

    stack->error = DSC_ERROR_OK;

    return stack->capacity;
}

/* Element access */

void *dsc_stack_top(const DSCStack stack) {
    if (stack == NULL) {
        return NULL;
    }

    if (dsc_stack_is_empty(stack)) {
        stack->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    stack->error = DSC_ERROR_OK;

    return stack->data[stack->size - 1];
}

/* Modifiers */

bool dsc_stack_push(DSCStack stack, void *data) {
    if (!stack) {
        return false;
    }

    // Check if the type of the new element is the same as the type of the stack
    if (sizeof(*data) != dsc_sizeof(stack->type)) {
        stack->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    // Resize the stack if the size exceeds the capacity
    if (stack->size >= stack->capacity) {
        size_t new_capacity = stack->capacity * 1.5;
        if (!dsc_stack_resize(stack, new_capacity)) {
            stack->error = DSC_ERROR_OUT_OF_MEMORY;
            return false;
        }
    }

    stack->data[stack->size] = data;
    stack->size++;

    stack->error = DSC_ERROR_OK;

    return true;
}

void *dsc_stack_pop(DSCStack stack) {
    if (!stack) {
        return NULL;
    }

    if (dsc_stack_is_empty(stack)) {
        stack->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    // Get the popped element so we can return it after freeing it
    void *result = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = NULL;
    stack->size--;

    stack->error = DSC_ERROR_OK;

    return result;
}

/* Error handling */

DSCError dsc_stack_error(const DSCStack stack) {
    return stack->error;
}
