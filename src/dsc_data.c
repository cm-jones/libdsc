// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>

#include "../include/dsc_data.h"

DSCError dsc_data_malloc(DSCData *data, DSCType type, size_t capacity) {
    if (data == NULL || capacity == 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    switch (type) {
        case DSC_TYPE_BOOL:
            data->b_ptr = malloc(capacity * sizeof(bool));
            if (data->b_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        case DSC_TYPE_CHAR:
            data->c_ptr = malloc(capacity * sizeof(char));
            if (data->c_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        case DSC_TYPE_INT:
            data->i_ptr = malloc(capacity * sizeof(int));
            if (data->i_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        case DSC_TYPE_FLOAT:
            data->f_ptr = malloc(capacity * sizeof(float));
            if (data->f_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        case DSC_TYPE_DOUBLE:
            data->d_ptr = malloc(capacity * sizeof(double));
            if (data->d_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        case DSC_TYPE_STRING:
            data->s_ptr = malloc(capacity * sizeof(char *));
            if (data->s_ptr == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            break;

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_data_realloc(DSCData *data, DSCType type, size_t capacity) {
    if (data == NULL || capacity == 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    void *new_data = NULL;

    switch (type) {
        case DSC_TYPE_BOOL:
            new_data = realloc(data->b_ptr, capacity * sizeof(bool));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->b_ptr = new_data;
            break;

        case DSC_TYPE_CHAR:
            new_data = realloc(data->c_ptr, capacity * sizeof(char));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->c_ptr = new_data;
            break;

        case DSC_TYPE_INT:
            new_data = realloc(data->i_ptr, capacity * sizeof(int));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->i_ptr = new_data;
            break;

        case DSC_TYPE_FLOAT:
            new_data = realloc(data->f_ptr, capacity * sizeof(float));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->f_ptr = new_data;
            break;

        case DSC_TYPE_DOUBLE:
            new_data = realloc(data->d_ptr, capacity * sizeof(double));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->d_ptr = new_data;
            break;

        case DSC_TYPE_STRING:
            new_data = realloc(data->s_ptr, capacity * sizeof(char *));
            if (new_data == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            data->s_ptr = new_data;
            break;

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_data_free(DSCData *data, DSCType type, size_t size) {
    if (data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    switch (type) {
        case DSC_TYPE_BOOL:
            free(data->b_ptr);
            data->b_ptr = NULL;
            break;

        case DSC_TYPE_CHAR:
            free(data->c_ptr);
            data->c_ptr = NULL;
            break;

        case DSC_TYPE_INT:
            free(data->i_ptr);
            data->i_ptr = NULL;
            break;

        case DSC_TYPE_FLOAT:
            free(data->f_ptr);
            data->f_ptr = NULL;
            break;

        case DSC_TYPE_DOUBLE:
            free(data->d_ptr);
            data->d_ptr = NULL;
            break;

        case DSC_TYPE_STRING:
            // Free each string before freeing the array of pointers
            for (size_t i = 0; i < size; i++) {
                if (data->s_ptr[i] != NULL) {
                    free(data->s_ptr[i]);
                    data->s_ptr[i] = NULL;
                }
            }
            free(data->s_ptr);
            data->s_ptr = NULL;
            break;

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_data_copy(DSCData *dest, void *src, DSCType type) {
    if (dest == NULL || src == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    switch (type) {
        case DSC_TYPE_BOOL:
            dest->b = *(bool *)src;
            break;

        case DSC_TYPE_CHAR:
            dest->c = *(char *)src;
            break;

        case DSC_TYPE_INT:
            dest->i = *(int *)src;
            break;

        case DSC_TYPE_FLOAT:
            dest->f = *(float *)src;
            break;

        case DSC_TYPE_DOUBLE:
            dest->d = *(double *)src;
            break;

        case DSC_TYPE_STRING: {
            char *str = *(char **)src;
            if (str == NULL) {
                dest->s = NULL;
                return DSC_ERROR_OK;
            }
            
            size_t len = strlen(str) + 1;
            dest->s = malloc(len);
            if (dest->s == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
            
            memcpy(dest->s, str, len);
            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

int dsc_compare(DSCData data1, void *data2, DSCType type) {
    switch (type) {
        case DSC_TYPE_BOOL:
            return data1.b - *(bool *) data2;

        case DSC_TYPE_CHAR:
            return data1.c - *(char *) data2;

        case DSC_TYPE_INT:
            return data1.i - *(int *) data2;

        case DSC_TYPE_FLOAT:
            return data1.f - *(float *) data2;

        case DSC_TYPE_DOUBLE:
            return data1.d - *(double *) data2;

        case DSC_TYPE_STRING:
            return strcmp(data1.s, *(const char **) data2);

        default:
            return INT32_MIN;
    }
}
