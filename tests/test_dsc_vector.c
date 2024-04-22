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

void test_dsc_vector_create() {
    dsc_vector_t *vector = dsc_vector_create();
    assert(vector != NULL && dsc_vector_empty(vector) && dsc_vector_size(vector) == 0 && dsc_vector_capacity(vector) == DSC_VECTOR_INITIAL_CAPACITY);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_free() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_free(vector);
    /* No assertion needed, just ensuring no memory leaks or crashes */
    tests_passed++;
}

void test_dsc_vector_push_back() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    assert(dsc_vector_size(vector) == 3 && dsc_vector_at(vector, 0) == 1 && dsc_vector_at(vector, 1) == 2 && dsc_vector_at(vector, 2) == 3);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_pop_back() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    dsc_vector_pop_back(vector);
    assert(dsc_vector_size(vector) == 2 && dsc_vector_at(vector, 0) == 1 && dsc_vector_at(vector, 1) == 2);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_insert() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    unsigned int position = dsc_vector_insert(vector, 1, 10);
    assert(position == 1 && dsc_vector_size(vector) == 4 && dsc_vector_at(vector, 0) == 1 && dsc_vector_at(vector, 1) == 10 && dsc_vector_at(vector, 2) == 2 && dsc_vector_at(vector, 3) == 3);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_erase() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    dsc_vector_erase(vector, 1);
    assert(dsc_vector_size(vector) == 2 && dsc_vector_at(vector, 0) == 1 && dsc_vector_at(vector, 1) == 3);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_at() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    assert(dsc_vector_at(vector, 0) == 1 && dsc_vector_at(vector, 1) == 2 && dsc_vector_at(vector, 2) == 3 && dsc_vector_at(vector, 3) == 0);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_empty() {
    dsc_vector_t *vector = dsc_vector_create();
    assert(dsc_vector_empty(vector));
    dsc_vector_push_back(vector, 1);
    assert(!dsc_vector_empty(vector));
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_size() {
    dsc_vector_t *vector = dsc_vector_create();
    assert(dsc_vector_size(vector) == 0);
    dsc_vector_push_back(vector, 1);
    assert(dsc_vector_size(vector) == 1);
    dsc_vector_push_back(vector, 2);
    assert(dsc_vector_size(vector) == 2);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_capacity() {
    dsc_vector_t *vector = dsc_vector_create();
    assert(dsc_vector_capacity(vector) == DSC_VECTOR_INITIAL_CAPACITY);
    dsc_vector_reserve(vector, 100);
    assert(dsc_vector_capacity(vector) == 100);
    dsc_vector_free(vector);
    tests_passed++;
}

void test_dsc_vector_reserve() {
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_reserve(vector, 100);
    assert(dsc_vector_capacity(vector) == 100);
    dsc_vector_free(vector);
    tests_passed++;
}

int main() {
    run_test(test_dsc_vector_create, "test_dsc_vector_create");
    run_test(test_dsc_vector_free, "test_dsc_vector_free");
    run_test(test_dsc_vector_push_back, "test_dsc_vector_push_back");
    run_test(test_dsc_vector_pop_back, "test_dsc_vector_pop_back");
    run_test(test_dsc_vector_insert, "test_dsc_vector_insert");
    run_test(test_dsc_vector_erase, "test_dsc_vector_erase");
    run_test(test_dsc_vector_at, "test_dsc_vector_at");
    run_test(test_dsc_vector_empty, "test_dsc_vector_empty");
    run_test(test_dsc_vector_size, "test_dsc_vector_size");
    run_test(test_dsc_vector_capacity, "test_dsc_vector_capacity");
    run_test(test_dsc_vector_reserve, "test_dsc_vector_reserve");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
