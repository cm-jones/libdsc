// SPDX-License-Identifier: GPL-3.0-or-later

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/dsc_vector.h"

void test_dsc_vector_init_deinit(void) {
    DSCVector **null_ptr = NULL;
    assert(dsc_vector_init(null_ptr, DSC_TYPE_BOOL) == DSC_ERROR_INVALID_ARGUMENT);
    
    DSCVector *vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_BOOL) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_CHAR) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_FLOAT) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_DOUBLE) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    vector = NULL;
    assert(dsc_vector_init(&vector, DSC_TYPE_STRING) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_size(void) {
    DSCVector *vector;
    size_t size;

    bool b = true;
    assert(dsc_vector_init(&vector, DSC_TYPE_BOOL) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    for (size_t i = 0; i < 100; ++i) {
        assert(dsc_vector_push_back(vector, &b) == DSC_ERROR_OK);
    }
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 100);
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    char c = 'a';
    assert(dsc_vector_init(&vector, DSC_TYPE_CHAR) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_push_back(vector, &c) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 1);
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    int i = 42;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_push_back(vector, &i) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 1);
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
    
    float f = 3.14f;
    assert(dsc_vector_init(&vector, DSC_TYPE_FLOAT) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_push_back(vector, &f) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 1);
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
    
    double d = 3.14159;
    assert(dsc_vector_init(&vector, DSC_TYPE_DOUBLE) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_push_back(vector, &d) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 1);
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_capacity(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);

    size_t capacity;
    assert(dsc_vector_capacity(vector, &capacity) == DSC_ERROR_OK);
    assert(capacity == DSC_VECTOR_INITIAL_CAPACITY);

    for (int i = 0; i <= DSC_VECTOR_INITIAL_CAPACITY; ++i) {
        assert(dsc_vector_push_back(vector, &i) == DSC_ERROR_OK);
    }

    assert(dsc_vector_capacity(vector, &capacity) == DSC_ERROR_OK);
    assert(capacity == 2 * DSC_VECTOR_INITIAL_CAPACITY);

    for (int i = 0; i <= 2 * DSC_VECTOR_INITIAL_CAPACITY; ++i) {
        assert(dsc_vector_push_back(vector, &i) == DSC_ERROR_OK);
    }

    assert(dsc_vector_capacity(vector, &capacity) == DSC_ERROR_OK);
    assert(capacity == 4 * DSC_VECTOR_INITIAL_CAPACITY);

    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_capacity(vector, &capacity) == DSC_ERROR_OK);
    assert(capacity == 4 * DSC_VECTOR_INITIAL_CAPACITY);
    
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_empty(void) {
    DSCVector *vector;
    bool empty;

    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_vector_empty(vector, &empty) == DSC_ERROR_OK);
    assert(empty == true);

    int value = 42;
    assert(dsc_vector_push_back(vector, &value) == DSC_ERROR_OK);
    assert(dsc_vector_empty(vector, &empty) == DSC_ERROR_OK);
    assert(empty == false);

    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_empty(vector, &empty) == DSC_ERROR_OK);
    assert(empty == true);

    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_at(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);

    for (int i = 0; i < 100; ++i) {
        assert(dsc_vector_push_back(vector, &i) == DSC_ERROR_OK);
    }

    int value;
    for (int i = 0; i < 100; ++i) {
        assert(dsc_vector_at(vector, i, &value) == DSC_ERROR_OK);
        assert(value == i);
    }

    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_front(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_STRING) == DSC_ERROR_OK);

    char s[] = "Hello, world!";
    char t[] = "Goodbye, world!";
    char *front = "";

    assert(dsc_vector_push_back(vector, &s) == DSC_ERROR_OK);
    assert(dsc_vector_front(vector, &front) == DSC_ERROR_OK);
    assert(strcmp(front, s) == 0);
    assert(dsc_vector_push_back(vector, &t) == DSC_ERROR_OK);
    assert(dsc_vector_front(vector, &front) == DSC_ERROR_OK);
    assert(strcmp(front, s) == 0);

    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_back(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        assert(dsc_vector_push_back(vector, &values[i]) == DSC_ERROR_OK);
    }
    
    int back_value;
    assert(dsc_vector_back(vector, &back_value) == DSC_ERROR_OK);
    assert(back_value == 50);
    
    // Test after pushing another value
    int new_value = 60;
    assert(dsc_vector_push_back(vector, &new_value) == DSC_ERROR_OK);
    assert(dsc_vector_back(vector, &back_value) == DSC_ERROR_OK);
    assert(back_value == 60);
    
    // Test error on empty vector
    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_back(vector, &back_value) == DSC_ERROR_EMPTY_CONTAINER);
    
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_push_back(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        assert(dsc_vector_push_back(vector, &values[i]) == DSC_ERROR_OK);
    }
    
    size_t size;
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 5);
    
    // Verify values
    int value;
    for (int i = 0; i < 5; i++) {
        assert(dsc_vector_at(vector, i, &value) == DSC_ERROR_OK);
        assert(value == values[i]);
    }
    
    // Test pushing many values to force resize
    for (int i = 0; i < 100; i++) {
        assert(dsc_vector_push_back(vector, &i) == DSC_ERROR_OK);
    }
    
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 105);
    
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_pop_back(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Test error on empty vector
    int popped;
    assert(dsc_vector_pop_back(vector, &popped) == DSC_ERROR_EMPTY_CONTAINER);
    
    // Add some values
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        assert(dsc_vector_push_back(vector, &values[i]) == DSC_ERROR_OK);
    }
    
    // Pop values in reverse order
    for (int i = 4; i >= 0; i--) {
        assert(dsc_vector_pop_back(vector, &popped) == DSC_ERROR_OK);
        assert(popped == values[i]);
    }
    
    size_t size;
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_insert_erase(void) {
    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    
    // Insert at empty vector (position 0)
    int value = 100;
    assert(dsc_vector_insert(vector, &value, 0) == DSC_ERROR_OK);
    
    // Insert at beginning
    value = 50;
    assert(dsc_vector_insert(vector, &value, 0) == DSC_ERROR_OK);
    
    // Insert at end
    value = 150;
    assert(dsc_vector_insert(vector, &value, 2) == DSC_ERROR_OK);
    
    // Insert in middle
    value = 75;
    assert(dsc_vector_insert(vector, &value, 1) == DSC_ERROR_OK);
    
    // Check expected sequence: 50, 75, 100, 150
    int expected[] = {50, 75, 100, 150};
    int retrieved;
    for (int i = 0; i < 4; i++) {
        assert(dsc_vector_at(vector, i, &retrieved) == DSC_ERROR_OK);
        assert(retrieved == expected[i]);
    }
    
    // Test erase from beginning
    assert(dsc_vector_erase(vector, 0) == DSC_ERROR_OK);
    
    // Check expected sequence: 75, 100, 150
    expected[0] = 75;
    expected[1] = 100;
    expected[2] = 150;
    
    for (int i = 0; i < 3; i++) {
        assert(dsc_vector_at(vector, i, &retrieved) == DSC_ERROR_OK);
        assert(retrieved == expected[i]);
    }
    
    // Test erase from middle
    assert(dsc_vector_erase(vector, 1) == DSC_ERROR_OK);
    
    // Check expected sequence: 75, 150
    expected[1] = 150;
    
    for (int i = 0; i < 2; i++) {
        assert(dsc_vector_at(vector, i, &retrieved) == DSC_ERROR_OK);
        assert(retrieved == expected[i]);
    }
    
    // Test erase from end
    assert(dsc_vector_erase(vector, 1) == DSC_ERROR_OK);
    
    // Only 75 should remain
    assert(dsc_vector_at(vector, 0, &retrieved) == DSC_ERROR_OK);
    assert(retrieved == 75);
    
    size_t size;
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 1);
    
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);
}

void test_dsc_vector_clear(void) {
    DSCVector *vector;
    int value;

    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);

    for (size_t i = 0; i < 100; ++i) {
        value = i * i;
        assert(dsc_vector_push_back(vector, &value) == DSC_ERROR_OK);
    }

    size_t size;
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 100);

    assert(dsc_vector_clear(vector) == DSC_ERROR_OK);
    assert(dsc_vector_size(vector, &size) == DSC_ERROR_OK);
    assert(size == 0);
    assert(dsc_vector_at(vector, 0, &value) == DSC_ERROR_OUT_OF_RANGE);
}

int main(void) {
    test_dsc_vector_init_deinit();
    test_dsc_vector_size();
    test_dsc_vector_capacity();
    test_dsc_vector_empty();
    test_dsc_vector_at();
    test_dsc_vector_front();
    test_dsc_vector_back();
    test_dsc_vector_push_back();
    test_dsc_vector_pop_back();
    test_dsc_vector_insert_erase();
    test_dsc_vector_clear();

    printf("All tests passed!\n");

    return 0;
}
