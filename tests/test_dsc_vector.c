#include <assert.h>
#include <stdio.h>

#include "../include/dsc_vector.h"

void run_test(void (*test_func)(void), const char *name) {
    printf("%s: ", name);
    test_func();
    printf("\033[32mpassed\033[0m\n");
}

void test_dsc_vector_init_deinit(void) {
    DSCVector vector_char = dsc_vector_init(DSC_TYPE_CHAR);
    assert(vector_char);
    assert(dsc_vector_is_empty(vector_char));
    assert(dsc_vector_deinit(vector_char));

    DSCVector vector_int = dsc_vector_init(DSC_TYPE_INT);
    assert(vector_int);
    assert(dsc_vector_is_empty(vector_int));
    assert(dsc_vector_deinit(vector_int));

    DSCVector vector_float = dsc_vector_init(DSC_TYPE_FLOAT);
    assert(vector_float);
    assert(dsc_vector_is_empty(vector_float));
    assert(dsc_vector_deinit(vector_float));

    DSCVector vector_double = dsc_vector_init(DSC_TYPE_DOUBLE);
    assert(vector_double);
    assert(dsc_vector_is_empty(vector_double));
    assert(dsc_vector_deinit(vector_double));

    DSCVector vector_bool = dsc_vector_init(DSC_TYPE_BOOL);
    assert(vector_bool);
    assert(dsc_vector_is_empty(vector_bool));
    assert(dsc_vector_deinit(vector_bool));
}

void test_dsc_vector_clear(void) {
    DSCVector vector = dsc_vector_init(DSC_TYPE_INT);
    assert(vector);
    assert(dsc_vector_is_empty(vector));
    int data1 = 5;
    int data2 = 10;
    dsc_vector_push_back(vector, &data1);
    assert(dsc_vector_size(vector) == 1);
    dsc_vector_push_back(vector, &data2);
    assert(dsc_vector_size(vector) == 2);
    assert(dsc_vector_clear(vector));
    assert(dsc_vector_size(vector) == 0);
    dsc_vector_deinit(vector);
}

void test_dsc_vector_error(void) {
    DSCVector vector = dsc_vector_init(DSC_TYPE_INT);
    assert(dsc_vector_error(vector) == DSC_ERROR_OK);
    char data = 'a';
    dsc_vector_push_back(vector, &data);
    assert(dsc_vector_error(vector) == DSC_ERROR_TYPE_MISMATCH);
    dsc_vector_deinit(vector);
}

int main(void) {
    printf("\n");
    run_test(test_dsc_vector_init_deinit, "test_dsc_vector_init_deinit");
    run_test(test_dsc_vector_clear, "test_dsc_vector_clear");
    run_test(test_dsc_vector_error, "test_dsc_vector_error");
    printf("All tests passed!\n");
    return 0;
}
