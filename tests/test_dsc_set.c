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

#include <check.h>

#include "../include/dsc_set.h"
#include "../include/dsc_error.h"

START_TEST(test_dsc_set_create_free)
{
    struct dsc_set_t *set = dsc_set_create();
    ck_assert_ptr_nonnull(set);
    ck_assert_int_eq(dsc_set_size(set), 0);
    ck_assert(dsc_set_empty(set));
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_insert)
{
    struct dsc_set_t *set = dsc_set_create();
    ck_assert(dsc_set_insert(set, 10));
    ck_assert_int_eq(dsc_set_size(set), 1);
    ck_assert(!dsc_set_empty(set));
    ck_assert(!dsc_set_insert(set, 10));
    ck_assert_int_eq(dsc_set_size(set), 1);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_erase)
{
    struct dsc_set_t *set = dsc_set_create();
    dsc_set_insert(set, 10);
    dsc_set_insert(set, 20);
    ck_assert(dsc_set_erase(set, 10));
    ck_assert_int_eq(dsc_set_size(set), 1);
    ck_assert(!dsc_set_erase(set, 10));
    ck_assert_int_eq(dsc_set_size(set), 1);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_contains)
{
    struct dsc_set_t *set = dsc_set_create();
    dsc_set_insert(set, 10);
    ck_assert(dsc_set_contains(set, 10));
    ck_assert(!dsc_set_contains(set, 20));
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_size)
{
    struct dsc_set_t *set = dsc_set_create();
    ck_assert_int_eq(dsc_set_size(set), 0);
    dsc_set_insert(set, 10);
    ck_assert_int_eq(dsc_set_size(set), 1);
    dsc_set_insert(set, 20);
    ck_assert_int_eq(dsc_set_size(set), 2);
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_empty)
{
    struct dsc_set_t *set = dsc_set_create();
    ck_assert(dsc_set_empty(set));
    dsc_set_insert(set, 10);
    ck_assert(!dsc_set_empty(set));
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_clear)
{
    struct dsc_set_t *set = dsc_set_create();
    dsc_set_insert(set, 10);
    dsc_set_insert(set, 20);
    ck_assert_int_eq(dsc_set_size(set), 2);
    dsc_set_clear(set);
    ck_assert_int_eq(dsc_set_size(set), 0);
    ck_assert(dsc_set_empty(set));
    dsc_set_free(set);
}
END_TEST

START_TEST(test_dsc_set_error_handling)
{
    struct dsc_set_t *set = NULL;
    ck_assert(!dsc_set_insert(set, 10));
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert(!dsc_set_erase(set, 10));
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert(!dsc_set_contains(set, 10));
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_size(set), 0);
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert(dsc_set_empty(set));
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
    dsc_set_clear(set);
    ck_assert_int_eq(dsc_get_last_error(), DSC_ERROR_INVALID_ARGUMENT);
}
END_TEST

Suite *dsc_set_suite(void)
{
    Suite *s = suite_create("dsc_set");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dsc_set_create_free);
    tcase_add_test(tc_core, test_dsc_set_insert);
    tcase_add_test(tc_core, test_dsc_set_erase);
    tcase_add_test(tc_core, test_dsc_set_contains);
    tcase_add_test(tc_core, test_dsc_set_size);
    tcase_add_test(tc_core, test_dsc_set_empty);
    tcase_add_test(tc_core, test_dsc_set_clear);
    tcase_add_test(tc_core, test_dsc_set_error_handling);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = dsc_set_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
