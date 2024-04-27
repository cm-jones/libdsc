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
#include <string.h>

#include "../include/dsc_vector.h"

/* Represents a vector (dynamic array) */

struct DSCVector {
    void **data;     /* Array of elements (void pointers) stored in the vector */

    size_t size;     /* The number of elements currently in the vector */
    size_t capacity; /* The current capacity of the vector */

    DSCType type;    /* The type of the elements in the vector */
    DSCError error;  /* The most recent error code */
};

/* Helper function for resizing a DSCVector when its size is equal to or greater than its capacity */

static bool dsc_vector_resize(DSCVector vector, size_t new_capacity) {
    void **new_data = realloc(vector->data, new_capacity * dsc_sizeof(vector->type));
    if (!new_data) {
        return false;
    }

    vector->data = new_data;
    vector->capacity = new_capacity;

    return true;
}

/* Helper function to shrink a DSCVector when its size is too small compared to its capacity. Unused thus far. */

bool dsc_vector_shrink_to_fit(DSCVector vector) {
    if (!vector) {
        return false;
    }

    if (vector->size == vector->capacity) {
        vector->error = DSC_ERROR_OK;
        return true;
    }

    if (!dsc_vector_resize(vector, vector->size)) {
        vector->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    vector->error = DSC_ERROR_OK;

    return true;
}

/* Constructor and destructor for a DSCVector */

DSCVector dsc_vector_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCVector new_vector = malloc(sizeof *new_vector);
    if (!new_vector) {
        return NULL;
    }

    new_vector->size = 0;
    new_vector->capacity = DSC_VECTOR_INITIAL_CAPACITY;
    new_vector->type = type;

    new_vector->data = malloc(new_vector->capacity * dsc_sizeof(type));
    if (!new_vector->data) {
        free(new_vector);
        return NULL;
    }

    return new_vector;
}

bool dsc_vector_deinit(DSCVector vector) {
    if (!vector) {
        return false;
    }

    free(vector->data);
    free(vector);

    return true;
}

/* Capacity */

bool dsc_vector_is_empty(const DSCVector vector) {
    if (!vector) {
        return false;
    }

    vector->error = DSC_ERROR_OK;

    return vector->size == 0;
}

int dsc_vector_size(const DSCVector vector) {
    if (!vector) {
        return -1;
    }

    vector->error = DSC_ERROR_OK;

    return vector->size;
}

int dsc_vector_capacity(const DSCVector vector) {
    if (!vector) {
        return -1;
    }

    vector->error = DSC_ERROR_OK;

    return vector->capacity;
}

void *dsc_vector_at(const DSCVector vector, size_t index) {
    if (!vector) {
        return NULL;
    }

    if (index >= vector->size) {
        vector->error = DSC_ERROR_OUT_OF_RANGE;
        return NULL;
    }

    vector->error = DSC_ERROR_OK;

    return vector->data[index];
}

void *dsc_vector_back(const DSCVector vector) {
    if (!vector) {
        return NULL;
    }

    if (dsc_vector_is_empty(vector)) {
        vector->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    vector->error = DSC_ERROR_OK;

    return vector->data[vector->size - 1];
}

/* Modifiers */

bool dsc_vector_push_back(DSCVector vector, void *data) {
    if (!vector) {
        return false;
    }

    // Check if the type of the new element is valid
    if (dsc_typeof(data) != vector->type) {
        vector->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        if (!dsc_vector_resize(vector, new_capacity)) {
            vector->error = DSC_ERROR_OUT_OF_MEMORY;
            return false;
        }
    }

    vector->data[vector->size] = data;
    vector->size++;

    vector->error = DSC_ERROR_OK;

    return true;
}

void *dsc_vector_pop_back(DSCVector vector) {
    if (!vector) {
        return NULL;
    }

    if (dsc_vector_is_empty(vector)) {
        vector->error = DSC_ERROR_EMPTY_CONTAINER;
        return NULL;
    }

    vector->size--;
    vector->error = DSC_ERROR_OK;

    return vector->data[vector->size];
}

bool dsc_vector_insert(DSCVector vector, void *data, size_t index) {
    if (!vector) {
        return false;
    }

    // Check if the type of the new element is the same as the type of the vector
    if (dsc_typeof(data) != vector->type) {
        vector->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    // Check if the index is out of range
    if (index > vector->size) {
        vector->error = DSC_ERROR_OUT_OF_RANGE;
        return false;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        if (!dsc_vector_resize(vector, new_capacity)) {
            vector->error = DSC_ERROR_OUT_OF_MEMORY;
            return false;
        }
    }

    // Shift elements to the right to make room for the new element
    for (size_t i = vector->size; i > index; --i) {
        vector->data[i] = vector->data[i - 1];
    }

    vector->data[index] = data;
    vector->size++;
    vector->error = DSC_ERROR_OK;

    return true;
}

bool dsc_vector_erase(DSCVector vector, size_t index) {
    if (!vector) {
        return false;
    }

    if (index >= vector->size) {
        vector->error = DSC_ERROR_OUT_OF_RANGE;
        return false;
    }

    // Shift elements to the left to fill the gap
    for (size_t i = index; i < vector->size - 1; ++i) {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;
    vector->error = DSC_ERROR_OK;

    return true;
}

bool dsc_vector_reserve(DSCVector vector, size_t new_capacity) {
    if (!vector) {
        return false;
    }

    if (new_capacity <= vector->capacity) {
        vector->error = DSC_ERROR_INVALID_ARGUMENT;
        return false;
    }

    if (!dsc_vector_resize(vector, new_capacity)) {
        vector->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    vector->error = DSC_ERROR_OK;

    return true;
}

bool dsc_vector_clear(DSCVector vector) {
    if (!vector) {
        return false;
    }

    vector->size = 0;
    vector->error = DSC_ERROR_OK;

    return true;
}

/* Error handling */

DSCError dsc_vector_error(const DSCVector vector) {
    return vector->error;
}
