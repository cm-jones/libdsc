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

#include "../include/dsc_set.h"

int tests_run = 0;
int tests_passed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

void test_dsc_set_create(void) {
    DSCSet *set = dsc_set_create();
    assert(set != NULL);
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_insert(void) {
    DSCSet *set = dsc_set_create();
    int value = 42;
    assert(dsc_set_insert(set, value) && dsc_set_contains(set, value));
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_insert_duplicate(void) {
    DSCSet *set = dsc_set_create();
    int value = 42;
    dsc_set_insert(set, value);
    assert(!dsc_set_insert(set, value));
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_erase(void) {
    DSCSet *set = dsc_set_create();
    int value = 42;
    dsc_set_insert(set, value);
    assert(dsc_set_erase(set, value) && !dsc_set_contains(set, value));
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_erase_nonexistent(void) {
    DSCSet *set = dsc_set_create();
    int value = 42;
    assert(!dsc_set_erase(set, value));
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_size(void) {
    DSCSet *set = dsc_set_create();
    assert(dsc_set_size(set) == 0);
    dsc_set_insert(set, 42);
    assert(dsc_set_size(set) == 1);
    dsc_set_insert(set, 73);
    assert(dsc_set_size(set) == 2);
    dsc_set_insert(set, 42);
    assert(dsc_set_size(set) == 2);
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_empty(void) {
    DSCSet *set = dsc_set_create();
    assert(dsc_set_empty(set));
    dsc_set_insert(set, 42);
    assert(!dsc_set_empty(set));
    dsc_set_free(set);
    tests_passed++;
}

void test_dsc_set_clear(void) {
    DSCSet *set = dsc_set_create();
    dsc_set_insert(set, 42);
    dsc_set_insert(set, 73);
    dsc_set_clear(set);
    assert(dsc_set_size(set) == 0);
    dsc_set_free(set);
    tests_passed++;
}

int main(void) {
    run_test(test_dsc_set_create, "test_dsc_set_create");
    run_test(test_dsc_set_insert, "test_dsc_set_insert");
    run_test(test_dsc_set_insert_duplicate, "test_dsc_set_insert_duplicate");
    run_test(test_dsc_set_erase, "test_dsc_set_erase");
    run_test(test_dsc_set_erase_nonexistent, "test_dsc_set_erase_nonexistent");
    run_test(test_dsc_set_size, "test_dsc_set_size");
    run_test(test_dsc_set_empty, "test_dsc_set_empty");
    run_test(test_dsc_set_clear, "test_dsc_set_clear");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
