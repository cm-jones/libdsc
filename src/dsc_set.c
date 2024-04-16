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
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_add(struct dsc_set_t *set, const int value)
{
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Check if the value already exists in the set
    if (dsc_set_contains(set, value)) {
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
    return DSC_ERROR_NONE;
}

bool dsc_set_contains(struct dsc_set_t *set, int value)
{
    return false;
}

int dsc_set_get_size(struct dsc_set_t *set)
{
    return 0;
}

bool dsc_set_is_empty(struct dsc_set_t *set)
{
    return false;
}

enum dsc_error_t dsc_set_clear(struct dsc_set_t *set)
{
    return DSC_ERROR_NONE;
}
