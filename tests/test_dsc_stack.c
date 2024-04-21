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
#include <stdio.h>

#include "../include/dsc_stack.h"

int tests_run = 0;
int tests_passed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

void test_dsc_stack_create() {
    dsc_stack_t *stack = dsc_stack_create();
    assert(stack != NULL);
    dsc_stack_free(stack);
    tests_passed++;
}

void test_dsc_stack_push() {
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    dsc_stack_push(stack, 73);
    assert(dsc_stack_top(stack) == 73);
    dsc_stack_free(stack);
    tests_passed++;
}

void test_dsc_stack_pop() {
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    dsc_stack_push(stack, 73);
    dsc_stack_pop(stack);
    assert(dsc_stack_top(stack) == 42);
    dsc_stack_free(stack);
    tests_passed++;
}

void test_dsc_stack_top() {
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    assert(dsc_stack_top(stack) == 42);
    dsc_stack_free(stack);
    tests_passed++;
}

void test_dsc_stack_empty() {
    dsc_stack_t *stack = dsc_stack_create();
    assert(dsc_stack_empty(stack));
    dsc_stack_push(stack, 42);
    assert(!dsc_stack_empty(stack));
    dsc_stack_free(stack);
    tests_passed++;
}

void test_dsc_stack_size() {
    dsc_stack_t *stack = dsc_stack_create();
    assert(dsc_stack_size(stack) == 0);
    dsc_stack_push(stack, 42);
    assert(dsc_stack_size(stack) == 1);
    dsc_stack_push(stack, 73);
    assert(dsc_stack_size(stack) == 2);
    dsc_stack_free(stack);
    tests_passed++;
}

int main() {
    run_test(test_dsc_stack_create, "test_dsc_stack_create");
    run_test(test_dsc_stack_push, "test_dsc_stack_push");
    run_test(test_dsc_stack_pop, "test_dsc_stack_pop");
    run_test(test_dsc_stack_top, "test_dsc_stack_top");
    run_test(test_dsc_stack_empty, "test_dsc_stack_empty");
    run_test(test_dsc_stack_size, "test_dsc_stack_size");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
