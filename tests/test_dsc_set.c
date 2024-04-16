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

START_TEST(test_dsc_set_create_destroy)
{
    struct dsc_set_t *set = dsc_set_create();
    ck_assert_ptr_nonnull(set);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);
    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_add)
{
    struct dsc_set_t *set = dsc_set_create();

    set = dsc_set_add(set, 10);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);
    ck_assert_int_eq(dsc_set_get_size(set), 1);

    set = dsc_set_add(set, 20);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);
    ck_assert_int_eq(dsc_set_get_size(set), 2);

    set = dsc_set_add(set, 10);
    ck_assert_int_eq(set->error, DSC_ERROR_VALUE_ALREADY_EXISTS);
    ck_assert_int_eq(dsc_set_get_size(set), 2);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_remove)
{
    struct dsc_set_t *set = dsc_set_create();

    set = dsc_set_add(set, 10);
    set = dsc_set_add(set, 20);

    set = dsc_set_remove(set, 10);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);
    ck_assert_int_eq(dsc_set_get_size(set), 1);

    set = dsc_set_remove(set, 30);
    ck_assert_int_eq(set->error, DSC_ERROR_VALUE_NOT_FOUND);
    ck_assert_int_eq(dsc_set_get_size(set), 1);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_contains)
{
    struct dsc_set_t *set = dsc_set_create();

    set = dsc_set_add(set, 10);
    set = dsc_set_add(set, 20);

    set = dsc_set_contains(set, 10);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);

    set = dsc_set_contains(set, 20);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);

    set = dsc_set_contains(set, 30);
    ck_assert_int_eq(set->error, DSC_ERROR_VALUE_NOT_FOUND);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_get_size)
{
    struct dsc_set_t *set = dsc_set_create();

    ck_assert_int_eq(dsc_set_get_size(set), 0);

    set = dsc_set_add(set, 10);
    ck_assert_int_eq(dsc_set_get_size(set), 1);

    set = dsc_set_add(set, 20);
    ck_assert_int_eq(dsc_set_get_size(set), 2);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_is_empty)
{
    struct dsc_set_t *set = dsc_set_create();

    set = dsc_set_is_empty(set);
    ck_assert_int_eq(set->error, DSC_ERROR_EMPTY_SET);

    set = dsc_set_add(set, 10);
    set = dsc_set_is_empty(set);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_clear)
{
    struct dsc_set_t *set = dsc_set_create();

    set = dsc_set_add(set, 10);
    set = dsc_set_add(set, 20);
    set = dsc_set_add(set, 30);
    ck_assert_int_eq(dsc_set_get_size(set), 3);

    set = dsc_set_clear(set);
    ck_assert_int_eq(set->error, DSC_ERROR_NONE);
    ck_assert_int_eq(dsc_set_get_size(set), 0);

    dsc_set_destroy(set);
}
END_TEST

Suite *dsc_set_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("DSC Set");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dsc_set_create_destroy);
    tcase_add_test(tc_core, test_dsc_set_add);
    tcase_add_test(tc_core, test_dsc_set_remove);
    tcase_add_test(tc_core, test_dsc_set_contains);
    tcase_add_test(tc_core, test_dsc_set_get_size);
    tcase_add_test(tc_core, test_dsc_set_is_empty);
    tcase_add_test(tc_core, test_dsc_set_clear);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = dsc_set_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}