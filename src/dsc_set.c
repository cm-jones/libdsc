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

#include "../include/dsc_set.h"
#include "../include/dsc_utils.h"
#include "../include/dsc_error.h"

/* Represents an entry in the hash set. */
struct DSCSetEntry {
    int key;                          /* The key of the entry. */
    DSCSetEntry *next;     /* Pointer to the next entry in case of collisions. */
};

/* Represents a hash set. */
struct DSCSet {
    DSCSetEntry **buckets; /* Array of pointers to entries. */
    unsigned int size;            /* The number of elements in the hash set. */
    unsigned int capacity;        /* The current capacity of the hash set. */
};

static void dsc_set_rehash(DSCSet *set, unsigned int new_capacity) {
    DSCSetEntry **new_buckets = calloc(new_capacity, sizeof(DSCSetEntry *));
    if (new_buckets == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return;
    }

    /* Rehash all the elements into the new buckets. */
    for (unsigned int i = 0; i < set->capacity; ++i) {
        DSCSetEntry *entry = set->buckets[i];
        while (entry != NULL) {
            DSCSetEntry *next = entry->next;

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

DSCSet *dsc_set_create(void) {
    DSCSet *new_set = calloc(1, sizeof *new_set);
    if (new_set == NULL) {
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    new_set->size = 0;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;

    new_set->buckets = calloc(new_set->capacity, sizeof(DSCSetEntry *));
    if (new_set->buckets == NULL) {
        free(new_set);
        dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
        return NULL;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return new_set;
}

void dsc_set_free(DSCSet *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Free all the entries in the set */
    for (unsigned int i = 0; i < set->capacity; ++i) {
        DSCSetEntry *curr = set->buckets[i];
        while (curr != NULL) {
            DSCSetEntry *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    /* Free the buckets array and the set itself */
    free(set->buckets);
    free(set);
    dsc_set_error(DSC_ERROR_NONE);
}

bool dsc_set_insert(DSCSet *set, int value) {
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
        unsigned int new_capacity = set->capacity * 2;
        dsc_set_rehash(set, new_capacity);
    }

    /* Create a new entry */
    DSCSetEntry *new_entry = malloc(sizeof *new_entry);
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

bool dsc_set_erase(DSCSet *set, int value) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    int index = dsc_hash(value, set->capacity);

    DSCSetEntry *prev = NULL;
    DSCSetEntry *entry = set->buckets[index];

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

bool dsc_set_contains(const DSCSet *set, int value) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return false;
    }

    /* Hash the value to determine the bucket index */
    int index = dsc_hash(value, set->capacity);

    /* Search for the value in the bucket */
    DSCSetEntry *entry = set->buckets[index];
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

int dsc_set_size(const DSCSet *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return -1;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return set->size;
}

bool dsc_set_empty(const DSCSet *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return true;
    }

    dsc_set_error(DSC_ERROR_NONE);
    return set->size == 0;
}

void dsc_set_clear(DSCSet *set) {
    if (set == NULL) {
        dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
        return;
    }

    /* Free all the entries in the set. */
    for (unsigned int i = 0; i < set->capacity; ++i) {
        DSCSetEntry *entry = set->buckets[i];
        while (entry != NULL) {
            DSCSetEntry *next = entry->next;
            free(entry);
            entry = next;
        }
        set->buckets[i] = NULL;
    }

    set->size = 0;
    dsc_set_error(DSC_ERROR_NONE);
}
