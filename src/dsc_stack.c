// SPDX-License-Identifier: GPL-3.0-or-later

#include "../include/dsc_stack.h"

#include <stdlib.h>
#include <string.h>

static DSCError dsc_stack_resize(DSCStack *stack, size_t new_capacity) {
    if (stack == NULL || new_capacity <= 0) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    DSCError errno = dsc_data_realloc(&stack->data, stack->type, new_capacity);
    if (errno != DSC_ERROR_OK) {
        return errno;
    }

    stack->capacity = new_capacity;

    return DSC_ERROR_OK;
}

DSCStack *dsc_stack_init(DSCType type) {
    if (dsc_type_invalid(type)) {
        return NULL;
    }

    DSCStack *new_stack = malloc(sizeof(DSCStack));
    if (new_stack == NULL) {
        return NULL;
    }

    new_stack->size = 0;
    new_stack->capacity = DSC_STACK_INITIAL_CAPACITY;
    new_stack->type = type;

    DSCError errno = dsc_data_malloc(&new_stack->data, type, new_stack->capacity);
    if (errno != DSC_ERROR_OK) {
        free(new_stack);
        return NULL;
    }

    return new_stack;
}

DSCError dsc_stack_deinit(DSCStack *stack) {
    if (stack == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    dsc_data_free(&stack->data, stack->type, stack->size);

    free(stack);
    stack = NULL;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_size(const DSCStack *stack, size_t *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->size;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_capacity(const DSCStack *stack, size_t *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_empty(const DSCStack *stack, bool *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_top(const DSCStack *stack, void *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (stack->type) {
        case DSC_TYPE_BOOL:
            *(bool *) result = stack->data.b_ptr[stack->size - 1];
            break;

        case DSC_TYPE_CHAR:
            *(char *) result = stack->data.c_ptr[stack->size - 1];
            break;

        case DSC_TYPE_INT:
            *(int *) result = stack->data.i_ptr[stack->size - 1];
            break;

        case DSC_TYPE_FLOAT:
            *(float *) result = stack->data.f_ptr[stack->size - 1];
            break;

        case DSC_TYPE_DOUBLE:
            *(double *) result = stack->data.d_ptr[stack->size - 1];
            break;

        case DSC_TYPE_STRING: {
            const char *str = stack->data.s_ptr[stack->size - 1];
            size_t str_size = strlen(str) + 1;

            char *temp = malloc(str_size);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, str, str_size);
            temp[str_size - 1] = '\0';

            *(char **) result = temp;
            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_stack_push(DSCStack *stack, void *value) {
    if (stack == NULL || value == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size >= stack->capacity) {
        DSCError errno = dsc_stack_resize(stack, stack->capacity * 2);
        if (errno != DSC_ERROR_OK) {
            return errno;
        }
    }

    switch (stack->type) {
        case DSC_TYPE_BOOL:
            stack->data.b_ptr[stack->size] = *(bool *) value;
            break;

        case DSC_TYPE_CHAR:
            stack->data.c_ptr[stack->size] = *(char *) value;
            break;

        case DSC_TYPE_INT:
            stack->data.i_ptr[stack->size] = *(int *) value;
            break;

        case DSC_TYPE_FLOAT:
            stack->data.f_ptr[stack->size] = *(float *) value;
            break;

        case DSC_TYPE_DOUBLE:
            stack->data.d_ptr[stack->size] = *(double *) value;
            break;

        case DSC_TYPE_STRING: {
            const char *str = *(char **) value;
            size_t str_size = strlen(str) + 1;

            stack->data.s_ptr[stack->size] = malloc(str_size);
            if (stack->data.s_ptr[stack->size] == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(stack->data.s_ptr[stack->size], str, str_size);
            stack->data.s_ptr[stack->size][str_size - 1] = '\0';
            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    stack->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_pop(DSCStack *stack, void *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (stack->type) {
        case DSC_TYPE_BOOL:
            *(bool *) result = stack->data.b_ptr[stack->size - 1];
            break;

        case DSC_TYPE_CHAR:
            *(char *) result = stack->data.c_ptr[stack->size - 1];
            break;

        case DSC_TYPE_INT:
            *(int *) result = stack->data.i_ptr[stack->size - 1];
            break;

        case DSC_TYPE_FLOAT:
            *(float *) result = stack->data.f_ptr[stack->size - 1];
            break;

        case DSC_TYPE_DOUBLE:
            *(double *) result = stack->data.d_ptr[stack->size - 1];
            break;

        case DSC_TYPE_STRING: {
            const char *str = stack->data.s_ptr[stack->size - 1];
            size_t str_size = strlen(str) + 1;

            char *temp = malloc(str_size);
            if (temp == NULL) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(temp, str, str_size);
            temp[str_size - 1] = '\0';

            *(char **) result = temp;

            free(stack->data.s_ptr[stack->size - 1]);
            stack->data.s_ptr[stack->size - 1] = NULL;

            break;
        }

        default:
            return DSC_ERROR_INVALID_TYPE;
    }

    stack->size--;

    return DSC_ERROR_OK;
}
