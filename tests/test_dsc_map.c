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

#include "../include/dsc_map.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_map_create)
{
    struct dsc_map_t *map = dsc_map_create();
    ck_assert_ptr_nonnull(map);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_insert)
{
    struct dsc_map_t *map = dsc_map_create();
    int key = 42;
    int value = 73;
    ck_assert_int_eq(dsc_map_insert(map, key, value), true);
    ck_assert_int_eq(dsc_map_get(map, key), value);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_insert_duplicate)
{
    struct dsc_map_t *map = dsc_map_create();
    int key = 42;
    int value1 = 73;
    int value2 = 84;
    dsc_map_insert(map, key, value1);
    ck_assert_int_eq(dsc_map_insert(map, key, value2), false);
    ck_assert_int_eq(dsc_map_get(map, key), value1);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_erase)
{
    struct dsc_map_t *map = dsc_map_create();
    int key = 42;
    int value = 73;
    dsc_map_insert(map, key, value);
    ck_assert_int_eq(dsc_map_erase(map, key), true);
    ck_assert_int_eq(dsc_map_get(map, key), 0);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_erase_nonexistent)
{
    struct dsc_map_t *map = dsc_map_create();
    int key = 42;
    ck_assert_int_eq(dsc_map_erase(map, key), false);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_contains)
{
    struct dsc_map_t *map = dsc_map_create();
    int key = 42;
    int value = 73;
    dsc_map_insert(map, key, value);
    ck_assert_int_eq(dsc_map_contains(map, key), true);
    ck_assert_int_eq(dsc_map_contains(map, 84), false);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_size)
{
    struct dsc_map_t *map = dsc_map_create();
    ck_assert_int_eq(dsc_map_size(map), 0);
    dsc_map_insert(map, 42, 73);
    ck_assert_int_eq(dsc_map_size(map), 1);
    dsc_map_insert(map, 84, 21);
    ck_assert_int_eq(dsc_map_size(map), 2);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_empty)
{
    struct dsc_map_t *map = dsc_map_create();
    ck_assert_int_eq(dsc_map_empty(map), true);
    dsc_map_insert(map, 42, 73);
    ck_assert_int_eq(dsc_map_empty(map), false);
    dsc_map_free(map);
}
END_TEST

START_TEST(test_dsc_map_clear)
{
    struct dsc_map_t *map = dsc_map_create();
    dsc_map_insert(map, 42, 73);
    dsc_map_insert(map, 84, 21);
    dsc_map_clear(map);
    ck_assert_int_eq(dsc_map_size(map), 0);
    dsc_map_free(map);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_map_suite(void) {
    Suite *suite = suite_create("dsc_map");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_map_create);
    tcase_add_test(tcase, test_dsc_map_insert);
    tcase_add_test(tcase, test_dsc_map_insert_duplicate);
    tcase_add_test(tcase, test_dsc_map_erase);
    tcase_add_test(tcase, test_dsc_map_erase_nonexistent);
    tcase_add_test(tcase, test_dsc_map_contains);
    tcase_add_test(tcase, test_dsc_map_size);
    tcase_add_test(tcase, test_dsc_map_empty);
    tcase_add_test(tcase, test_dsc_map_clear);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_map_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
