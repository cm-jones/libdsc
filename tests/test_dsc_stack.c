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
