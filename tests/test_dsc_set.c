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
    enum dsc_error_t error = dsc_set_destroy(set);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
}
END_TEST

START_TEST(test_dsc_set_add)
{
    struct dsc_set_t *set = dsc_set_create();

    enum dsc_error_t error = dsc_set_add(set, 10);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    unsigned int size;
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 1);

    error = dsc_set_add(set, 20);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 2);

    error = dsc_set_add(set, 10);
    ck_assert_int_eq(error, DSC_ERROR_VALUE_ALREADY_EXISTS);
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 2);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_remove)
{
    struct dsc_set_t *set = dsc_set_create();

    dsc_set_add(set, 10);
    dsc_set_add(set, 20);

    enum dsc_error_t error = dsc_set_remove(set, 10);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    unsigned int size;
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 1);

    error = dsc_set_remove(set, 30);
    ck_assert_int_eq(error, DSC_ERROR_VALUE_NOT_FOUND);
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 1);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_contains)
{
    struct dsc_set_t *set = dsc_set_create();

    dsc_set_add(set, 10);
    dsc_set_add(set, 20);

    bool result;
    enum dsc_error_t error = dsc_set_contains(set, 10, &result);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert(result);

    error = dsc_set_contains(set, 20, &result);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert(result);

    error = dsc_set_contains(set, 30, &result);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert(!result);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_get_size)
{
    struct dsc_set_t *set = dsc_set_create();

    unsigned int size;
    enum dsc_error_t error = dsc_set_get_size(set, &size);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert_int_eq(size, 0);

    dsc_set_add(set, 10);
    error = dsc_set_get_size(set, &size);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert_int_eq(size, 1);

    dsc_set_add(set, 20);
    error = dsc_set_get_size(set, &size);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert_int_eq(size, 2);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_is_empty)
{
    struct dsc_set_t *set = dsc_set_create();

    bool result;
    enum dsc_error_t error = dsc_set_is_empty(set, &result);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert(result);

    dsc_set_add(set, 10);
    error = dsc_set_is_empty(set, &result);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    ck_assert(!result);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_clear)
{
    struct dsc_set_t *set = dsc_set_create();

    dsc_set_add(set, 10);
    dsc_set_add(set, 20);
    dsc_set_add(set, 30);
    unsigned int size;
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 3);

    enum dsc_error_t error = dsc_set_clear(set);
    ck_assert_int_eq(error, DSC_ERROR_NONE);
    dsc_set_get_size(set, &size);
    ck_assert_int_eq(size, 0);

    dsc_set_destroy(set);
}
END_TEST

START_TEST(test_dsc_set_null_parameter)
{
    bool result;
    unsigned int size;

    ck_assert_int_eq(dsc_set_destroy(NULL), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_add(NULL, 10), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_remove(NULL, 10), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_contains(NULL, 10, &result), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_contains(dsc_set_create(), 10, NULL), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_get_size(NULL, &size), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_get_size(dsc_set_create(), NULL), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_is_empty(NULL, &result), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_is_empty(dsc_set_create(), NULL), DSC_ERROR_INVALID_ARGUMENT);
    ck_assert_int_eq(dsc_set_clear(NULL), DSC_ERROR_INVALID_ARGUMENT);
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
    tcase_add_test(tc_core, test_dsc_set_null_parameter);

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
