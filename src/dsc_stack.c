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
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#include "../include/dsc_stack.h"
#include "../include/dsc_error.h"

struct dsc_stack_t {
    int *values;
    size_t size;
    size_t capacity;
};

static void dsc_stack_resize(struct dsc_stack_t *stack, size_t new_capacity) {
    if (new_capacity > SIZE_MAX / sizeof(int)) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    int *new_values = malloc(new_capacity * sizeof(int));
    if (new_values == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    if (stack->values != NULL) {
        memcpy(new_values, stack->values, stack->size * sizeof(int));
        free(stack->values);
    }

    stack->values = new_values;
    stack->capacity = new_capacity;
}

struct dsc_stack_t *dsc_stack_create() {
    struct dsc_stack_t *new_stack = malloc(sizeof *new_stack);
    if (new_stack == NULL) {
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_stack->size = 0;
    new_stack->capacity = DSC_STACK_INITIAL_CAPACITY;
    dsc_stack_resize(new_stack, new_stack->capacity);

    if (new_stack->values == NULL) {
        free(new_stack);
        dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_last_error(DSC_ERROR_NONE);
    return new_stack;
}

void dsc_stack_free(struct dsc_stack_t *stack) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    free(stack->values);
    free(stack);

    dsc_set_last_error(DSC_ERROR_NONE);
}

void dsc_stack_push(struct dsc_stack_t *stack, int value) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    // Resize the stack if the size exceeds the capacity
    if (stack->size >= stack->capacity) {
        size_t new_capacity = stack->capacity * 1.5; // Use a 1.5x growth factor
        dsc_stack_resize(stack, new_capacity);
        if (stack->values == NULL) {
            dsc_set_last_error(DSC_ERROR_OUT_OF_MEMORY);
            return;
        }
    }

    stack->values[stack->size] = value;
    stack->size++;
    dsc_set_last_error(DSC_ERROR_NONE);
}

void dsc_stack_pop(struct dsc_stack_t *stack) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    if (dsc_stack_empty(stack)) {
        dsc_set_last_error(DSC_ERROR_EMPTY_STACK);
        return;
    }

    stack->size--;
    dsc_set_last_error(DSC_ERROR_NONE);
}

int dsc_stack_top(const struct dsc_stack_t *stack) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    if (dsc_stack_empty(stack)) {
        dsc_set_last_error(DSC_ERROR_EMPTY_STACK);
        return 0;
    }

    dsc_set_last_error(DSC_ERROR_NONE);
    return stack->values[stack->size - 1];
}

bool dsc_stack_empty(const struct dsc_stack_t *stack) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dsc_set_last_error(DSC_ERROR_NONE);
    return stack->size == 0;
}

size_t dsc_stack_size(const struct dsc_stack_t *stack) {
    if (stack == NULL) {
        dsc_set_last_error(DSC_ERROR_INVALID_ARGUMENT);
        return 0;
    }

    dsc_set_last_error(DSC_ERROR_NONE);
    return stack->size;
}