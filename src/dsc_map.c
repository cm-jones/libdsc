// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>

#include "../include/dsc_map.h"
#include "../include/dsc_utils.h"

typedef struct DSCMapEntry DSCMapEntry;

struct DSCMapEntry {
   DSCData key;            // Key of the entry
   DSCData value;          // Value associated with the key
   DSCMapEntry *next;      // Pointer to the next entry in the same bucket
};

struct DSCMap {
    DSCMapEntry **buckets; // Array of pointers to entries
    size_t size;           // The number of elements currently in the hash map
    size_t capacity;       // The current capacity of the hash map
    DSCType key_type;      // The type of the keys in the map
    DSCType value_type;    // The type of the values in the map
};

/* Helper method to rehash all the entries in the DSCMap when the load factor exceeds the threshold */

static bool dsc_map_rehash(DSCMap *map, size_t new_capacity) {
   DSCMapEntry **new_buckets = calloc(new_capacity, sizeof(DSCMapEntry*));
   if (new_buckets == NULL) {
       return false;
   }

   // Rehash all the elements into the new buckets
   for (size_t i = 0; i < map->capacity; ++i) {
       DSCMapEntry *entry = map->buckets[i];
       while (entry) {
            DSCMapEntry *next = entry->next;

            // Rehash the value to determine the new index
            uint32_t index;
            switch (map->key_type) {
                case DSC_TYPE_CHAR: {
                    index = dsc_hash(&entry->key.c, map->key_type, new_capacity);
                    break;
                }

                case DSC_TYPE_INT: {
                    index = dsc_hash(&entry->key.i, map->key_type, new_capacity);
                    break;
                }

                case DSC_TYPE_FLOAT: {
                    index = dsc_hash(&entry->key.f, map->key_type, new_capacity);
                    break;
                }

                case DSC_TYPE_DOUBLE: {
                    index = dsc_hash(&entry->key.d, map->key_type, new_capacity);
                    break;
                }

                case DSC_TYPE_STRING: {
                    index = dsc_hash(&entry->key.s, map->key_type, new_capacity);
                    break;
                }

                default: {
                    return false;
                }
            }

           entry->next = new_buckets[index];
           new_buckets[index] = entry;
           entry = next;
       }
   }

   free(map->buckets);
   map->buckets = new_buckets;
   map->capacity = new_capacity;

   return true;
}

DSCError dsc_map_init(DSCMap *new_map, DSCType key_type, DSCType value_type) {
    if (new_map == NULL || !dsc_type_is_valid(key_type) || !dsc_type_is_valid(value_type)) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    new_map->size = 0;
    new_map->capacity = DSC_MAP_INITIAL_CAPACITY;
    new_map->key_type = key_type;
    new_map->value_type = value_type;

    new_map->buckets = calloc(new_map->capacity, sizeof(DSCMapEntry *));
    if (new_map->buckets == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }
    
    return DSC_ERROR_OK;
}

DSCError dsc_map_deinit(DSCMap *map) {
    if (map == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    for (size_t i = 0; i < map->capacity; ++i) {
        DSCMapEntry *curr = map->buckets[i];

        while (curr != NULL) {
            DSCMapEntry *next = curr->next;

            if (map->key_type == DSC_TYPE_STRING) {
                free(curr->key.s);
            }

            if (map->value_type == DSC_TYPE_STRING) {
                free(curr->value.s);
            }

            free(curr);
            curr = next;
        }
    }
    
    free(map->buckets);
    free(map);

    return DSC_ERROR_OK;
}

DSCError dsc_map_size(const DSCMap *map, size_t *size) {
    if (map == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    *size = map->size;
    
    return DSC_ERROR_OK;
}

DSCError dsc_map_capacity(const DSCMap *map, size_t *capacity) {
    if (map == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }

    *capacity = map->capacity;

    return DSC_ERROR_OK;
}

DSCError dsc_map_empty(const DSCMap *map, bool *is_empty) {
    if (map == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    *is_empty = map->size == 0;
    
    return DSC_ERROR_OK;
}

DSCError dsc_map_get(const DSCMap *map, void *key, void *value) {
    if (map == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);
    
    DSCMapEntry *curr = map->buckets[index];
    
    while (curr != NULL) {
        switch (map->key_type) {
            case DSC_TYPE_CHAR: {
                if (curr->key.c == *(char *) key) {
                    *(char *) value = curr->value.c;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_INT: {
                if (curr->key.i == *(int *) key) {
                    *(int *) value = curr->value.i;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_FLOAT: {
                if (curr->key.f == *(float *) key) {
                    *(float *) value = curr->value.f;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_DOUBLE: {
                if (curr->key.d == *(double *) key) {
                    *(double *) value = curr->value.d;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_STRING: {
                if (strcmp(curr->key.s, *(char **) key) == 0) {
                    const char *string = curr->value.s;
                    size_t string_size = strlen(string) + 1;
                    size_t key_size = strlen(*(char **) key) + 1;

                    if (string_size > key_size) {
                        *(char **) value = malloc(string_size);
                        if (*(char **) value == NULL) {
                            return DSC_ERROR_OUT_OF_MEMORY;
                        }
                    }
                    return DSC_ERROR_OK;
                }

                break;
            }
        }
        
        curr = curr->next;
    }
    
    return DSC_ERROR_NOT_FOUND;
}

DSCError dsc_map_insert(DSCMap *map, void *key, void *value) {
    if (map == NULL || key == NULL || value == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    // Check if the key already exists
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);

    DSCMapEntry *curr = map->buckets[index];
    while (curr != NULL) {
        switch (map->key_type) {
            case DSC_TYPE_CHAR: {
                if (curr->key.c == *(char *) key) {
                    return DSC_ERROR_ALREADY_EXISTS;
                }

                break;
            }

            case DSC_TYPE_INT: {
                if (curr->key.i == *(int *) key) {
                    return DSC_ERROR_ALREADY_EXISTS;
                }

                break;
            }

            case DSC_TYPE_FLOAT: {
                if (curr->key.f == *(float *) key) {
                    return DSC_ERROR_ALREADY_EXISTS;
                }

                break;
            }

            case DSC_TYPE_DOUBLE: {
                if (curr->key.d == *(double *) key) {
                    return DSC_ERROR_ALREADY_EXISTS;
                }

                break;
            }

            case DSC_TYPE_STRING: {
                if (strcmp(curr->key.s, *(char **) key) == 0) {
                    return DSC_ERROR_ALREADY_EXISTS;
                }

                break;
            }

            default: {
                return DSC_ERROR_INVALID_TYPE;
            }
        }

        curr = curr->next;
    }
    
    // Create a new entry
    DSCMapEntry *new_entry = malloc(sizeof(DSCMapEntry));
    if (new_entry == NULL) {
        return DSC_ERROR_OUT_OF_MEMORY;
    }
    
    switch (map->key_type) {
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
            char *str = *(char **) key;
            size_t str_size = strlen(str) + 1;

            new_entry->key.s = malloc(str_size);
            if (new_entry->key.s == NULL) {
                free(new_entry);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(new_entry->key.s, str, str_size - 1);
            new_entry->key.s[str_size - 1] = '\0';

            break;
        }

        default: {
            return DSC_ERROR_INVALID_TYPE;
        }
    }

    switch (map->value_type) {
        case DSC_TYPE_CHAR: {
            new_entry->value.c = *(char *) value;
            break;
        }

        case DSC_TYPE_INT: {
            new_entry->value.i = *(int *) value;
            break;
        }

        case DSC_TYPE_FLOAT: {
            new_entry->value.f = *(float *) value;
            break;
        }

        case DSC_TYPE_DOUBLE: {
            new_entry->value.d = *(double *) value;
            break;
        }

        case DSC_TYPE_STRING: {
            char *str = *(char **) value;
            size_t str_size = strlen(str);

            new_entry->value.s = malloc(str_size + 1);
            if (new_entry->value.s == NULL) {
                free(new_entry);
                return DSC_ERROR_OUT_OF_MEMORY;
            }

            strncpy(new_entry->value.s, str, str_size);
            new_entry->value.s[str_size] = '\0';

            break;
        }
    }
    
    // Insert the entry into the appropriate bucket
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->size++;
    
    // Rehash if the load factor exceeds the threshold
    if (map->size >= DSC_MAP_LOAD_FACTOR * map->capacity) {
        dsc_map_rehash(map, map->capacity * 2);
    }
    
    return DSC_ERROR_OK;
}

DSCError dsc_map_erase(DSCMap *map, void *key) {
    if (map == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);
    
    DSCMapEntry *prev = NULL;
    DSCMapEntry *curr = map->buckets[index];
    
    while (curr != NULL) {
        switch (map->key_type) {
            case DSC_TYPE_CHAR: {
                if (curr->key.c == *(char *) key) {
                    if (prev == NULL) {
                        map->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    map->size--;
            
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_INT: {
                if (curr->key.i == *(int *) key) {
                    if (prev == NULL) {
                        map->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    map->size--;
            
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_FLOAT: {
                if (curr->key.f == *(float *) key) {
                    if (prev == NULL) {
                        map->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    map->size--;
            
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_DOUBLE: {
                if (curr->key.d == *(double *) key) {
                    if (prev == NULL) {
                        map->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    free(curr);
                    map->size--;
            
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_STRING: {
                if (strcmp(curr->key.s, *(char **) key) == 0) {
                    if (prev == NULL) {
                        map->buckets[index] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }
                    free(curr->key.s);
                    free(curr);
                    map->size--;
            
                    return DSC_ERROR_OK;
                }

                break;
            }

            default: {
                return DSC_ERROR_INVALID_TYPE;
            }
        }
        
        prev = curr;
        curr = curr->next;
    }
    
    return DSC_ERROR_NOT_FOUND;
}

DSCError dsc_map_contains(const DSCMap *map, void *key, bool *contains) {
    if (map == NULL || key == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);

    DSCMapEntry *curr = map->buckets[index];
    
    while (curr != NULL) {
        switch (map->key_type) {
            case DSC_TYPE_CHAR: {
                if (curr->key.c == *(char *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_INT: {
                if (curr->key.i == *(int *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_FLOAT: {
                if (curr->key.f == *(float *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_DOUBLE: {
                if (curr->key.d == *(double *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_STRING: {
                if (strcmp(curr->key.s, *(char **) key) == 0) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            case DSC_TYPE_BOOL: {
                if (curr->key.b == *(bool *) key) {
                    *contains = true;
                    return DSC_ERROR_OK;
                }

                break;
            }

            default: {
                return DSC_ERROR_INVALID_TYPE;
            }
        }
        
        curr = curr->next;
    }

    *contains = false;
    
    return DSC_ERROR_OK;
}

DSCError dsc_map_clear(DSCMap *map) {
    if (map == NULL) {
        return DSC_ERROR_INVALID_ARGUMENT;
    }
    
    for (size_t i = 0; i < map->capacity; ++i) {
        DSCMapEntry *curr = map->buckets[i];

        while (curr != NULL) {
            DSCMapEntry *next = curr->next;

            if (map->key_type == DSC_TYPE_STRING) {
                free(curr->key.s);
            }

            if (map->value_type == DSC_TYPE_STRING) {
                free(curr->value.s);
            }

            free(curr);

            curr = next;
        }

        map->buckets[i] = NULL;
    }
    
    map->size = 0;
    
    return DSC_ERROR_OK;
}
