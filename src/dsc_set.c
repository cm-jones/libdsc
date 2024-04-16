/*
 * This file is part of the Data Structures for C (DSC) library.
 *
 * The Data Structures for C (DSC) library is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * The Data Structures for C (DSC) library is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * the Data Structures for C (DSC) library. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "../include/dsc_set.h"

struct dsc_set_t *dsc_set_create()
{
    struct dsc_set_t *new_set = malloc(sizeof *new_set);
    if (new_set == NULL) {
        return dsc_set_create_with_error(DSC_ERROR_OUT_OF_MEMORY);
    }

    new_set->buckets = NULL;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;
    new_set->size = 0;
    new_set->error = DSC_ERROR_NONE;

    return new_set;
}

struct dsc_set_t *dsc_set_create_with_error(enum dsc_error_t error)
{
    struct dsc_set_t *new_set = malloc(sizeof *new_set);
    if (new_set == NULL) {
        return NULL;
    }

    new_set->buckets = NULL;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;
    new_set->size = 0;
    new_set->error = error;

    return new_set;
}

struct dsc_set_t *dsc_set_destroy(struct dsc_set_t *set)
{
    if (set == NULL) {
        return dsc_set_create_with_error(DSC_ERROR_INVALID_ARGUMENT);
    }

    if (set->buckets == NULL) {
        free(set);
        return NULL;
    }

    for (int i = 0; i < set->size; i++) {
        struct dsc_set_entry_t *bucket = set->buckets[i];
        free(bucket->next);
        free(bucket);
    }

    free(set);
    return NULL;
}

struct dsc_set_t *dsc_set_add(struct dsc_set_t *set, int value)
{
    if (set == NULL) {
        return dsc_set_create_with_error(DSC_ERROR_INVALID_ARGUMENT);
    }

    set->error = DSC_ERROR_NONE;
    return set;
}

struct dsc_set_t *dsc_set_remove(struct dsc_set_t *set, int value)
{
    if (set == NULL) {
        return dsc_set_create_with_error(DSC_ERROR_INVALID_ARGUMENT);
    }

    set->error = DSC_ERROR_NONE;
    return set;
}

bool dsc_set_contains(struct dsc_set_t *set, int value)
{
    if (set == NULL) {
        return false;
    }

    return false;
}

int dsc_set_size(struct dsc_set_t *set)
{
    if (set == NULL) {
        return -1;
    }

    set->error = DSC_ERROR_NONE;
    return set->size;
}

bool dsc_set_is_empty(struct dsc_set_t *set)
{
    if (set != NULL) {
        return set->size == 0;
    }
}

struct dsc_set_t *dsc_set_clear(struct dsc_set_t *set)
{
    if (set == NULL) {
        return dsc_set_create_with_error(DSC_ERROR_INVALID_ARGUMENT);
    }

    set->size = 0;
    set->error = DSC_ERROR_NONE;
    return set;
}
