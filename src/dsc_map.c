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

#include "../include/dsc_map.h"
#include "../include/dsc_utils.h"

/* Represents an entry in a hash map */

typedef struct DSCMapEntry *DSCMapEntry;

struct DSCMapEntry {
   void *key;             /* Key of the entry */
   void *value;           /* Value associated with the key */
   DSCMapEntry next;      /* Pointer to the next entry in the same bucket */
};

/* Represents a hash map  */

struct DSCMap {
    DSCMapEntry *buckets; /* Array of pointers to entries */
    size_t size;          /* The number of elements currently in the hash map */
    size_t capacity;      /* The current capacity of the hash map */
    DSCType key_type;     /* The type of the keys in the map */
    DSCType value_type;   /* The type of the values in the map */
    DSCError error;       /* The most recent error code */
};

/* Helper method to rehash all the entries in the DSCMap when the load factor exceeds the threshold */

static bool dsc_map_rehash(DSCMap map, size_t new_capacity) {
   DSCMapEntry *new_buckets = calloc(new_capacity, sizeof(DSCMapEntry *));
   if (!new_buckets) {
       return false;
   }

   // Rehash all the elements into the new buckets
   for (size_t i = 0; i < map->capacity; ++i) {
       DSCMapEntry entry = map->buckets[i];
       while (entry) {
           DSCMapEntry next = entry->next;

           // Rehash the value to determine the new index
           uint32_t index = dsc_hash(entry->key, map->key_type, new_capacity);

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

/* Constructor and destructor for a DSCMap */

DSCMap dsc_map_init(DSCType key_type, DSCType value_type) {
    if (!dsc_type_is_valid(key_type) || !dsc_type_is_valid(value_type)) {
        return NULL;
    }

    DSCMap new_map = malloc(sizeof *new_map);
    if (!new_map) {
        return NULL;
    }

    new_map->buckets = malloc(new_map->capacity * sizeof(DSCMapEntry));
    if (!new_map->buckets) {
        free(new_map);
        return NULL;
    }
    
    new_map->size = 0;
    new_map->capacity = DSC_MAP_INITIAL_CAPACITY;
    new_map->key_type = key_type;
    new_map->value_type = value_type;
    new_map->error = DSC_ERROR_OK;
    
    return new_map;
}

bool dsc_map_deinit(DSCMap map) {
    if (!map) {
        return false;
    }
    
    // Free all the entries in the map
    for (size_t i = 0; i < map->capacity; ++i) {
        DSCMapEntry curr = map->buckets[i];
        while (curr) {
            DSCMapEntry next = curr->next;
            free(curr);
            curr = next;
        }
    }
    
    // Free the buckets array and the map itself
    free(map->buckets);
    free(map);

    return true;
}

/* Capacity */

bool dsc_map_is_empty(const DSCMap map) {
    if (!map) {
        return false;
    }
    
    map->error = DSC_ERROR_OK;
    
    return map->size == 0;
}

int dsc_map_size(const DSCMap map) {
    if (!map) {
        return -1;
    }
    
    map->error = DSC_ERROR_OK;
    
    return map->size;
}

/* Element access */

void *dsc_map_get(const DSCMap map, void *key) {
    if (!map) {
        return NULL;
    }

    // Check if the type of the key to get the associated value of is valid
    if (dsc_typeof(key) != map->key_type) {
        map->error = DSC_ERROR_TYPE_MISMATCH;
        return NULL;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);
    
    DSCMapEntry entry = map->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            map->error = DSC_ERROR_OK;
            return entry->value;
        }
        
        entry = entry->next;
    }
    
    map->error = DSC_ERROR_KEY_NOT_FOUND;
    
    return NULL;
}

/* Modifiers */

bool dsc_map_insert(DSCMap map, void *key, void *value) {
    if (!map) {
        return false;
    }

    // Check if the type of the new key and value are both valid
    if (dsc_typeof(key) != map->key_type || dsc_typeof(value) != map->value_type) {
        map->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }
    
    // Check if the key already exists
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);

    DSCMapEntry entry = map->buckets[index];
    while (entry) {
        if (dsc_compare(entry->key, key, map->key_type)) {
            map->error = DSC_ERROR_KEY_ALREADY_EXISTS;
            return false;
        }
        entry = entry->next;
    }
    
    // Create a new entry
    entry = malloc(sizeof(DSCMapEntry));
    if (!entry) {
        map->error = DSC_ERROR_OUT_OF_MEMORY;
        return false;
    }
    
    entry->key = key;
    entry->value = value;
    
    // Insert the entry into the appropriate bucket
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
    map->size++;
    
    // Rehash if the load factor exceeds the threshold
    if (map->size > DSC_MAP_LOAD_FACTOR * map->capacity) {
        dsc_map_rehash(map, map->capacity * 2);
    }

    map->error = DSC_ERROR_OK;
    
    return true;
}

bool dsc_map_erase(DSCMap map, void *key) {
    if (!map) {
        return false;
    }

    // Check if the type of the key to erase is valid
    if (dsc_typeof(key) != map->key_type) {
        map->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);
    
    DSCMapEntry prev = NULL;
    DSCMapEntry entry = map->buckets[index];
    
    while (entry) {
        if (dsc_compare(entry->key, key, map->key_type) == 0) {
            if (!prev) {
                map->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            
            free(entry);
            map->size--;
            map->error = DSC_ERROR_OK;
            
            return true;
        }
        
        prev = entry;
        entry = entry->next;
    }

    map->error = DSC_ERROR_KEY_NOT_FOUND;
    
    return false;
}

bool dsc_map_contains(const DSCMap map, void *key) {
    if (!map) {
        return false;
    }

    // Check if the type of the key to look for is valid
    if (dsc_typeof(key) != map->key_type) {
        map->error = DSC_ERROR_TYPE_MISMATCH;
        return false;
    }
    
    uint32_t index = dsc_hash(key, map->key_type, map->capacity);

    DSCMapEntry entry = map->buckets[index];
    
    while (entry) {
        if (dsc_compare(entry->key, key, map->key_type) == 0) {
            map->error = DSC_ERROR_OK;
            return true;
        }
        
        entry = entry->next;
    }
    
    map->error = DSC_ERROR_KEY_NOT_FOUND;
    
    return false;
}

bool dsc_map_clear(DSCMap map) {
    if (!map) {
        return false;
    }
    
    // Free all the entries in the map
    for (size_t i = 0; i < map->capacity; ++i) {
        DSCMapEntry entry = map->buckets[i];

        while (entry) {
            DSCMapEntry next = entry->next;
            free(entry);
            entry = next;
        }

        map->buckets[i] = NULL;
    }
    
    map->size = 0;
    map->error = DSC_ERROR_OK;
    
    return true;
}

/* Error handling */

DSCError dsc_map_error(const DSCMap map) {
    return map->error;
}
