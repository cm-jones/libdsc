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
#include "../include/dsc_list.h"

START_TEST(test_dsc_list_create)
{
    struct dsc_list_t *list = dsc_list_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_create_with_error)
{
    struct dsc_list_t *list = dsc_list_create_with_error(DSC_ERROR_OUT_OF_MEMORY);
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_int_eq(list->error, DSC_ERROR_OUT_OF_MEMORY);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_destroy)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_prepend(list, 1);
    list = dsc_list_prepend(list, 2);
    list = dsc_list_destroy(list);
    ck_assert_ptr_null(list);
}
END_TEST

START_TEST(test_dsc_list_prepend)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_prepend(list, 1);
    list = dsc_list_prepend(list, 2);
    ck_assert_int_eq(list->head->value, 2);
    ck_assert_int_eq(list->head->next->value, 1);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_append)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_insert(list, 1, 0);
    list = dsc_list_insert(list, 2, 1);
    list = dsc_list_insert(list, 3, 1);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->head->next->next->value, 2);

    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert_before)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_insert_before(list, list->head->next, 3);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->head->next->next->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert_after)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_insert_after(list, list->head, 3);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->head->next->next->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_delete_head)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_delete_head(list);
    ck_assert_int_eq(list->head->value, 2);
    ck_assert_ptr_null(list->head->next);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_delete_tail)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_delete_tail(list);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_ptr_null(list->head->next);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_delete_at_position)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    list = dsc_list_delete_at_position(list, 1);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_remove_first_occurrence)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    list = dsc_list_remove_first_occurrence(list, 2);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 2);
    ck_assert_int_eq(list->head->next->next->value, 3);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_remove_all_occurrences)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    list = dsc_list_remove_all_occurrences(list, 2);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_reverse)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    list = dsc_list_reverse(list);
    ck_assert_int_eq(list->head->value, 3);
    ck_assert_int_eq(list->head->next->value, 2);
    ck_assert_int_eq(list->head->next->next->value, 1);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_search)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    struct dsc_node_t *node = dsc_list_search(list, 2);
    ck_assert_ptr_nonnull(node);
    ck_assert_int_eq(node->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_count)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    int count = dsc_list_count(list, 2);
    ck_assert_int_eq(count, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_is_empty)
{
    struct dsc_list_t *list = dsc_list_create();
    ck_assert(dsc_list_is_empty(list));
    list = dsc_list_append(list, 1);
    ck_assert(!dsc_list_is_empty(list));
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_length)
{
    struct dsc_list_t *list = dsc_list_create();
    ck_assert_int_eq(dsc_list_get_length(list), 0);
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    ck_assert_int_eq(dsc_list_get_length(list), 3);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_nth_node)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    list = dsc_list_append(list, 3);
    struct dsc_node_t *node = dsc_list_get_nth_node(list, 1);
    ck_assert_ptr_nonnull(node);
    ck_assert_int_eq(node->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_head)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    struct dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_ptr_nonnull(head);
    ck_assert_int_eq(head->value, 1);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_tail)
{
    struct dsc_list_t *list = dsc_list_create();
    list = dsc_list_append(list, 1);
    list = dsc_list_append(list, 2);
    struct dsc_node_t *tail = dsc_list_get_tail(list);
    ck_assert_ptr_nonnull(tail);
    ck_assert_int_eq(tail->value, 2);
    dsc_list_destroy(list);
}
END_TEST

Suite *dsc_list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("DSC List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dsc_list_create);
    tcase_add_test(tc_core, test_dsc_list_create_with_error);
    tcase_add_test(tc_core, test_dsc_list_destroy);
    tcase_add_test(tc_core, test_dsc_list_prepend);
    tcase_add_test(tc_core, test_dsc_list_append);
    tcase_add_test(tc_core, test_dsc_list_insert);
    tcase_add_test(tc_core, test_dsc_list_insert_before);
    tcase_add_test(tc_core, test_dsc_list_insert_after);
    tcase_add_test(tc_core, test_dsc_list_delete_head);
    tcase_add_test(tc_core, test_dsc_list_delete_tail);
    tcase_add_test(tc_core, test_dsc_list_delete_at_position);
    tcase_add_test(tc_core, test_dsc_list_remove_first_occurrence);
    tcase_add_test(tc_core, test_dsc_list_remove_all_occurrences);
    tcase_add_test(tc_core, test_dsc_list_reverse);
    tcase_add_test(tc_core, test_dsc_list_search);
    tcase_add_test(tc_core, test_dsc_list_count);
    tcase_add_test(tc_core, test_dsc_list_is_empty);
    tcase_add_test(tc_core, test_dsc_list_get_length);
    tcase_add_test(tc_core, test_dsc_list_get_nth_node);
    tcase_add_test(tc_core, test_dsc_list_get_head);
    tcase_add_test(tc_core, test_dsc_list_get_tail);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = dsc_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
