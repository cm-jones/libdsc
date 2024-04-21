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

#include "../include/dsc_stack.h"

/* Setup and teardown functions */
void setup(void) {
    /* No setup needed */
}

void teardown(void) {
    /* No teardown needed */
}

/* Test cases */

START_TEST(test_dsc_stack_create)
{
    dsc_stack_t *stack = dsc_stack_create();
    ck_assert_ptr_nonnull(stack);
    dsc_stack_free(stack);
}
END_TEST

START_TEST(test_dsc_stack_push)
{
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    dsc_stack_push(stack, 73);
    ck_assert_int_eq(dsc_stack_top(stack), 73);
    dsc_stack_free(stack);
}
END_TEST

START_TEST(test_dsc_stack_pop)
{
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    dsc_stack_push(stack, 73);
    dsc_stack_pop(stack);
    ck_assert_int_eq(dsc_stack_top(stack), 42);
    dsc_stack_free(stack);
}
END_TEST

START_TEST(test_dsc_stack_top)
{
    dsc_stack_t *stack = dsc_stack_create();
    dsc_stack_push(stack, 42);
    ck_assert_int_eq(dsc_stack_top(stack), 42);
    dsc_stack_free(stack);
}
END_TEST

START_TEST(test_dsc_stack_empty)
{
    dsc_stack_t *stack = dsc_stack_create();
    ck_assert_int_eq(dsc_stack_empty(stack), true);
    dsc_stack_push(stack, 42);
    ck_assert_int_eq(dsc_stack_empty(stack), false);
    dsc_stack_free(stack);
}
END_TEST

START_TEST(test_dsc_stack_size)
{
    ck_assert_int_eq(dsc_stack_size(NULL), -1);
    dsc_stack_t *stack = dsc_stack_create();
    ck_assert_int_eq(dsc_stack_size(stack), 0);
    dsc_stack_push(stack, 42);
    ck_assert_int_eq(dsc_stack_size(stack), 1);
    dsc_stack_push(stack, 73);
    ck_assert_int_eq(dsc_stack_size(stack), 2);
    dsc_stack_free(stack);
}
END_TEST

/* Suite setup and teardown functions */
Suite *dsc_stack_suite(void) {
    Suite *suite = suite_create("dsc_stack");
    TCase *tcase = tcase_create("core");

    tcase_add_checked_fixture(tcase, setup, teardown);
    tcase_add_test(tcase, test_dsc_stack_create);
    tcase_add_test(tcase, test_dsc_stack_push);
    tcase_add_test(tcase, test_dsc_stack_pop);
    tcase_add_test(tcase, test_dsc_stack_top);
    tcase_add_test(tcase, test_dsc_stack_empty);
    tcase_add_test(tcase, test_dsc_stack_size);

    suite_add_tcase(suite, tcase);
    return suite;
}

/* Main function */
int main(void) {
    int failed;
    Suite *suite = dsc_stack_suite();
    SRunner *runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
