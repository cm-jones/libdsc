// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_STACK_H_
#define DSC_STACK_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} dsc_stack_t;

// Create a new stack
dsc_stack_t *stack_create(size_t element_size);

// Destroy a stack
void stack_destroy(dsc_stack_t *stack);

// Get the number of elements in the stack
size_t stack_size(dsc_stack_t const *stack);

// Check if the stack is empty
bool stack_empty(dsc_stack_t const *stack);

// Push an element onto the stack
dsc_error_t stack_push(dsc_stack_t *stack, void const *element);

// Pop an element from the stack
dsc_error_t stack_pop(dsc_stack_t *stack);

// Get the top element of the stack
void *dsc_stack_top(dsc_stack_t const *stack);

// Clear all elements from the stack
void stack_clear(dsc_stack_t *stack);

// Reserve space for elements
dsc_error_t stack_reserve(dsc_stack_t *stack, size_t capacity);

#ifdef __cplusplus
}
#endif

#endif  // DSC_STACK_H_
