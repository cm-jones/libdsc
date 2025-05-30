// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/stack.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static dsc_error grow_stack(dsc_stack *stack) {
    size_t new_capacity = stack->capacity * 2;
    void *new_data = realloc(stack->data, new_capacity * stack->element_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;
    return DSC_ERROR_OK;
}

dsc_stack *stack_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    dsc_stack *stack = malloc(sizeof(dsc_stack));
    if (!stack) {
        return NULL;
    }

    stack->data = malloc(INITIAL_CAPACITY * element_size);
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->element_size = element_size;

    return stack;
}

void stack_destroy(dsc_stack *stack) {
    if (!stack) {
        return;
    }

    free(stack->data);
    free(stack);
}

size_t stack_size(dsc_stack const *stack) { return stack ? stack->size : 0; }

bool stack_empty(dsc_stack const *stack) {
    return !stack || stack->size == 0;
}

dsc_error stack_push(dsc_stack *stack, void const *element) {
    if (!stack || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == stack->capacity) {
        dsc_error err = grow_stack(stack);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    memcpy((char *)stack->data + stack->size * stack->element_size, element,
           stack->element_size);
    stack->size++;

    return DSC_ERROR_OK;
}

dsc_error stack_pop(dsc_stack *stack) {
    if (!stack) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    stack->size--;
    return DSC_ERROR_OK;
}

void *dsc_stackop(dsc_stack const *stack) {
    if (!stack || stack->size == 0) {
        return NULL;
    }

    return (char *)stack->data + (stack->size - 1) * stack->element_size;
}

void stack_clear(dsc_stack *stack) {
    if (stack) {
        stack->size = 0;
    }
}

dsc_error stack_reserve(dsc_stack *stack, size_t capacity) {
    if (!stack) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (capacity <= stack->capacity) {
        return DSC_ERROR_OK;
    }

    void *new_data = realloc(stack->data, capacity * stack->element_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    stack->data = new_data;
    stack->capacity = capacity;
    return DSC_ERROR_OK;
}
