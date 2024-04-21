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
#include <check.h>

#include "../include/dsc_list.h"
#include "../include/dsc_node.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_list_create)
{
    dsc_list_t *list = dsc_list_create();
    ck_assert_ptr_nonnull(list);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_push_front)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_int_eq(head->value, 73);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_push_back)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_back(list, 42);
    dsc_list_push_back(list, 73);
    dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_int_eq(head->value, 42);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert_after)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_node_t *head = dsc_list_get_head(list);
    dsc_list_insert_after(list, head, 73);
    dsc_node_t *next_node = head->next;
    ck_assert_int_eq(next_node->value, 73);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_pop_front)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_pop_front(list);
    dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_int_eq(head->value, 42);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_remove)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_remove(list, 73);
    dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_int_eq(head->value, 42);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_remove_all)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    dsc_list_push_front(list, 73);
    dsc_list_push_front(list, 73);
    dsc_list_remove_all(list, 73);
    ck_assert_int_eq(dsc_list_front(list), 42);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_front)
{
    dsc_list_t *list = dsc_list_create();
    dsc_list_push_front(list, 42);
    ck_assert_int_eq(dsc_list_front(list), 42);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_empty)
{
    dsc_list_t *list = dsc_list_create();
    ck_assert_int_eq(dsc_list_empty(list), true);
    dsc_list_push_front(list, 42);
    ck_assert_int_eq(dsc_list_empty(list), false);
    dsc_list_destroy(list);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_list_suite(void) {
    Suite *suite = suite_create("dsc_list");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_list_create);
    tcase_add_test(tcase, test_dsc_list_push_front);
    tcase_add_test(tcase, test_dsc_list_push_back);
    tcase_add_test(tcase, test_dsc_list_insert_after);
    tcase_add_test(tcase, test_dsc_list_pop_front);
    tcase_add_test(tcase, test_dsc_list_remove);
    tcase_add_test(tcase, test_dsc_list_remove_all);
    tcase_add_test(tcase, test_dsc_list_front);
    tcase_add_test(tcase, test_dsc_list_empty);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_list_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
