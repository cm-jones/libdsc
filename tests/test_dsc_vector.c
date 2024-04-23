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

#include "../include/dsc_vector.h"

int tests_run = 0;
int tests_passed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

void test_DSCVector_create(void) {
    DSCVector vector = DSCVector_create();
    assert(vector != NULL);
    assert(DSCVector_is_empty(vector));
    assert(DSCVector_size(vector) == 0);
    assert(DSCVector_capacity(vector) == DSC_VECTOR_INITIAL_CAPACITY);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_free(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_free(vector));
    /* No assertion needed, just ensuring no memory leaks or crashes */
    tests_passed++;
}

void test_DSCVector_push_back(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_push_back(vector, 3));
    assert(DSCVector_size(vector) == 3);
    assert(DSCVector_at(vector, 0) == 1);
    assert(DSCVector_at(vector, 1) == 2);
    assert(DSCVector_at(vector, 2) == 3);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_pop_back(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_push_back(vector, 3));
    assert(DSCVector_pop_back(vector));
    assert(DSCVector_size(vector) == 2);
    assert(DSCVector_at(vector, 0) == 1);
    assert(DSCVector_at(vector, 1) == 2);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_insert(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_push_back(vector, 3));
    assert(DSCVector_insert(vector, 10, 1));
    assert(DSCVector_size(vector) == 4);
    assert(DSCVector_at(vector, 0) == 1);
    assert(DSCVector_at(vector, 1) == 10);
    assert(DSCVector_at(vector, 2) == 2);
    assert(DSCVector_at(vector, 3) == 3);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_erase(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_push_back(vector, 3));
    assert(DSCVector_erase(vector, 1));
    assert(DSCVector_size(vector) == 2);
    assert(DSCVector_at(vector, 0) == 1);
    assert(DSCVector_at(vector, 1) == 3);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_at(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_push_back(vector, 3));
    assert(DSCVector_at(vector, 0) == 1);
    assert(DSCVector_at(vector, 1) == 2);
    assert(DSCVector_at(vector, 2) == 3);
    assert(DSCVector_at(vector, 3) == -1);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_is_empty(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_is_empty(vector));
    assert(DSCVector_push_back(vector, 1));
    assert(!DSCVector_is_empty(vector));
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_size(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_size(vector) == 0);
    assert(DSCVector_push_back(vector, 1));
    assert(DSCVector_size(vector) == 1);
    assert(DSCVector_push_back(vector, 2));
    assert(DSCVector_size(vector) == 2);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_capacity(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_capacity(vector) == DSC_VECTOR_INITIAL_CAPACITY);
    assert(DSCVector_reserve(vector, 100));
    assert(DSCVector_capacity(vector) == 100);
    DSCVector_free(vector);
    tests_passed++;
}

void test_DSCVector_reserve(void) {
    DSCVector vector = DSCVector_create();
    assert(DSCVector_reserve(vector, 100));
    assert(DSCVector_capacity(vector) == 100);
    DSCVector_free(vector);
    tests_passed++;
}

int main(void) {
    run_test(test_DSCVector_create, "test_DSCVector_create");
    run_test(test_DSCVector_free, "test_DSCVector_free");
    run_test(test_DSCVector_push_back, "test_DSCVector_push_back");
    run_test(test_DSCVector_pop_back, "test_DSCVector_pop_back");
    run_test(test_DSCVector_insert, "test_DSCVector_insert");
    run_test(test_DSCVector_erase, "test_DSCVector_erase");
    run_test(test_DSCVector_at, "test_DSCVector_at");
    run_test(test_DSCVector_is_empty, "test_DSCVector_is_empty");
    run_test(test_DSCVector_size, "test_DSCVector_size");
    run_test(test_DSCVector_capacity, "test_DSCVector_capacity");
    run_test(test_DSCVector_reserve, "test_DSCVector_reserve");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
