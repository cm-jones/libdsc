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

#include "../include/dsc_queue.h"

int tests_run = 0;
int tests_passed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

void test_dsc_queue_create(void) {
    DSCQueue *queue = dsc_queue_create();
    assert(queue != NULL);
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_push(void) {
    DSCQueue *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    assert(dsc_queue_front(queue) == 42 && dsc_queue_back(queue) == 73);
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_pop(void) {
    DSCQueue *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    dsc_queue_pop(queue);
    assert(dsc_queue_front(queue) == 73);
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_front(void) {
    DSCQueue *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    assert(dsc_queue_front(queue) == 42);
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_back(void) {
    DSCQueue *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    assert(dsc_queue_back(queue) == 73);
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_empty(void) {
    DSCQueue *queue = dsc_queue_create();
    assert(dsc_queue_empty(queue));
    dsc_queue_push(queue, 42);
    assert(!dsc_queue_empty(queue));
    dsc_queue_free(queue);
    tests_passed++;
}

void test_dsc_queue_size(void) {
    DSCQueue *queue = dsc_queue_create();
    assert(dsc_queue_size(queue) == 0);
    dsc_queue_push(queue, 42);
    assert(dsc_queue_size(queue) == 1);
    dsc_queue_push(queue, 73);
    assert(dsc_queue_size(queue) == 2);
    dsc_queue_free(queue);
    tests_passed++;
}

int main(void) {
    run_test(test_dsc_queue_create, "test_dsc_queue_create");
    run_test(test_dsc_queue_push, "test_dsc_queue_push");
    run_test(test_dsc_queue_pop, "test_dsc_queue_pop");
    run_test(test_dsc_queue_front, "test_dsc_queue_front");
    run_test(test_dsc_queue_back, "test_dsc_queue_back");
    run_test(test_dsc_queue_empty, "test_dsc_queue_empty");
    run_test(test_dsc_queue_size, "test_dsc_queue_size");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
