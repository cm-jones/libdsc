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

#include "../include/dsc_map.h"

int tests_run = 0;
int tests_passed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

void test_dsc_map_create(void) {
    DSCMap *map = dsc_map_create();
    assert(map != NULL);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_insert(void) {
    DSCMap *map = dsc_map_create();
    int key = 42;
    int value = 73;
    assert(dsc_map_insert(map, key, value) == true);
    assert(dsc_map_get(map, key) == value);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_insert_duplicate(void) {
    DSCMap *map = dsc_map_create();
    int key = 42;
    int value1 = 73;
    int value2 = 84;
    dsc_map_insert(map, key, value1);
    assert(dsc_map_insert(map, key, value2) == false);
    assert(dsc_map_get(map, key) == value1);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_erase(void) {
    DSCMap *map = dsc_map_create();
    int key = 42;
    int value = 73;
    dsc_map_insert(map, key, value);
    assert(dsc_map_erase(map, key) == true);
    assert(dsc_map_get(map, key) == 0);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_erase_nonexistent(void) {
    DSCMap *map = dsc_map_create();
    int key = 42;
    assert(dsc_map_erase(map, key) == false);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_contains(void) {
    DSCMap *map = dsc_map_create();
    int key = 42;
    int value = 73;
    dsc_map_insert(map, key, value);
    assert(dsc_map_contains(map, key) == true);
    assert(dsc_map_contains(map, 84) == false);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_size(void) {
    assert(dsc_map_size(NULL) == -1);
    DSCMap *map = dsc_map_create();
    assert(dsc_map_size(map) == 0);
    dsc_map_insert(map, 42, 73);
    assert(dsc_map_size(map) == 1);
    dsc_map_insert(map, 84, 21);
    assert(dsc_map_size(map) == 2);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_empty(void) {
    DSCMap *map = dsc_map_create();
    assert(dsc_map_empty(map) == true);
    dsc_map_insert(map, 42, 73);
    assert(dsc_map_empty(map) == false);
    dsc_map_free(map);
    tests_passed++;
}

void test_dsc_map_clear(void) {
    DSCMap *map = dsc_map_create();
    dsc_map_insert(map, 42, 73);
    dsc_map_insert(map, 84, 21);
    dsc_map_clear(map);
    assert(dsc_map_size(map) == 0);
    dsc_map_free(map);
    tests_passed++;
}

int main(void) {
    run_test(test_dsc_map_create, "test_dsc_map_create");
    run_test(test_dsc_map_insert, "test_dsc_map_insert");
    run_test(test_dsc_map_insert_duplicate, "test_dsc_map_insert_duplicate");
    run_test(test_dsc_map_erase, "test_dsc_map_erase");
    run_test(test_dsc_map_erase_nonexistent, "test_dsc_map_erase_nonexistent");
    run_test(test_dsc_map_contains, "test_dsc_map_contains");
    run_test(test_dsc_map_size, "test_dsc_map_size");
    run_test(test_dsc_map_empty, "test_dsc_map_empty");
    run_test(test_dsc_map_clear, "test_dsc_map_clear");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
