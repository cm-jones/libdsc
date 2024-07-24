// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../include/dsc_stack.h"

void dsc_stack_init_deinit(void) {
    DSCStack *stack;
    assert(dsc_stack_init(NULL, DSC_TYPE_BOOL) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_init(NULL, DSC_TYPE_CHAR) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_init(NULL, DSC_TYPE_INT) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_init(NULL, DSC_TYPE_FLOAT) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_init(NULL, DSC_TYPE_DOUBLE) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_stack_init(NULL, DSC_TYPE_STRING) == DSC_ERROR_INVALID_ARGUMENT);

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

}

void test_dsc_stack_capacity() {

}

void test_dsc_stack_empty(void) {

}

void test_dsc_stack_top(void) {

}

void test_dsc_stack_push(void) {

}

void test_dsc_stack_pop(void) {

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
