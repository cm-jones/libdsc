#include <check.h>
#include "../include/dsc_list.h"

START_TEST(test_dsc_list_create) {
    struct dsc_list_t *list = dsc_list_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_int_eq(list->error, DSC_ERROR_NONE);
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
    return (number_failed == 0) ? 0 : 1;
}
