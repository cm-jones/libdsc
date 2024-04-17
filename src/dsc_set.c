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
#include <stdbool.h>

#include "../include/dsc_set.h"
#include "../include/dsc_hash_utils.h"

struct dsc_set_t *dsc_set_create()
{
    struct dsc_set_t *new_set = calloc(1, sizeof *new_set);
    if (new_set == NULL) {
        return NULL;
    }

    new_set->capacity = DSC_SET_INITIAL_CAPACITY;
    new_set->size = 0;

    new_set->buckets = calloc(new_set->capacity, sizeof(struct dsc_set_entry_t *));
    if (new_set->buckets == NULL) {
        free(new_set);
        return NULL;
    }

    return new_set;
}

enum dsc_error_t dsc_set_destroy(struct dsc_set_t *set)
{
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Free all the entries in the set
    for (int i = 0; i < set->capacity; i++) {
        struct dsc_set_entry_t *entry = set->buckets[i];
        while (entry != NULL) {
            struct dsc_set_entry_t *next = entry->next;
            free(entry);
            entry = next;
        }
    }

    // Free the buckets array and the set itself
    free(set->buckets);
    free(set);

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_add(struct dsc_set_t *set, int value)
{
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Check if the value already exists in the set
    bool result;
    enum dsc_error_t error = dsc_set_contains(set, value, &result);
    if (error != DSC_ERROR_NONE) {
        return error;
    }
    if (result) {
        return DSC_ERROR_VALUE_ALREADY_EXISTS;
    }

    // Resize the set if the load factor exceeds the threshold
    if ((float) set->size / set->capacity >= DSC_SET_LOAD_FACTOR) {
        int new_capacity = set->capacity * 2;
        struct dsc_set_entry_t **new_buckets = calloc(new_capacity, sizeof(struct dsc_set_entry_t *));
        if (new_buckets == NULL) {
            return DSC_ERROR_OUT_OF_MEMORY;
        }

        // Rehash all the elements into the new buckets
        for (int i = 0; i < set->capacity; i++) {
            struct dsc_set_entry_t *entry = set->buckets[i];
            while (entry != NULL) {
                struct dsc_set_entry_t *next = entry->next;
                int index = dsc_hash(entry->key, new_capacity);
                entry->next = new_buckets[index];
                new_buckets[index] = entry;
                entry = next;
            }
        }

        free(set->buckets);
        set->buckets = new_buckets;
        set->capacity = new_capacity;
    }

    // Create a new entry
    struct dsc_set_entry_t *new_entry = malloc(sizeof *new_entry);
    if (new_entry == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_entry->key = value;
    new_entry->next = NULL;

    // Hash the value to determine the bucket index
    int index = dsc_hash(value, set->capacity);

    // Insert the new entry at the beginning of the bucket
    new_entry->next = set->buckets[index];
    set->buckets[index] = new_entry;

    set->size++;

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_remove(struct dsc_set_t *set, int value)
{
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    int index = dsc_hash(value, set->capacity);

    struct dsc_set_entry_t *prev = NULL;
    struct dsc_set_entry_t *entry = set->buckets[index];

    while (entry != NULL) {
        if (entry->key == value) {
            if (prev == NULL) {
                set->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            set->size--;
            return DSC_ERROR_NONE;
        }
        prev = entry;
        entry = entry->next;
    }

    return DSC_ERROR_VALUE_NOT_FOUND;
}

enum dsc_error_t dsc_set_contains(const struct dsc_set_t *set,
                                  int value,
                                  bool *result)
{
    if (set == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Hash the value to determine the bucket index
    int index = dsc_hash(value, set->capacity);

    // Search for the value in the bucket
    struct dsc_set_entry_t *entry = set->buckets[index];
    while (entry != NULL) {
        if (entry->key == value) {
            *result = true;
            return DSC_ERROR_NONE;
        }
        entry = entry->next;
    }

    *result = false;
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_get_size(const struct dsc_set_t *set,
                                  unsigned int *result)
{
    if (set == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = set->size;

    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_is_empty(const struct dsc_set_t *set, bool *result)
{
    if (set == NULL || result == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *result = (set->size == 0);
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_clear(struct dsc_set_t *set)
{
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Free all the entries in the set
    for (int i = 0; i < set->capacity; i++) {
        struct dsc_set_entry_t *entry = set->buckets[i];
        while (entry != NULL) {
            struct dsc_set_entry_t *next = entry->next;
            free(entry);
            entry = next;
        }
        set->buckets[i] = NULL;
    }

    set->size = 0;

    return DSC_ERROR_NONE;
}
