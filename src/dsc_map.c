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
#include "../include/dsc_error.h"

/* Represents a hash map entry. */
struct dsc_map_entry_t {
   int key;                       /* Key of the entry. */
   int value;                     /* Value associated with the key. */
   struct dsc_map_entry_t *next;  /* Pointer to the next entry in the same bucket. */
};

/* Represents a hash map. */
struct dsc_map_t {
   struct dsc_map_entry_t **buckets;  /* Array of buckets (linked lists). */
   size_t size;                       /* Number of entries in the map. */
   size_t capacity;                   /* Number of buckets in the map. */
};

static void dsc_map_rehash(dsc_map_t *map, size_t new_capacity) {
   dsc_map_entry_t **new_buckets = calloc(new_capacity, sizeof(dsc_map_entry_t *));
   if (new_buckets == NULL) {
       dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
       return;
   }

   /* Rehash all the elements into the new buckets. */
   for (size_t i = 0; i < map->capacity; ++i) {
       dsc_map_entry_t *entry = map->buckets[i];
       while (entry != NULL) {
           dsc_map_entry_t *next = entry->next;

           /* Rehash the value to determine the new index. */
           int index = dsc_hash(entry->key, new_capacity);

           entry->next = new_buckets[index];
           new_buckets[index] = entry;
           entry = next;
       }
   }

   free(map->buckets);
   map->buckets = new_buckets;
   map->capacity = new_capacity;
}

dsc_map_t *dsc_map_create() {
   dsc_map_t *new_map = malloc(sizeof *new_map);
   if (new_map == NULL) {
       dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
       return NULL;
   }

   new_map->size = 0;
   new_map->capacity = DSC_MAP_INITIAL_CAPACITY;

   new_map->buckets = calloc(new_map->capacity, sizeof(dsc_map_entry_t *));
   if (new_map->buckets == NULL) {
       free(new_map);
       dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
       return NULL;
   }

   dsc_set_error(DSC_ERROR_NONE);
   return new_map;
}

void dsc_map_free(dsc_map_t *map) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return;
   }

   /* Free all the entries in the map. */
   for (size_t i = 0; i < map->capacity; ++i) {
       dsc_map_entry_t *curr = map->buckets[i];
       while (curr != NULL) {
           dsc_map_entry_t *next = curr->next;
           free(curr);
           curr = next;
       }
   }

   /* Free the buckets array and the map itself. */
   free(map->buckets);
   free(map);
   dsc_set_error(DSC_ERROR_NONE);
}

bool dsc_map_insert(dsc_map_t *map, int key, int value) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return false;
   }

   /* Check if the key already exists */
   dsc_map_entry_t *entry = map->buckets[dsc_hash(key, map->capacity)];
   while (entry != NULL) {
       if (entry->key == key) {
           entry->value = value;
           dsc_set_error(DSC_ERROR_NONE);
           return false;
       }
       entry = entry->next;
   }

   /* Create a new entry */
   entry = malloc(sizeof(dsc_map_entry_t));
   if (entry == NULL) {
       dsc_set_error(DSC_ERROR_OUT_OF_MEMORY);
       return false;
   }
   entry->key = key;
   entry->value = value;

   /* Insert the entry into the appropriate bucket */
   int index = dsc_hash(key, map->capacity);
   entry->next = map->buckets[index];
   map->buckets[index] = entry;
   map->size++;

   /* Rehash if the load factor exceeds the threshold */
   if (map->size > DSC_MAP_LOAD_FACTOR * map->capacity) {
       dsc_map_rehash(map, map->capacity * 2);
   }

   dsc_set_error(DSC_ERROR_NONE);
   return true;
}

bool dsc_map_erase(dsc_map_t *map, int key) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return false;
   }

   int index = dsc_hash(key, map->capacity);
   dsc_map_entry_t *prev = NULL;
   dsc_map_entry_t *entry = map->buckets[index];

   while (entry != NULL) {
       if (entry->key == key) {
           if (prev == NULL) {
               map->buckets[index] = entry->next;
           } else {
               prev->next = entry->next;
           }
           free(entry);
           map->size--;
           dsc_set_error(DSC_ERROR_NONE);
           return true;
       }
       prev = entry;
       entry = entry->next;
   }

   dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
   return false;
}

int dsc_map_get(const dsc_map_t *map, int key) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return 0;
   }

   int index = dsc_hash(key, map->capacity);
   dsc_map_entry_t *entry = map->buckets[index];

   while (entry != NULL) {
       if (entry->key == key) {
           dsc_set_error(DSC_ERROR_NONE);
           return entry->value;
       }
       entry = entry->next;
   }

   dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
   return 0;
}

bool dsc_map_contains(const dsc_map_t *map, int key) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return false;
   }

   int index = dsc_hash(key, map->capacity);
   dsc_map_entry_t *entry = map->buckets[index];

   while (entry != NULL) {
       if (entry->key == key) {
           dsc_set_error(DSC_ERROR_NONE);
           return true;
       }
       entry = entry->next;
   }

   dsc_set_error(DSC_ERROR_KEY_NOT_FOUND);
   return false;
}

size_t dsc_map_size(const dsc_map_t *map) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return 0;
   }

   dsc_set_error(DSC_ERROR_NONE);
   return map->size;
}

bool dsc_map_empty(const dsc_map_t *map) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return true;
   }

   dsc_set_error(DSC_ERROR_NONE);
   return map->size == 0;
}

void dsc_map_clear(dsc_map_t *map) {
   if (map == NULL) {
       dsc_set_error(DSC_ERROR_INVALID_ARGUMENT);
       return;
   }

   /* Free all the entries in the map */
   for (size_t i = 0; i < map->capacity; ++i) {
       dsc_map_entry_t *entry = map->buckets[i];
       while (entry != NULL) {
           dsc_map_entry_t *next = entry->next;
           free(entry);
           entry = next;
       }
       map->buckets[i] = NULL;
   }

   map->size = 0;
   dsc_set_error(DSC_ERROR_NONE);
}
