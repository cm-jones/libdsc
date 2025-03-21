// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>

#include "../include/dsc_vector.h"
#include "../include/dsc_utils.h"

struct DSCVector {
    DSCData    data; // The data stored in the vector
    size_t     size; // The number of elements currently in the vector
    size_t capacity; // The current capacity of the vector
    DSCType    type; // The type of the elements in the vector
};


DSCError dsc_vector_resize(DSCVector *vector, size_t new_capacity) {
    switch (vector->type) {
        case DSC_TYPE_CHAR: {
            char *new_data = realloc(vector->data.c_ptr, new_capacity * sizeof(char));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            vector->data.c_ptr = new_data;
            break;
        }

        case DSC_TYPE_INT: {
            int *new_data = realloc(vector->data.i_ptr, new_capacity * sizeof(int));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            vector->data.i_ptr = new_data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            float *new_data = realloc(vector->data.f_ptr, new_capacity * sizeof(float));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            vector->data.f_ptr = new_data;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            double *new_data = realloc(vector->data.d_ptr, new_capacity * sizeof(double));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            vector->data.d_ptr = new_data;
            break;
        }

        case DSC_TYPE_STRING: {
            char **new_data = realloc(vector->data.s_ptr, new_capacity * sizeof(char *));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            vector->data.s_ptr = new_data;
            break;
        }

        case DSC_TYPE_BOOL: {
            bool *new_data = realloc(vector->data.b_ptr, new_capacity * sizeof(bool));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            vector->data.b_ptr = new_data;
            break;
        }

        default: {
            // Unknown type
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    vector->capacity = new_capacity;
    return DSC_ERROR_OK;
}

DSCError dsc_vector_init(DSCVector **vector_ptr, DSCType type) {
    if (vector_ptr == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    if (!dsc_type_is_valid(type)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    DSCVector *new_vector = malloc(sizeof(DSCVector));
    if (new_vector == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_vector->size = 0;
    new_vector->capacity = DSC_VECTOR_INITIAL_CAPACITY;
    new_vector->type = type;

    switch (type) {
        case DSC_TYPE_CHAR: {
            new_vector->data.c_ptr = malloc(new_vector->capacity * sizeof(char));
            if (new_vector->data.c_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;
        }

        case DSC_TYPE_INT: {
            new_vector->data.i_ptr = malloc(new_vector->capacity * sizeof(int));
            if (new_vector->data.i_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            break;
        }

        case DSC_TYPE_FLOAT: {
            new_vector->data.f_ptr = malloc(new_vector->capacity * sizeof(float));
            if (new_vector->data.f_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            break;
        }

        case DSC_TYPE_DOUBLE: {
            new_vector->data.d_ptr = malloc(new_vector->capacity * sizeof(double));
            if (new_vector->data.d_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            break;
        }

        case DSC_TYPE_STRING: {
            new_vector->data.s_ptr = malloc(new_vector->capacity * sizeof(char *));
            if (new_vector->data.s_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            break;
        }

        case DSC_TYPE_BOOL: {
            new_vector->data.b_ptr = malloc(new_vector->capacity * sizeof(bool));
            if (new_vector->data.b_ptr == NULL) {
                free(new_vector);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            break;
        }

        default: {
            free(new_vector);
            return DSC_ERROR_INVALID_TYPE;
        }
    }
    
    *vector_ptr = new_vector;
    return DSC_ERROR_OK;
}


DSCError dsc_vector_deinit(DSCVector *vector) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    switch (vector->type) {
        case DSC_TYPE_CHAR: {
            free(vector->data.c_ptr);
            break;
        }

        case DSC_TYPE_INT: {
            free(vector->data.i_ptr);
            break;
        }

        case DSC_TYPE_FLOAT: {
            free(vector->data.f_ptr);
            break;
        }

        case DSC_TYPE_DOUBLE: {
            free(vector->data.d_ptr);
            break;
        }

        case DSC_TYPE_STRING: {
            for (size_t i = 0; i < vector->size; ++i) {
                free(vector->data.s_ptr[i]);
            }

            free(vector->data.s_ptr);
            break;
        }

        case DSC_TYPE_BOOL: {
            free(vector->data.b_ptr);
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    free(vector);

    return DSC_ERROR_OK;
}

DSCError dsc_vector_size(const DSCVector *vector, size_t *result) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = vector->size;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_capacity(const DSCVector *vector, size_t *result) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = vector->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_empty(const DSCVector *vector, bool *result) {
    if (vector == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = vector->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_front(const DSCVector *vector, void *result) {
    if (vector == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    // Front is just the element at index 0
    return dsc_vector_at(vector, 0, result);
}

DSCError dsc_vector_at(const DSCVector *vector, size_t index, void *result) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (index >= vector->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    switch (vector->type) {
        case DSC_TYPE_CHAR: {
            *(char *) result = vector->data.c_ptr[index];
            break;
        }

        case DSC_TYPE_INT: {
            *(int *) result = vector->data.i_ptr[index];
            break;
        }

        case DSC_TYPE_FLOAT: {
            *(float *) result = vector->data.f_ptr[index];
            break;
        }

        case DSC_TYPE_DOUBLE: {
            *(double *) result = vector->data.d_ptr[index];
            break;
        }

        case DSC_TYPE_STRING: {
            char *str = vector->data.s_ptr[index];
            size_t size = strlen(str) + 1;

            char **result_ptr = (char **)result;
            *result_ptr = malloc(size);
            if (*result_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(*result_ptr, str, size - 1);
            (*result_ptr)[size - 1] = '\0';
            break;
        }
    }

    return DSC_ERROR_OK;
}

DSCError dsc_vector_back(const DSCVector *vector, void *data) {
    if (vector == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (vector->type) {
        case DSC_TYPE_BOOL:
            *(bool *) data = vector->data.b_ptr[vector->size - 1];
            break;
        case DSC_TYPE_CHAR:
            *(char *) data = vector->data.c_ptr[vector->size - 1];
            break;
        case DSC_TYPE_INT:
            *(int *) data = vector->data.i_ptr[vector->size - 1];
            break;
        case DSC_TYPE_FLOAT:
            *(float *) data = vector->data.f_ptr[vector->size - 1];
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) data = vector->data.d_ptr[vector->size - 1];
            break;
        case DSC_TYPE_STRING: {
            char *str = vector->data.s_ptr[vector->size - 1];
            size_t string_size = strlen(str);

            // Allocate an extra byte of memory for the null terminator
            char **result = (char **)data;
            *result = malloc(string_size + 1);
            if (*result == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(*result, str, string_size);
            (*result)[string_size] = '\0';
        }
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_vector_push_back(DSCVector *vector, void *data) {
    if (vector == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        DSCError resize_result = dsc_vector_resize(vector, new_capacity);
        if (resize_result != DSC_ERROR_OK) {
            return resize_result;
        }
    }

    switch (vector->type) {
        case DSC_TYPE_CHAR: {
            vector->data.c_ptr[vector->size] = *(char *) data;
            break;
        }

        case DSC_TYPE_INT: {
            vector->data.i_ptr[vector->size] = *(int *) data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            vector->data.f_ptr[vector->size] = *(float *) data;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            vector->data.d_ptr[vector->size] = *(double *) data;
            break;
        }

        case DSC_TYPE_STRING: {
            size_t data_size = strlen((char *) data);

            vector->data.s_ptr[vector->size] = malloc(data_size + 1);
            if (vector->data.s_ptr[vector->size] == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(vector->data.s_ptr[vector->size], (char *) data, data_size);
            memset(vector->data.s_ptr[vector->size] + data_size, '\0', 1);
            break;
        }

        case DSC_TYPE_BOOL: {
            vector->data.b_ptr[vector->size] = *(bool *) data;
            break;
        }

        default: {
            // Unknown type
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    vector->size++;
    return DSC_ERROR_OK;
}

DSCError dsc_vector_pop_back(DSCVector *vector, void *data) {
    if (vector == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (vector->type) {
        case DSC_TYPE_BOOL:
            *(bool *) data = vector->data.b_ptr[vector->size - 1];
            break;
        case DSC_TYPE_CHAR:
            *(char *) data = vector->data.c_ptr[vector->size - 1];
            break;
        case DSC_TYPE_INT:
            *(int *) data = vector->data.i_ptr[vector->size - 1];
            break;
        case DSC_TYPE_FLOAT:
            *(float *) data = vector->data.f_ptr[vector->size - 1];
            break;
        case DSC_TYPE_DOUBLE:
            *(double *) data = vector->data.d_ptr[vector->size - 1];
            break;
        case DSC_TYPE_STRING:
            *(char **) data = vector->data.s_ptr[vector->size - 1];
            vector->data.s_ptr[vector->size - 1] = NULL;
            break;
        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    vector->size--;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_insert(DSCVector *vector, void *data, size_t index) {
    if (vector == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Check if the index is out of range
    if (index > vector->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    // Resize the vector if the size exceeds the capacity
    if (vector->size >= vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        DSCError resize_result = dsc_vector_resize(vector, new_capacity);
        if (resize_result != DSC_ERROR_OK) {
            return resize_result;
        }
    }

    // Shift elements to the right to make room for the new element
    for (size_t i = vector->size; i > index; --i) {
        switch (vector->type) {
            case DSC_TYPE_BOOL:
                vector->data.b_ptr[i] = vector->data.b_ptr[i - 1];
                break;
            case DSC_TYPE_CHAR:
                vector->data.c_ptr[i] = vector->data.c_ptr[i - 1];
                break;
            case DSC_TYPE_INT:
                vector->data.i_ptr[i] = vector->data.i_ptr[i - 1];
                break;
            case DSC_TYPE_FLOAT:
                vector->data.f_ptr[i] = vector->data.f_ptr[i - 1];
                break;
            case DSC_TYPE_DOUBLE:
                vector->data.d_ptr[i] = vector->data.d_ptr[i - 1];
                break;
            case DSC_TYPE_STRING:
                vector->data.s_ptr[i] = vector->data.s_ptr[i - 1];
                break;
            default:
                return DSC_ERROR_INVALID_TYPE;
        }
    }

    switch (vector->type) {
        case DSC_TYPE_CHAR: {
            vector->data.c_ptr[index] = *(char *) data;
            break;
        }

        case DSC_TYPE_INT: {
            vector->data.i_ptr[index] = *(int *) data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            vector->data.f_ptr[index] = *(float *) data;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            vector->data.d_ptr[index] = *(double *) data;
            break;
        }

        case DSC_TYPE_STRING: {
            vector->data.s_ptr[index] = strdup(*(char **) data);
            break;
        }

        case DSC_TYPE_BOOL: {
            vector->data.b_ptr[index] = *(bool *) data;
            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    vector->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_erase(DSCVector *vector, size_t index) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (index >= vector->size) {
        return DSC_ERROR_OUT_OF_RANGE;
    }

    if (vector->type == DSC_TYPE_STRING) {
        free(vector->data.s_ptr[index]);
    }

    // Shift elements to the left to fill the gap
    for (size_t i = index; i < vector->size - 1; ++i) {
        switch (vector->type) {
            case DSC_TYPE_CHAR: {
                vector->data.c_ptr[i] = vector->data.c_ptr[i + 1];
                break;
            }

            case DSC_TYPE_INT: {
                vector->data.i_ptr[i] = vector->data.i_ptr[i + 1];
                break;
            }

            case DSC_TYPE_FLOAT: {
                vector->data.f_ptr[i] = vector->data.f_ptr[i + 1];
                break;
            }

            case DSC_TYPE_DOUBLE: {
                vector->data.d_ptr[i] = vector->data.d_ptr[i + 1];
                break;
            }

            case DSC_TYPE_STRING: {
                vector->data.s_ptr[i] = vector->data.s_ptr[i + 1];
                break;
            }

            case DSC_TYPE_BOOL: {
                vector->data.b_ptr[i] = vector->data.b_ptr[i + 1];
                break;
            }

            default: {
                return DSC_ERROR_INVALID_TYPE;
            }
        }
    }

    vector->size--;

    return DSC_ERROR_OK;
}

DSCError dsc_vector_clear(DSCVector *vector) {
    if (vector == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (vector->type == DSC_TYPE_STRING) {
        for (size_t i = 0; i < vector->size; ++i) {
            free(vector->data.s_ptr[i]);
        }
    }

    vector->size = 0;

    return DSC_ERROR_OK;
}
