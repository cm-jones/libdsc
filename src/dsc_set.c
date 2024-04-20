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
#include "../include/dsc_utils.h"
#include "../include/dsc_error.h"

/* Represents an entry in the hash set. */
struct dsc_set_entry_t {
    int key;                          /* The key of the entry. */
    struct dsc_set_entry_t *next;     /* Pointer to the next entry in case of collisions. */
};

/* Represents a hash set. */
struct dsc_set_t {
    struct dsc_set_entry_t **buckets; /* Array of pointers to entries. */
    size_t size;                      /* The number of elements in the hash set. */
    size_t capacity;                  /* The current capacity of the hash set. */
};

static void dsc_set_rehash(dsc_set_t *set, size_t new_capacity) {
    dsc_set_entry_t **new_buckets = calloc(new_capacity, sizeof(dsc_set_entry_t *));
    if (new_buckets == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    /* Rehash all the elements into the new buckets. */
    for (size_t i = 0; i < set->capacity; ++i) {
        dsc_set_entry_t *entry = set->buckets[i];
        while (entry != NULL) {
            dsc_set_entry_t *next = entry->next;

            /* Rehash the value to determine the new index. */
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

dsc_set_t *dsc_set_create() {
    dsc_set_t *new_set = calloc(1, sizeof *new_set);
    if (new_set == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_set->size = 0;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;

    new_set->buckets = calloc(new_set->capacity, sizeof(dsc_set_entry_t *));
    if (new_set->buckets == NULL) {
        free(new_set);
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return new_set;
}

void dsc_set_free(dsc_set_t *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Free all the entries in the set */
    for (size_t i = 0; i < set->capacity; ++i) {
        dsc_set_entry_t *curr = set->buckets[i];
        while (curr != NULL) {
            dsc_set_entry_t *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    /* Free the buckets array and the set itself */
    free(set->buckets);
    free(set);
    dsc_set_error(DSC_ERROR_NONE);
}

bool dsc_set_insert(dsc_set_t *set, int value) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    if (dsc_set_contains(set, value)) {
        /* TODO: handle error */
        return false;
    }

    /* Resize the set if the load factor exceeds the threshold */
    if ((float) set->size / set->capacity >= DSC_SET_LOAD_FACTOR) {
        size_t new_capacity = set->capacity * 2;
        dsc_set_rehash(set, new_capacity);
    }

    /* Create a new entry */
    dsc_set_entry_t *new_entry = malloc(sizeof *new_entry);
    if (new_entry == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return false;
    }

    new_entry->key = value;
    new_entry->next = NULL;

    /* Hash the value to determine the bucket index */
    int index = dsc_hash(value, set->capacity);

    /* Insert the new entry at the beginning of the bucket */
    new_entry->next = set->buckets[index];
    set->buckets[index] = new_entry;

    set->size++;

    dsc_set_error(DSC_ERROR_NONE);
    return true;
}

bool dsc_set_erase(dsc_set_t *set, int value) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    int index = dsc_hash(value, set->capacity);

    dsc_set_entry_t *prev = NULL;
    dsc_set_entry_t *entry = set->buckets[index];

    while (entry != NULL) {
        if (entry->key == value) {
            if (prev == NULL) {
                set->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry);
            set->size--;
            dsc_set_error(DSC_ERROR_NONE);
            return true;
        }
        prev = entry;
        entry = entry->next;
    }

    dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
    return false;
}

bool dsc_set_contains(const dsc_set_t *set, int value) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    /* Hash the value to determine the bucket index */
    int index = dsc_hash(value, set->capacity);

    /* Search for the value in the bucket */
    dsc_set_entry_t *entry = set->buckets[index];
    while (entry != NULL) {
        if (entry->key == value) {
            dsc_set_error(DSC_ERROR_NONE);
            return true;
        }
        entry = entry->next;
    }

    dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
    return false;
}

size_t dsc_set_size(const dsc_set_t *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return set->size;
}

bool dsc_set_empty(const dsc_set_t *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return true;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return set->size == 0;
}

void dsc_set_clear(dsc_set_t *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Free all the entries in the set. */
    for (size_t i = 0; i < set->capacity; ++i) {
        dsc_set_entry_t *entry = set->buckets[i];
        while (entry != NULL) {
            dsc_set_entry_t *next = entry->next;
            free(entry);
            entry = next;
        }
        set->buckets[i] = NULL;
    }

    set->size = 0;
    dsc_set_error(DSC_ERROR_NONE);
}
