#include <check.h>
#include <stdlib.h>

#include "../include/dsc_list.h"

START_TEST(test_dsc_list_create) {
    struct dsc_list_t *list = dsc_list_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert_after)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    struct dsc_node_t *node = dsc_list_search(list, 1);
    dsc_list_insert_after(list, node, 3);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->head->next->next->value, 2);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_insert_before)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    struct dsc_node_t *node = dsc_list_search(list, 2);
    dsc_list_insert_before(list, node, 3);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->head->next->next->value, 2);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_delete_at_position)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    dsc_list_append(list, 3);
    dsc_list_delete_at_position(list, 1);
    ck_assert_int_eq(list->head->value, 1);
    ck_assert_int_eq(list->head->next->value, 3);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_print)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    dsc_list_append(list, 3);
    dsc_list_print(list);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_nth_node)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    dsc_list_append(list, 3);
    struct dsc_node_t *node = dsc_list_get_nth_node(list, 1);
    ck_assert_int_eq(node->value, 2);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_head)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    struct dsc_node_t *head = dsc_list_get_head(list);
    ck_assert_int_eq(head->value, 1);
    dsc_list_destroy(list);
}
END_TEST

START_TEST(test_dsc_list_get_tail)
{
    struct dsc_list_t *list = dsc_list_create();
    dsc_list_append(list, 1);
    dsc_list_append(list, 2);
    struct dsc_node_t *tail = dsc_list_get_tail(list);
    ck_assert_int_eq(tail->value, 2);
    dsc_list_destroy(list);
}
END_TEST

// Add more test cases for other functions

Suite *list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dsc_list_create);
    tcase_add_test(tc_core, test_dsc_list_insert_after);
    tcase_add_test(tc_core, test_dsc_list_insert_before);
    tcase_add_test(tc_core, test_dsc_list_delete_at_position);
    tcase_add_test(tc_core, test_dsc_list_print);
    tcase_add_test(tc_core, test_dsc_list_get_nth_node);
    tcase_add_test(tc_core, test_dsc_list_get_head);
    tcase_add_test(tc_core, test_dsc_list_get_tail);

    // Add more test cases to the test case

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
