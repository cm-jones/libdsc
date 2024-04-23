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
#include "../include/dsc_error.h"

struct DSCVector {
    int *values;           // Array of values stored in the vector
    int size;     // The number of elements in the vector
    int capacity; // The current capacity of the vector.
};

static bool DSCVector_resize(DSCVector vector, int new_capacity) {
    int *new_values = realloc(vector->values, new_capacity * sizeof(int));
    if (new_values == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    vector->values = new_values;
    vector->capacity = new_capacity;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

DSCVector DSCVector_create(void) {
    DSCVector new_vector = malloc(sizeof *new_vector);
    if (new_vector == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_vector->size = 0;
    new_vector->capacity = DSC_VECTOR_INITIAL_CAPACITY;

    new_vector->values = malloc(new_vector->capacity * sizeof(int));
    if (new_vector->values == NULL) {
        free(new_vector);
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return new_vector;
}

bool DSCVector_free(DSCVector vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    free(vector->values);
    free(vector);

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool DSCVector_push_back(DSCVector vector, int value) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        int new_capacity = vector->capacity * 1.5;
        if (!DSCVector_resize(vector, new_capacity)) {
            dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
            return false;
        }
    }

    vector->values[vector->size] = value;
    vector->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool DSCVector_pop_back(DSCVector vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (DSCVector_is_empty(vector)) {
        dsc_set_error(DSC_ERROR_EMPTY_CONTAINER);
        return false;
    }

    vector->size--;

    dsc_set_error(DSC_ERROR_NONE);
    return vector->values[vector->size];
}

bool DSCVector_insert(DSCVector vector, int value, int position) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (position < 0 || position > vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return false;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        int new_capacity = vector->capacity * 1.5;
        if (!DSCVector_resize(vector, new_capacity)) {
            dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
            return false;
        }
    }

    // Shift elements to the right to make room for the new element
    for (int i = vector->size; i > position; --i) {
        vector->values[i] = vector->values[i - 1];
    }

    vector->values[position] = value;
    vector->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool DSCVector_erase(DSCVector vector, int position) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (position < 0 || position >= vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return false;
    }

    // Shift elements to the left to fill the gap
    for (int i = position; i < vector->size - 1; ++i) {
        vector->values[i] = vector->values[i + 1];
    }

    vector->size--;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

int DSCVector_at(const DSCVector vector, int index) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    if (index < 0 || index >= vector->size) {
        dsc_set_error(DSC_ERROR_OUT_OF_RANGE);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->values[index];
}

bool DSCVector_is_empty(const DSCVector vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->size == 0;
}

int DSCVector_size(const DSCVector vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->size;
}

int DSCVector_capacity(const DSCVector vector) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return vector->capacity;
}

bool DSCVector_reserve(DSCVector vector, int new_capacity) {
    if (vector == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (new_capacity <= vector->capacity) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (!DSCVector_resize(vector, new_capacity)) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}
