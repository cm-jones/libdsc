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

#include "../include/dsc_vector.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_vector_create)
{
    dsc_vector_t *vector = dsc_vector_create();
    ck_assert_ptr_nonnull(vector);
    ck_assert_int_eq(dsc_vector_empty(vector), true);
    ck_assert_int_eq(dsc_vector_size(vector), 0);
    ck_assert_int_eq(dsc_vector_capacity(vector), DSC_VECTOR_INITIAL_CAPACITY);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_free)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_free(vector);
    /* No assertion needed, just ensuring no memory leaks or crashes */
}
END_TEST

START_TEST(test_dsc_vector_push_back)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    ck_assert_int_eq(dsc_vector_size(vector), 3);
    ck_assert_int_eq(dsc_vector_at(vector, 0), 1);
    ck_assert_int_eq(dsc_vector_at(vector, 1), 2);
    ck_assert_int_eq(dsc_vector_at(vector, 2), 3);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_pop_back)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    dsc_vector_pop_back(vector);
    ck_assert_int_eq(dsc_vector_size(vector), 2);
    ck_assert_int_eq(dsc_vector_at(vector, 0), 1);
    ck_assert_int_eq(dsc_vector_at(vector, 1), 2);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_insert)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    size_t position = dsc_vector_insert(vector, 1, 10);
    ck_assert_int_eq(position, 1);
    ck_assert_int_eq(dsc_vector_size(vector), 4);
    ck_assert_int_eq(dsc_vector_at(vector, 0), 1);
    ck_assert_int_eq(dsc_vector_at(vector, 1), 10);
    ck_assert_int_eq(dsc_vector_at(vector, 2), 2);
    ck_assert_int_eq(dsc_vector_at(vector, 3), 3);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_erase)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    dsc_vector_erase(vector, 1);
    ck_assert_int_eq(dsc_vector_size(vector), 2);
    ck_assert_int_eq(dsc_vector_at(vector, 0), 1);
    ck_assert_int_eq(dsc_vector_at(vector, 1), 3);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_at)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_push_back(vector, 1);
    dsc_vector_push_back(vector, 2);
    dsc_vector_push_back(vector, 3);
    ck_assert_int_eq(dsc_vector_at(vector, 0), 1);
    ck_assert_int_eq(dsc_vector_at(vector, 1), 2);
    ck_assert_int_eq(dsc_vector_at(vector, 2), 3);
    ck_assert_int_eq(dsc_vector_at(vector, 3), 0); /* Out of bounds */
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_empty)
{
    dsc_vector_t *vector = dsc_vector_create();
    ck_assert_int_eq(dsc_vector_empty(vector), true);
    dsc_vector_push_back(vector, 1);
    ck_assert_int_eq(dsc_vector_empty(vector), false);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_size)
{
    dsc_vector_t *vector = dsc_vector_create();
    ck_assert_int_eq(dsc_vector_size(vector), 0);
    dsc_vector_push_back(vector, 1);
    ck_assert_int_eq(dsc_vector_size(vector), 1);
    dsc_vector_push_back(vector, 2);
    ck_assert_int_eq(dsc_vector_size(vector), 2);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_capacity)
{
    dsc_vector_t *vector = dsc_vector_create();
    ck_assert_int_eq(dsc_vector_capacity(vector), DSC_VECTOR_INITIAL_CAPACITY);
    dsc_vector_reserve(vector, 100);
    ck_assert_int_eq(dsc_vector_capacity(vector), 100);
    dsc_vector_free(vector);
}
END_TEST

START_TEST(test_dsc_vector_reserve)
{
    dsc_vector_t *vector = dsc_vector_create();
    dsc_vector_reserve(vector, 100);
    ck_assert_int_eq(dsc_vector_capacity(vector), 100);
    dsc_vector_free(vector);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_vector_suite(void) {
    Suite *suite = suite_create("dsc_vector");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_vector_create);
    tcase_add_test(tcase, test_dsc_vector_free);
    tcase_add_test(tcase, test_dsc_vector_push_back);
    tcase_add_test(tcase, test_dsc_vector_pop_back);
    tcase_add_test(tcase, test_dsc_vector_insert);
    tcase_add_test(tcase, test_dsc_vector_erase);
    tcase_add_test(tcase, test_dsc_vector_at);
    tcase_add_test(tcase, test_dsc_vector_empty);
    tcase_add_test(tcase, test_dsc_vector_size);
    tcase_add_test(tcase, test_dsc_vector_capacity);
    tcase_add_test(tcase, test_dsc_vector_reserve);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_vector_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
