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

#include "../include/dsc_list.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

/* Test cases */

void test_DSCList_create(void) {
    DSCList list = DSCList_create();
    assert(list != NULL);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_push_front(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_front(list, 42));
    assert(DSCList_push_front(list, 73));
    assert(DSCList_get_head(list) == 73);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_push_back(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_back(list, 42));
    assert(DSCList_push_back(list, 73));
    assert(DSCList_get_head(list) == 42);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_insert(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_front(list, 42));
    assert(DSCList_insert(list, 73, 1));
    assert(DSCList_get_head(list) == 42);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_pop_front(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_front(list, 42));
    assert(DSCList_push_front(list, 73));
    assert(DSCList_pop_front(list) == 73);
    assert(DSCList_get_head(list) == 42);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_remove(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_front(list, 42));
    assert(DSCList_push_front(list, 73));
    assert(DSCList_remove(list, 73));
    assert(DSCList_get_head(list) == 42);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_remove_all(void) {
    DSCList list = DSCList_create();
    assert(DSCList_push_front(list, 42));
    assert(DSCList_push_front(list, 73));
    assert(DSCList_push_front(list, 73));
    assert(DSCList_remove_all(list, 73));
    assert(DSCList_get_head(list) == 42);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_size(void) {
    DSCList list = DSCList_create();
    assert(DSCList_size(list) == 0);
    assert(DSCList_push_front(list, 42));
    assert(DSCList_size(list) == 1);
    assert(DSCList_push_front(list, 73));
    assert(DSCList_size(list) == 2);
    DSCList_destroy(list);
    tests_passed++;
}

void test_DSCList_is_empty(void) {
    DSCList list = DSCList_create();
    assert(DSCList_is_empty(list));
    assert(DSCList_push_front(list, 42));
    assert(!DSCList_is_empty(list));
    DSCList_destroy(list);
    tests_passed++;
}

int main(void) {
    run_test(test_DSCList_create, "test_DSCList_create");
    run_test(test_DSCList_push_front, "test_DSCList_push_front");
    run_test(test_DSCList_push_back, "test_DSCList_push_back");
    run_test(test_DSCList_insert, "test_DSCList_insert");
    run_test(test_DSCList_pop_front, "test_DSCList_pop_front");
    run_test(test_DSCList_remove, "test_DSCList_remove");
    run_test(test_DSCList_remove_all, "test_DSCList_remove_all");
    run_test(test_DSCList_size, "test_DSCList_size");
    run_test(test_DSCList_is_empty, "test_DSCList_is_empty");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
