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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/dsc_vector.h"

void test_dsc_vector_init_deinit(void) {
    assert(dsc_vector_init(NULL, DSC_TYPE_BOOL) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_vector_init(NULL, DSC_TYPE_CHAR) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_vector_init(NULL, DSC_TYPE_INT) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_vector_init(NULL, DSC_TYPE_FLOAT) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_vector_init(NULL, DSC_TYPE_DOUBLE) == DSC_ERROR_INVALID_ARGUMENT);
    assert(dsc_vector_init(NULL, DSC_TYPE_STRING) == DSC_ERROR_INVALID_ARGUMENT);

    DSCVector *vector;
    assert(dsc_vector_init(&vector, DSC_TYPE_BOOL) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    assert(dsc_vector_init(&vector, DSC_TYPE_CHAR) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    assert(dsc_vector_init(&vector, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    assert(dsc_vector_init(&vector, DSC_TYPE_FLOAT) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

    assert(dsc_vector_init(&vector, DSC_TYPE_DOUBLE) == DSC_ERROR_OK);
    assert(dsc_vector_deinit(vector) == DSC_ERROR_OK);

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
    
}

void test_dsc_vector_push_back(void) {

}

void test_dsc_vector_pop_back(void) {

}

void test_dsc_vector_insert_erase(void) {
    
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
