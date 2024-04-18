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

#include "../include/dsc_set.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_set_create)
{
    dsc_set_t *set = dsc_set_create();
    ck_assert_ptr_nonnull(set);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_insert)
{
    dsc_set_t *set = dsc_set_create();
    int value = 42;
    ck_assert_int_eq(dsc_set_insert(set, value), true);
    ck_assert_int_eq(dsc_set_contains(set, value), true);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_insert_duplicate)
{
    dsc_set_t *set = dsc_set_create();
    int value = 42;
    dsc_set_insert(set, value);
    ck_assert_int_eq(dsc_set_insert(set, value), false);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_erase)
{
    dsc_set_t *set = dsc_set_create();
    int value = 42;
    dsc_set_insert(set, value);
    ck_assert_int_eq(dsc_set_erase(set, value), true);
    ck_assert_int_eq(dsc_set_contains(set, value), false);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_erase_nonexistent)
{
    dsc_set_t *set = dsc_set_create();
    int value = 42;
    ck_assert_int_eq(dsc_set_erase(set, value), false);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_size)
{
    dsc_set_t *set = dsc_set_create();
    ck_assert_int_eq(dsc_set_size(set), 0);
    dsc_set_insert(set, 42);
    ck_assert_int_eq(dsc_set_size(set), 1);
    dsc_set_insert(set, 73);
    ck_assert_int_eq(dsc_set_size(set), 2);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_empty)
{
    dsc_set_t *set = dsc_set_create();
    ck_assert_int_eq(dsc_set_empty(set), true);
    dsc_set_insert(set, 42);
    ck_assert_int_eq(dsc_set_empty(set), false);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_clear)
{
    dsc_set_t *set = dsc_set_create();
    dsc_set_insert(set, 42);
    dsc_set_insert(set, 73);
    dsc_set_clear(set);
    ck_assert_int_eq(dsc_set_size(set), 0);
    dsc_set_free(set);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_set_suite(void) {
    Suite *suite = suite_create("dsc_set");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_set_create);
    tcase_add_test(tcase, test_dsc_set_insert);
    tcase_add_test(tcase, test_dsc_set_insert_duplicate);
    tcase_add_test(tcase, test_dsc_set_erase);
    tcase_add_test(tcase, test_dsc_set_erase_nonexistent);
    tcase_add_test(tcase, test_dsc_set_size);
    tcase_add_test(tcase, test_dsc_set_empty);
    tcase_add_test(tcase, test_dsc_set_clear);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_set_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
