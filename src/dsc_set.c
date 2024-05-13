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

typedef struct DSCSetEntry DSCSetEntry;

struct DSCSetEntry {
    DSCData key;           // The key stored in the entry
    DSCSetEntry *next;     // Pointer to the next entry in case of collisions
};

struct DSCSet {
    DSCSetEntry **buckets; // Array of pointers to entries
    size_t size;           // The number of elements currently in the hash set
    size_t capacity;       // The current capacity of the hash set
    DSCType type;          // The type of the set elements
};

static bool dsc_set_rehash(DSCSet *set, size_t new_capacity) {
    DSCSetEntry **new_buckets = calloc(new_capacity, sizeof(DSCSetEntry *));
    if (new_buckets == NULL) {
        return false;
    }

    // Rehash all the elements into the new buckets
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry *entry = set->buckets[i];
        while (entry) {
            DSCSetEntry *next = entry->next;
            uint32_t index;

            switch (set->type) {
                case DSC_TYPE_CHAR: {
                    index = dsc_hash(&entry->key.c, set->type, new_capacity);
                    break;
                }

                case DSC_TYPE_INT: {
                    index = dsc_hash(&entry->key.i, set->type, new_capacity);
                    break;
                }

                case DSC_TYPE_FLOAT: {
                    index = dsc_hash(&entry->key.f, set->type, new_capacity);
                    break;
                }

                case DSC_TYPE_DOUBLE: {
                    index = dsc_hash(&entry->key.d, set->type, new_capacity);
                    break;
                }

                case DSC_TYPE_STRING: {
                    index = dsc_hash(&entry->key.s, set->type, new_capacity);
                    break;
                }

                case DSC_TYPE_BOOL: {
                    index = dsc_hash(&entry->key.s, set->type, new_capacity);
                    break;
                }
            }

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

DSCError dsc_set_init(DSCSet *new_set, DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return DSC_ERROR_INVALID_TYPE;
    }

    new_set = malloc(sizeof new_set);
    if (new_set == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    new_set->size = 0;
    new_set->capacity = DSC_SET_INITIAL_CAPACITY;
    new_set->type = type;

    new_set->buckets = calloc(new_set->capacity, sizeof(DSCSetEntry *));
    if (new_set->buckets == NULL) {
        free(new_set);
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    return DSC_ERROR_OK;
}

DSCError dsc_set_deinit(DSCSet *set) {
    if (set == NULL) { 
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Free all of the entries in the set
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry *curr = set->buckets[i];

        while (curr) {
            if (set->type == DSC_TYPE_STRING) {
                free(curr->key.s);
            }

            DSCSetEntry *next = curr->next;
            free(curr);
            curr = next;
        }
    }

    // Free the buckets array and the set itself
    free(set->buckets);
    free(set);
    
    return DSC_ERROR_OK;
}

DSCError dsc_set_size(const DSCSet *set, size_t *size) {
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *size = set->size;

    return DSC_ERROR_OK;
}

DSCError dsc_set_capacity(const DSCSet *set, size_t *capacity) {
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *capacity = set->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_set_load_factor(const DSCSet *set, double *load_factor) {
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *load_factor = (double) set->size / set->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_set_is_empty(const DSCSet *set, bool *is_empty) {
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *is_empty = set->size == 0;

    return DSC_ERROR_OK;
}

DSCError dsc_set_contains(const DSCSet *set, void *key, bool *contains) {
    if (set == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Hash the value to determine the bucket index
    uint32_t index = dsc_hash(key, set->type, set->capacity);

    *contains = false;

    // Search for the value in the bucket
    DSCSetEntry *entry = set->buckets[index];
    while (entry) {
        switch (set->type) {
            case DSC_TYPE_CHAR: {
                if (entry->key.c == *(char *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }
    
                break;
            }

            case DSC_TYPE_INT: {
                if (entry->key.i == *(int *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_FLOAT: {
                if (entry->key.f == *(float *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_DOUBLE: {
                if (entry->key.d == *(double *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_STRING: {
                if (strcmp(entry->key.s, *(char **) key) == 0) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_BOOL: {
                if (entry->key.b == *(bool *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }
        }

        entry = entry->next;
    }

    return DSC_ERROR_NOT_FOUND;
}

DSCError dsc_set_insert(DSCSet *set, void *key) {
    if (set == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    bool contains;
    dsc_set_contains(set, key, &contains);

    if (contains) {
        return DSC_ERROR_ALREADY_EXISTS;
    }

    // Resize the set if the load factor exceeds the threshold
    if (set->size >= DSC_SET_LOAD_FACTOR * set->capacity) {
        size_t new_capacity = set->capacity * 2;
        if (!dsc_set_rehash(set, new_capacity)) {
            return DSC_ERROR_OUT_OF_MEMORY;
        }
    }

    DSCSetEntry *new_entry = malloc(sizeof new_entry);
    if (new_entry == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }

    switch (set->type) {
        case DSC_TYPE_CHAR: {
            new_entry->key.c = *(char *) key;
            break;
        }

        case DSC_TYPE_INT: {
            new_entry->key.i = *(int *) key;
            break;
        }

        case DSC_TYPE_FLOAT: {
            new_entry->key.f = *(float *) key;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            new_entry->key.d = *(double *) key;
            break;
        }

        case DSC_TYPE_STRING: {
            dsc_str_cpy(&new_entry->key.s, *(char **) key);
            break;
        }

        case DSC_TYPE_BOOL: {
            new_entry->key.b = *(bool *) key;
            break;
        }
    }

    new_entry->next = NULL;

    // Hash the value to determine the bucket index
    uint32_t index = dsc_hash(key, set->type, set->capacity);

    // Insert the new entry at the beginning of the bucket
    new_entry->next = set->buckets[index];
    set->buckets[index] = new_entry;
    set->size++;

    return DSC_ERROR_OK;
}

DSCError dsc_set_erase(DSCSet *set, void *key) {
    if (set == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    uint32_t index = dsc_hash(key, set->type, set->capacity);

    DSCSetEntry *curr = set->buckets[index];
    DSCSetEntry *prev = NULL;

    while (curr) {
        switch (set->type) {
            case DSC_TYPE_CHAR: {
                if (curr->key.c == *(char *) key) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }

            case DSC_TYPE_INT: {
                if (curr->key.i == *(int *) key) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }

            case DSC_TYPE_FLOAT: {
                if (curr->key.f == *(float *) key) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }

            case DSC_TYPE_DOUBLE: {
                if (curr->key.d == *(double *) key) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }

            case DSC_TYPE_STRING: {
                if (strcmp(curr->key.s, *(char **) key) == 0) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr->key.s);
                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }

            case DSC_TYPE_BOOL: {
                if (curr->key.b == *(bool *) key) {
                    if (!prev) {
                        set->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    set->size--;

                    return DSC_ERROR_OK;
                }
            }
        }

        prev = curr;
        curr = curr->next;
    }

    return DSC_ERROR_NOT_FOUND;
}

DSCError dsc_set_clear(DSCSet *set) {
    if (set == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    // Free all the entries in the set
    for (size_t i = 0; i < set->capacity; ++i) {
        DSCSetEntry *curr = set->buckets[i];

        while (curr) {
            DSCSetEntry *next = curr->next;

            if (set->type == DSC_TYPE_STRING) {
                free(curr->key.s);
                curr->key.s = NULL;
            }

            free(curr);
            curr = next;
        }

        set->buckets[i] = NULL;
    }

    set->size = 0;

    return DSC_ERROR_OK;
}
