// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "../include/dsc_stack.h"

void test_dsc_stack_init_deinit(void) {
    DSCStack *stack;
    assert(dsc_stack_init(NULL, DSC_TYPE_BOOL) == DSC_ERROR_INVALID_ARGUMENT);
    
    DSCStack **null_stack = NULL;
    assert(dsc_stack_init(null_stack, DSC_TYPE_INT) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_init(&stack, DSC_TYPE_BOOL) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);

    assert(dsc_stack_init(&stack, DSC_TYPE_CHAR) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);

    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);

    assert(dsc_stack_init(&stack, DSC_TYPE_FLOAT) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);

    assert(dsc_stack_init(&stack, DSC_TYPE_DOUBLE) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);

    assert(dsc_stack_init(&stack, DSC_TYPE_STRING) == DSC_ERROR_OK);
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_size(void) {
    DSCStack *stack;
    size_t size;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test empty stack
    assert(dsc_stack_size(stack, &size) == DSC_ERROR_OK);
    assert(size == 0);
    
    // Test after adding elements
    int value = 42;
    assert(dsc_stack_push(stack, &value) == DSC_ERROR_OK);
    assert(dsc_stack_size(stack, &size) == DSC_ERROR_OK);
    assert(size == 1);
    
    value = 100;
    assert(dsc_stack_push(stack, &value) == DSC_ERROR_OK);
    assert(dsc_stack_size(stack, &size) == DSC_ERROR_OK);
    assert(size == 2);
    
    // Test error cases
    assert(dsc_stack_size(NULL, &size) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_size(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_capacity(void) {
    DSCStack *stack;
    size_t capacity;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test initial capacity
    assert(dsc_stack_capacity(stack, &capacity) == DSC_ERROR_OK);
    assert(capacity == DSC_STACK_INITIAL_CAPACITY);
    
    // Test error cases
    assert(dsc_stack_capacity(NULL, &capacity) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_capacity(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_empty(void) {
    DSCStack *stack;
    bool is_empty;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test empty stack
    assert(dsc_stack_empty(stack, &is_empty) == DSC_ERROR_OK);
    assert(is_empty == true);
    
    // Test after adding an element
    int value = 42;
    assert(dsc_stack_push(stack, &value) == DSC_ERROR_OK);
    assert(dsc_stack_empty(stack, &is_empty) == DSC_ERROR_OK);
    assert(is_empty == false);
    
    // Test after removing the element
    int popped;
    assert(dsc_stack_pop(stack, &popped) == DSC_ERROR_OK);
    assert(popped == 42);
    assert(dsc_stack_empty(stack, &is_empty) == DSC_ERROR_OK);
    assert(is_empty == true);
    
    // Test error cases
    assert(dsc_stack_empty(NULL, &is_empty) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_empty(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_top(void) {
    DSCStack *stack;
    int value, top_value;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test error on empty stack
    assert(dsc_stack_top(stack, &top_value) == DSC_ERROR_EMPTY_CONTAINER);
    
    // Test single element
    value = 42;
    assert(dsc_stack_push(stack, &value) == DSC_ERROR_OK);
    assert(dsc_stack_top(stack, &top_value) == DSC_ERROR_OK);
    assert(top_value == 42);
    
    // Test with multiple elements
    value = 100;
    assert(dsc_stack_push(stack, &value) == DSC_ERROR_OK);
    assert(dsc_stack_top(stack, &top_value) == DSC_ERROR_OK);
    assert(top_value == 100);
    
    // Test error cases
    assert(dsc_stack_top(NULL, &top_value) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_top(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_push(void) {
    DSCStack *stack;
    int values[] = {10, 20, 30, 40, 50};
    int top_value;
    size_t size;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test pushing multiple elements
    for (int i = 0; i < 5; i++) {
        assert(dsc_stack_push(stack, &values[i]) == DSC_ERROR_OK);
        assert(dsc_stack_top(stack, &top_value) == DSC_ERROR_OK);
        assert(top_value == values[i]);
        assert(dsc_stack_size(stack, &size) == DSC_ERROR_OK);
        assert(size == (size_t)(i + 1));
    }
    
    // Test error cases
    assert(dsc_stack_push(NULL, &values[0]) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_push(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

void test_dsc_stack_pop(void) {
    DSCStack *stack;
    int values[] = {10, 20, 30};
    int popped_value;
    size_t size;
    
    assert(dsc_stack_init(&stack, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test error on empty stack
    assert(dsc_stack_pop(stack, &popped_value) == DSC_ERROR_EMPTY_CONTAINER);
    
    // Push some values
    for (int i = 0; i < 3; i++) {
        assert(dsc_stack_push(stack, &values[i]) == DSC_ERROR_OK);
    }
    
    // Test popping in reverse order
    for (int i = 2; i >= 0; i--) {
        assert(dsc_stack_pop(stack, &popped_value) == DSC_ERROR_OK);
        assert(popped_value == values[i]);
        assert(dsc_stack_size(stack, &size) == DSC_ERROR_OK);
        assert(size == (size_t)i);
    }
    
    // Test error cases
    assert(dsc_stack_pop(NULL, &popped_value) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_pop(stack, NULL) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_pop(stack, &popped_value) == DSC_ERROR_EMPTY_CONTAINER);
    
    assert(dsc_stack_deinit(stack) == DSC_ERROR_OK);
}

int main(void) {
    test_dsc_stack_init_deinit();
    test_dsc_stack_size();
    test_dsc_stack_capacity();
    test_dsc_stack_empty();
    test_dsc_stack_top();
    test_dsc_stack_push();
    test_dsc_stack_pop();

    printf("All tests passed!\n");

    return EXIT_SUCCESS;
}
