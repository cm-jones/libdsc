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

#include "../include/dsc_stack.h"

struct DSCStack {
    union {
        char *c;     // An array of characters
        int *i;      // An array of integers
        float *f;    // An array of floats
        double *d;   // An array of doubles
        char **s;    // An array of strings
        bool *b;     // An array of booleans
    } data;          // The data stored in the stack

    size_t size;     // The number of elements currently in the stack
    size_t capacity; // The current capacity of the stack
    DSCType type;    // The type of the elements in the stack
};

static bool dsc_stack_resize(DSCStack stack, size_t new_capacity) {
    switch (stack->type) {
        case DSC_TYPE_CHAR: {
            char **new_data = realloc(stack->data.c, new_capacity * sizeof(char));
            if (new_data == NULL) {
                return false;
            }
            stack->data.c = new_data;
            break;
        }

        case DSC_TYPE_INT: {
            int *new_data = realloc(stack->data.i, new_capacity * sizeof(int));
            if (new_data == NULL) {
                return false;
            }
            stack->data.i = new_data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            float *new_data = realloc(stack->data.f, new_capacity * sizeof(float));
            if (new_data == NULL) {
                return false;
            }
            stack->data.f = new_data;
            break;
        }
    
        case DSC_TYPE_DOUBLE: {
            double *new_data = realloc(stack->data.d, new_capacity * sizeof(double));
            if (new_data == NULL) {
                return false;
            }
            stack->data.d = new_data;
            break;
        }
    
        case DSC_TYPE_STRING: {
            char **new_data = realloc(stack->data.s, new_capacity * sizeof(char *));
            if (new_data == NULL) {
            return false;
            }
            stack->data.s = new_data;
            break;
        }
    
        case DSC_TYPE_BOOL: {
            bool *new_data = realloc(stack->data.b, new_capacity * sizeof(bool));
            if (new_data == NULL) {
                return false;
            }
            stack->data.b = new_data;
            break;
        }

        default:
            return false;
    }

    stack->capacity = new_capacity;

    return true;
}

DSCStack dsc_stack_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCStack new_stack = malloc(sizeof(DSCStack));
    if (new_stack == NULL) {
        return NULL;
    }

    new_stack->size = 0;
    new_stack->capacity = DSC_STACK_INITIAL_CAPACITY;
    new_stack->type = type;

    switch (type) {
        case DSC_TYPE_CHAR: {
            new_stack->data.c = malloc(new_stack->capacity * sizeof(char));
            if (new_stack->data.c == NULL) {
                free(new_stack);
                return NULL;
            }

            return new_stack;
        }

        case DSC_TYPE_INT: {
            new_stack->data.i = malloc(new_stack->capacity * sizeof(int));
            if (new_stack->data.i == NULL) {
                free(new_stack);
                return NULL;
            }

            return new_stack;
        }

        case DSC_TYPE_FLOAT: {
            new_stack->data.f = malloc(new_stack->capacity * sizeof(float));
            if (new_stack->data.f == NULL) {
                free(new_stack);
                return NULL;
            }
            
            return new_stack;
        }

        case DSC_TYPE_DOUBLE: {
            new_stack->data.d = malloc(new_stack->capacity * sizeof(double));
            if (new_stack->data.d == NULL) {
                free(new_stack);
                return NULL;
            }
            
            return new_stack;
        }

        case DSC_TYPE_STRING: {
            new_stack->data.s = malloc(new_stack->capacity * sizeof(char *));
            if (new_stack->data.s == NULL) {
                free(new_stack);
                return NULL;
            }
            
            return new_stack;
        }

        case DSC_TYPE_BOOL: {
            new_stack->data.b = malloc(new_stack->capacity * sizeof(bool));
            if (new_stack->data.b == NULL) {
                free(new_stack);
                return NULL;
            }
            
            return new_stack;
        }
    }

    free(new_stack);

    return NULL;
}

DSCError dsc_stack_deinit(DSCStack stack) {
    if (stack == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    switch (stack->type) {
        case DSC_TYPE_CHAR: {
            free(stack->data.c);
            break;
        }
        
        case DSC_TYPE_INT: {
            free(stack->data.i);
            break;
        }

        case DSC_TYPE_FLOAT: {
            free(stack->data.f);
            break;
        }

        case DSC_TYPE_DOUBLE: {
            free(stack->data.d);
            break;
        }

        case DSC_TYPE_STRING: {
            for (size_t i = 0; i < stack->size; i++) {
                free(stack->data.s[i]);
            }

            free(stack->data.s);
            break;
        }

        case DSC_TYPE_BOOL: {
            free(stack->data.b);
            break;
        }
    }

    free(stack);

    return DSC_ERROR_OK;
}

DSCError dsc_stack_size(const DSCStack stack, size_t *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->size;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_capacity(const DSCStack stack, size_t *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_is_empty(const DSCStack stack, bool *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = stack->size == 0;

    return DSC_ERROR_OK;
}

#include <string.h>

DSCError dsc_stack_top(const DSCStack stack, void *result) {
    if (stack == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    switch (stack->type) {
        case DSC_TYPE_CHAR: {
            *(char *) result = stack->data.c[stack->size - 1];
            break;
        }

        case DSC_TYPE_INT: {
            *(int *) result = stack->data.i[stack->size - 1];
            break;
        }

        case DSC_TYPE_FLOAT: {
            *(float *) result = stack->data.f[stack->size - 1];
            break;
        }

        case DSC_TYPE_DOUBLE: {
            *(double *) result = stack->data.d[stack->size - 1];
            break;
        }

        case DSC_TYPE_STRING: {
            const char *s = stack->data.s[stack->size - 1];
            size_t string_size = strlen(s);
            size_t result_size = strlen((char *) result);

            if (string_size >= result_size) {
                return DSC_ERROR_OUT_OF_MEMORY;
            }
        
            strncpy((char *) result, s, string_size + 1);
            break;
        }

        case DSC_TYPE_BOOL: {
            *(bool *) result = stack->data.b[stack->size - 1];
            break;
        }

        default:
            return DSC_ERROR_TYPE_MISMATCH;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_stack_push(DSCStack stack, void *data) {
    if (stack == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Resize the stack if its size is equal to or exceeds its capacity
    if (stack->size >= stack->capacity) {
        size_t new_capacity = stack->capacity * 1.5;
        if (!dsc_stack_resize(stack, new_capacity)) {
            return DSC_ERROR_OUT_OF_MEMORY;
        }
    }

    switch (stack->type) {
        case DSC_TYPE_CHAR: {
            stack->data.c[stack->size] = *(char *) data;
            break;
        }

        case DSC_TYPE_INT: {
            stack->data.i[stack->size] = *(int *) data;
            break;
        }

        case DSC_TYPE_FLOAT: {
            stack->data.f[stack->size] = *(float *) data;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            stack->data.d[stack->size] = *(double *) data;
            break;
        }

        case DSC_TYPE_STRING: {
            stack->data.s[stack->size] = strdup(*(char **) data);
            break;
        }

        case DSC_TYPE_BOOL: {
            stack->data.b[stack->size] = *(bool *) data;
            break;
        }

        default:
            return DSC_ERROR_TYPE_MISMATCH;
    }

    stack->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_stack_pop(DSCStack stack, void *data) {
    if (stack == NULL || data == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    if (stack->size == 0) {
        return DSC_ERROR_EMPTY_CONTAINER;
    }

    // Get the popped element so we can return it after freeing it
    switch (stack->type) {
        case DSC_TYPE_CHAR: {
            *(char *) data = stack->data.c[stack->size - 1];
            break;
        }

        case DSC_TYPE_INT: {
            *(int *) data = stack->data.i[stack->size - 1];
            break;
        }

        case DSC_TYPE_FLOAT: {
            *(float *) data = stack->data.f[stack->size - 1];
            break;
        }

        case DSC_TYPE_DOUBLE: {
            *(double *) data = stack->data.d[stack->size - 1];
            break;
        }

        case DSC_TYPE_STRING: {
            *(char **) data = stack->data.s[stack->size - 1];
            stack->data.s[stack->size - 1] = NULL;
            break;
        }

        case DSC_TYPE_BOOL: {
            *(bool *) data = stack->data.b[stack->size - 1];
            break;
        }

        default:
            return DSC_ERROR_TYPE_MISMATCH;
    }

    stack->size--;

    return DSC_ERROR_OK;
}
