// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/stack.h"

#include <stdlib.h>
#include <string.h>

#define DSC_STACK_INITIAL_CAPACITY 16

static DSCError grow_stack(DSCStack *stack) {
    size_t new_capacity;
    if (!dsc_safe_grow_capacity(stack->capacity, &new_capacity)) {
        return DSC_ERROR_OVERFLOW;
    }

    size_t new_size;
    if (!dsc_safe_multiply(new_capacity, stack->element_size, &new_size)) {
        return DSC_ERROR_OVERFLOW;
    }

    void *new_data = dsc_realloc(stack->data, new_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;
    return DSC_ERROR_OK;
}

DSCStack *stack_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    DSCStack *stack = dsc_malloc(sizeof(DSCStack));
    if (!stack) {
        return NULL;
    }

    size_t initial_size;
    if (!dsc_safe_multiply(DSC_STACK_INITIAL_CAPACITY, element_size, &initial_size)) {
        dsc_free(stack);
        return NULL;
    }

    stack->data = dsc_malloc(initial_size);
    if (!stack->data) {
        dsc_free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = DSC_STACK_INITIAL_CAPACITY;
    stack->element_size = element_size;

    return stack;
}

void stack_destroy(DSCStack *stack) {
    if (!stack) {
        return;
    }

    dsc_free(stack->data);
    dsc_free(stack);
}

size_t stack_size(DSCStack const *stack) { return stack ? stack->size : 0; }

bool stack_empty(DSCStack const *stack) { return !stack || stack->size == 0; }

DSCError stack_push(DSCStack *stack, void const *element) {
    if (!stack || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == stack->capacity) {
        DSCError err = grow_stack(stack);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    size_t offset;
    if (!dsc_safe_multiply(stack->size, stack->element_size, &offset)) {
        return DSC_ERROR_OVERFLOW;
    }

    memcpy((char *)stack->data + offset, element, stack->element_size);
    stack->size++;

    return DSC_ERROR_OK;
}

DSCError stack_pop(DSCStack *stack) {
    if (!stack) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    stack->size--;
    return DSC_ERROR_OK;
}

void *stack_top(DSCStack const *stack) {
    if (!stack || stack->size == 0) {
        return NULL;
    }

    size_t offset;
    if (!dsc_safe_multiply(stack->size - 1, stack->element_size, &offset)) {
        return NULL;
    }

    return (char *)stack->data + offset;
}

void stack_clear(DSCStack *stack) {
    if (stack) {
        stack->size = 0;
    }
}

DSCError stack_reserve(DSCStack *stack, size_t capacity) {
    if (!stack) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (capacity <= stack->capacity) {
        return DSC_ERROR_OK;
    }

    size_t new_size;
    if (!dsc_safe_multiply(capacity, stack->element_size, &new_size)) {
        return DSC_ERROR_OVERFLOW;
    }

    void *new_data = dsc_realloc(stack->data, new_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    stack->data = new_data;
    stack->capacity = capacity;
    return DSC_ERROR_OK;
}
