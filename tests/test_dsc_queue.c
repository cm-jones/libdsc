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

#include "../include/dsc_queue.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_queue_create)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    ck_assert_ptr_nonnull(queue);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_push)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    ck_assert_int_eq(dsc_queue_front(queue), 42);
    ck_assert_int_eq(dsc_queue_back(queue), 73);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_pop)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    dsc_queue_pop(queue);
    ck_assert_int_eq(dsc_queue_front(queue), 73);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_front)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    ck_assert_int_eq(dsc_queue_front(queue), 42);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_back)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    dsc_queue_push(queue, 42);
    dsc_queue_push(queue, 73);
    ck_assert_int_eq(dsc_queue_back(queue), 73);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_empty)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    ck_assert_int_eq(dsc_queue_empty(queue), true);
    dsc_queue_push(queue, 42);
    ck_assert_int_eq(dsc_queue_empty(queue), false);
    dsc_queue_free(queue);
}
END_TEST

START_TEST(test_dsc_queue_size)
{
    struct dsc_queue_t *queue = dsc_queue_create();
    ck_assert_int_eq(dsc_queue_size(queue), 0);
    dsc_queue_push(queue, 42);
    ck_assert_int_eq(dsc_queue_size(queue), 1);
    dsc_queue_push(queue, 73);
    ck_assert_int_eq(dsc_queue_size(queue), 2);
    dsc_queue_free(queue);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_queue_suite(void) {
    Suite *suite = suite_create("dsc_queue");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_queue_create);
    tcase_add_test(tcase, test_dsc_queue_push);
    tcase_add_test(tcase, test_dsc_queue_pop);
    tcase_add_test(tcase, test_dsc_queue_front);
    tcase_add_test(tcase, test_dsc_queue_back);
    tcase_add_test(tcase, test_dsc_queue_empty);
    tcase_add_test(tcase, test_dsc_queue_size);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_queue_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
