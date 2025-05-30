// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/vector.h"

#include <assert.h>

#define VECTOR_INITIAL_CAPACITY 16

dsc_vector *vector_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }

    dsc_vector *vec = dsc_malloc(sizeof(dsc_vector));
    if (!vec) {
        return NULL;
    }

    vec->data = dsc_malloc(element_size * VECTOR_INITIAL_CAPACITY);
    if (!vec->data) {
        dsc_free(vec);
        return NULL;
    }

    vec->size = 0;
    vec->capacity = VECTOR_INITIAL_CAPACITY;
    vec->element_size = element_size;

    return vec;
}

void vector_destroy(dsc_vector *vec) {
    if (!vec) {
        return;
    }

    dsc_free(vec->data);
    dsc_free(vec);
}

size_t vector_size(dsc_vector const *vec) { return vec ? vec->size : 0; }

bool vector_empty(dsc_vector const *vec) {
    return vec ? vec->size == 0 : true;
}

size_t vector_capacity(dsc_vector const *vec) {
    return vec ? vec->capacity : 0;
}

dsc_error vector_reserve(dsc_vector *vec, size_t n) {
    if (!vec) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (n <= vec->capacity) {
        return DSC_ERROR_OK;
    }

    void *new_data = dsc_realloc(vec->data, n * vec->element_size);
    if (!new_data) {
        return DSC_ERROR_MEMORY;
    }

    vec->data = new_data;
    vec->capacity = n;
    return DSC_ERROR_OK;
}

dsc_error vector_resize(dsc_vector *vec, size_t n) {
    if (!vec) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (n > vec->capacity) {
        dsc_error err = vector_reserve(vec, n);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    vec->size = n;
    return DSC_ERROR_OK;
}

dsc_error vector_push_back(dsc_vector *vec, void const *element) {
    if (!vec || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        dsc_error err = vector_reserve(vec, new_capacity);
        if (err != DSC_ERROR_OK) {
            return err;
        }
    }

    void *dest = (char *)vec->data + (vec->size * vec->element_size);
    memcpy(dest, element, vec->element_size);
    ++(vec->size);

    return DSC_ERROR_OK;
}

dsc_error vector_pop_back(dsc_vector *vec) {
    if (!vec) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vec->size == 0) {
        return DSC_ERROR_EMPTY;
    }

    vec->size--;
    return DSC_ERROR_OK;
}

void *vector_at(dsc_vector *vec, size_t index) {
    if (!vec || index >= vec->size) {
        return NULL;
    }

    return (char *)vec->data + (index * vec->element_size);
}

void *vector_front(dsc_vector *vec) { return vector_at(vec, 0); }

void *vector_back(dsc_vector *vec) {
    if (!vec || vec->size == 0) {
        return NULL;
    }
    return vector_at(vec, vec->size - 1);
}

dsc_error vector_insert(dsc_vector *vec, size_t index,
                          void const *element) {
    if (!vec || !element) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (index > vec->size) {
        return DSC_ERROR_NOT_FOUND;
    }

    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        dsc_error err = vector_reserve(vec, new_capacity);
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
    void *dest = (char *)vec->data + (index * vec->element_size);
    memcpy(dest, element, vec->element_size);
    ++(vec->size);

    return DSC_ERROR_OK;
}

dsc_error vector_erase(dsc_vector *vec, size_t index) {
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

void vector_clear(dsc_vector *vec) {
    if (vec) {
        vec->size = 0;
    }
}

dsc_error vector_shrink_to_fit(dsc_vector *vec) {
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
