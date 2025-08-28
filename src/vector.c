// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/vector.h"

#include <assert.h>

#define DSC_VECTOR_INITIAL_CAPACITY 16

DSCVector *vector_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    DSCVector *vector = dsc_malloc(sizeof(DSCVector));
    if (vector == NULL) {
        return NULL;
    }

    vector->data = dsc_malloc(element_size * DSC_VECTOR_INITIAL_CAPACITY);
    if (vector->data == NULL) {
        dsc_free(vector);
        return NULL;
    }

    vector->size = 0;
    vector->capacity = DSC_VECTOR_INITIAL_CAPACITY;
    vector->element_size = element_size;

    return vector;
}

void vector_destroy(DSCVector *vector) {
    if (vector == NULL) {
        return;
    }

    dsc_free(vector->data);
    dsc_free(vector);
}

size_t vector_size(const DSCVector *vector) {
    return vector ? vector->size : 0;
}

bool vector_empty(const DSCVector *vector) {
    return vector ? vector->size == 0 : true;
}

size_t vector_capacity(const DSCVector *vector) {
    return vector ? vector->capacity : 0;
}

DSCError vector_reserve(DSCVector *vector, size_t n) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (n <= vector->capacity) {
        return DSC_ERROR_OK;
    }

    void *new_data = dsc_realloc(vector->data, n * vector->element_size);
    if (new_data == NULL) return DSC_ERROR_MEMORY;

    vector->data = new_data;
    vector->capacity = n;
    return DSC_ERROR_OK;
}

DSCError vector_resize(DSCVector *vec, size_t n) {
    if (vec == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (n > vec->capacity) {
        DSCError err = vector_reserve(vec, n);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    vec->size = n;
    return DSC_ERROR_OK;
}

DSCError vector_push_back(DSCVector *vector, const void *element) {
    if (!vector || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        DSCError err = vector_reserve(vec, new_capacity);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    void *dest = (char *) vector->data + (vector->size * vector->element_size);
    memcpy(dest, element, vector->element_size);
    ++(vector->size);

    return DSC_ERROR_OK;
}

DSCError vector_pop_back(DSCVector *vector) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    vector->size--;
    return DSC_ERROR_OK;
}

void *vector_at(DSCVector *vec, size_t index) {
    if (!vec || index >= vec->size) {
        return NULL;
    }

    return (char *) vec->data + (index * vec->element_size);
}

void *vector_front(DSCVector *vec)
{
    return vector_at(vec, 0);
}

void *vector_back(DSCVector *vector)
{
    if (vector == NULL || vec->size == 0) {
        return NULL;
    }

    return vector_at(vector, vector->size - 1);
}

DSCError vector_insert(DSCVector *vec, size_t index, void const *element)
{
    if (!vec || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (index > vec->size) {
        return DSC_ERROR_NOT_FOUND;
    }

    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        DSCError err = vector_reserve(vec, new_capacity);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    // Move elements to make space
    if (index < vec->size) {
        void *dest = (char *)vec->data + ((index + 1) * vec->element_size);
        void *src = (char *)vec->data + (index * vec->element_size);
        size_t bytes_to_move = (vec->size - index) * vec->element_size;
        memmove(dest, src, bytes_to_move);
    }

    // Insert the new element
    void *dest = (char *) vec->data + (index * vec->element_size);
    memcpy(dest, element, vec->element_size);
    ++(vec->size);

    return DSC_ERROR_OK;
}

DSCError vector_erase(DSCVector *vec, size_t index) {
    if (!vec) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (index >= vec->size) {
        return DSC_ERROR_NOT_FOUND;
    }

    if (index < vec->size - 1) {
        void *dest = (char *)vec->data + (index * vec->element_size);
        void *src = (char *)vec->data + ((index + 1) * vec->element_size);
        size_t bytes_to_move = (vec->size - index - 1) * vec->element_size;
        memmove(dest, src, bytes_to_move);
    }

    vec->size--;
    return DSC_ERROR_OK;
}

void vector_clear(DSCVector *vector) {
    if (vector != NULL)
        vector->size = 0;
}

DSCError vector_shrink_to_fit(DSCVector *vec) {
    if (!vec) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vec->size == vec->capacity) {
        return DSC_ERROR_OK;
    }

    void *new_data = dsc_realloc(vec->data, vec->size * vec->element_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    vec->data = new_data;
    vec->capacity = vec->size;
    return DSC_ERROR_OK;
}
