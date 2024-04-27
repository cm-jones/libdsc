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

/* Represents an entry in the hash set. */

typedef struct DSCSetEntry *DSCSetEntry;

struct DSCSetEntry {
    void *key;        /* The key of the entry */
    DSCSetEntry next; /* Pointer to the next entry in case of collisions */
};

/* Represents a hash set */

struct DSCSet {
    DSCSetEntry *buckets; /* Array of pointers to entries */
    size_t size;          /* The number of elements currently in the hash set */
    size_t capacity;      /* The current capacity of the hash set */
    DSCType type;         /* The type of the set elements */
    DSCError error;       /* The most recent error code */
};

static bool dsc_set_rehash(DSCSet set, size_t new_capacity) {
    DSCSetEntry *new_buckets = calloc(new_capacity, sizeof(DSCSetEntry *));
    if (!new_buckets) {
        return false;
    }

    // Rehash all the elements into the new buckets. */
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry entry = set->buckets[i];
        while (entry) {
            DSCSetEntry next = entry->next;

            /* Rehash the value to determine the new index. */
            uint32_t index = dsc_hash(entry->key, set->type, new_capacity);

            entry->next = new_buckets[index];
            new_buckets[index] = entry;
            entry = next;
        }
    }

    free(set->buckets);
    set->buckets = new_buckets;
    set->capacity = new_capacity;

    return true;
}

/* Constructor and destructor for a DSCSet */

DSCSet dsc_set_init(DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return NULL;
    }

    DSCSet new_set = malloc(sizeof *new_set);
    if (!new_set) {
        return NULL;
    }

    new_set->buckets = calloc(new_set->capacity, sizeof(DSCSetEntry *));
    if (!new_set->buckets) {
        free(new_set);
        return NULL;
    }

    new_set->size = 0;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;
    new_set->type = type;
    new_set->error = DSC_ERROR_OK;

    return new_set;
}

bool dsc_set_deinit(DSCSet set) {
    if (!set) { 
        return false;
    }

    // Free all of the entries in the set
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry curr = set->buckets[i];
        while (curr) {
            DSCSetEntry next = curr->next;
            free(curr);
            curr = next;
        }
    }

    // Free the buckets array and the set itself
    free(set->buckets);
    free(set);
    
    return true;
}

/* Capacity */

bool dsc_set_is_empty(const DSCSet set) {
    if (!set) {
        return false;
    }

    set->error = DSC_ERROR_OK;

    return set->size == 0;
}

int dsc_set_size(const DSCSet set) {
    if (!set) {
        return -1;
    }

    set->error = DSC_ERROR_OK;

    return set->size;
}

int dsc_set_capacity(const DSCSet set) {
    if (!set) {
        return -1;
    }

    set->error = DSC_ERROR_OK;

    return set->capacity;
}

double dsc_set_load_factor(const DSCSet set) {
    if (!set) {
        return -1.0;
    }

    set->error = DSC_ERROR_OK;

    return (double) set->size / set->capacity;
}


/* Element access */

bool dsc_set_contains(const DSCSet set, void *key) {
    if (!set) {
        return false;
    }

    // Check if the type of the key is valid
    if (dsc_typeof(key) != set->type) {
        set->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    // Hash the value to determine the bucket index
    uint32_t index = dsc_hash(key, set->type, set->capacity);

    // Search for the value in the bucket
    DSCSetEntry entry = set->buckets[index];
    while (entry) {
        if (entry->key == key) {
            set->error = DSC_ERROR_OK;
            return true;
        }

        entry = entry->next;
    }

    set->error = DSC_ERROR_KEY_NOT_FOUND;

    return false;
}

/* Modifiers */

bool dsc_set_insert(DSCSet set, void *key) {
    if (!set) {
        return false;
    }

    // Check if the type of the new key is valid
    if (dsc_typeof(key) != set->type) {
        set->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    if (dsc_set_contains(set, key)) {
        set->error = DSC_ERROR_KEY_ALREADY_EXISTS;
        return false;
    }

    // Resize the set if the load factor exceeds the threshold
    if (set->size >= DSC_SET_LOAD_FACTOR * set->capacity) {
        size_t new_capacity = dsc_next_prime(set->capacity * 2);
        if (!dsc_set_rehash(set, new_capacity)) {
            set->error = DSC_ERROR_OUT_OF_MEMORY;
            return false;
        }
    }

    // Create a new entry
    DSCSetEntry new_entry = malloc(sizeof *new_entry);
    if (!new_entry) {
        set->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }

    new_entry->key = key;
    new_entry->next = NULL;

    // Hash the value to determine the bucket index
    uint32_t index = dsc_hash(key, set->type, set->capacity);

    // Insert the new entry at the beginning of the bucket
    new_entry->next = set->buckets[index];
    set->buckets[index] = new_entry;
    set->size++;

    set->error = DSC_ERROR_OK;

    return true;
}

bool dsc_set_erase(DSCSet set, void *key) {
    if (!set) {
        return false;
    }

    // Check if the type of the key is valid
    if (dsc_typeof(key) != set->type) {
        set->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }

    uint32_t index = dsc_hash(key, set->type, set->capacity);

    DSCSetEntry entry = set->buckets[index];
    DSCSetEntry prev = NULL;

    while (entry) {
        if (entry->key == key) {
            if (!prev) {
                set->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
        
            free(entry);
            set->size--;
            set->error = DSC_ERROR_OK;

            return true;
        }

        prev = entry;
        entry = entry->next;
    }

    set->error = DSC_ERROR_KEY_NOT_FOUND;

    return false;
}

bool dsc_set_clear(DSCSet set) {
    if (!set) {
        return false;
    }

    // Free all the entries in the set
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry entry = set->buckets[i];

        while (entry) {
            DSCSetEntry next = entry->next;
            free(entry);
            entry = next;
        }

        set->buckets[i] = NULL;
    }

    set->size = 0;
    set->error = DSC_ERROR_OK;

    return true;
}
