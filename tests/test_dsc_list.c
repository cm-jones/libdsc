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
#include "../include/dsc_node.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

void run_test(void (*test_func)(void), const char *name) {
    printf("Running test: %s\n", name);
    tests_run++;
    test_func();
}

/* Test cases */

void test_dsc_list_create() {
    DSCList *list = dsc_list_create();
    assert(list != NULL);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_push_front(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    DSCNode *head = dsc_list_get_head(list);
    assert(head->value == 73);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_push_back(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_back(list, 42);
    dsc_list_push_back(list, 73);
    DSCNode *head = dsc_list_get_head(list);
    assert(head->value == 42);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_insert_after(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    DSCNode *head = dsc_list_get_head(list);
    dsc_list_insert_after(list, head, 73);
    DSCNode *next_node = head->next;
    assert(next_node->value == 73);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_pop_front(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_pop_front(list);
    DSCNode *head = dsc_list_get_head(list);
    assert(head->value == 42);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_remove(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_remove(list, 73);
    DSCNode *head = dsc_list_get_head(list);
    assert(head->value == 42);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_remove_all(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_push_front(list, 73);
    dsc_list_remove_all(list, 73);
    assert(dsc_list_front(list) == 42);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_front(void) {
    DSCList *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    assert(dsc_list_front(list) == 42);
    dsc_list_destroy(list);
    tests_passed++;
}

void test_dsc_list_empty(void) {
    DSCList *list = dsc_list_create();
    assert(dsc_list_empty(list));
    dsc_list_push_front(list, 42);
    assert(!dsc_list_empty(list));
    dsc_list_destroy(list);
    tests_passed++;
}

int main(void) {
    run_test(test_dsc_list_create, "test_dsc_list_create");
    run_test(test_dsc_list_push_front, "test_dsc_list_push_front");
    run_test(test_dsc_list_push_back, "test_dsc_list_push_back");
    run_test(test_dsc_list_insert_after, "test_dsc_list_insert_after");
    run_test(test_dsc_list_pop_front, "test_dsc_list_pop_front");
    run_test(test_dsc_list_remove, "test_dsc_list_remove");
    run_test(test_dsc_list_remove_all, "test_dsc_list_remove_all");
    run_test(test_dsc_list_front, "test_dsc_list_front");
    run_test(test_dsc_list_empty, "test_dsc_list_empty");

    printf("\nTest Results:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
