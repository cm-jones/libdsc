// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/unordered_map.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75f

static size_t find_slot(dsc_unordered_map const *map, void const *key,
                        size_t hash) {
    size_t mask = map->capacity - 1;
    size_t idx = hash & mask;

    while (map->hashes[idx] != 0) {
        if (map->hashes[idx] == hash &&
            map->compare_fn((char *)map->keys + idx * map->key_size, key) ==
                0) {
            return idx;
        }
        idx = (idx + 1) & mask;
    }
    return idx;
}

static dsc_error rehash(dsc_unordered_map *map) {
    size_t old_capacity = map->capacity;
    void *old_keys = map->keys;
    void *old_values = map->values;
    size_t *old_hashes = map->hashes;

    map->capacity *= 2;
    map->keys = calloc(map->capacity, map->key_size);
    map->values = calloc(map->capacity, map->value_size);
    map->hashes = calloc(map->capacity, sizeof(size_t));

    if (!map->keys || !map->values || !map->hashes) {
        free(map->keys);
        free(map->values);
        free(map->hashes);
        map->keys = old_keys;
        map->values = old_values;
        map->hashes = old_hashes;
        map->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_hashes[i] != 0) {
            size_t new_idx = find_slot(
                map, (char *)old_keys + i * map->key_size, old_hashes[i]);

            memcpy((char *)map->keys + new_idx * map->key_size,
                   (char *)old_keys + i * map->key_size, map->key_size);
            memcpy((char *)map->values + new_idx * map->value_size,
                   (char *)old_values + i * map->value_size, map->value_size);
            map->hashes[new_idx] = old_hashes[i];
        }
    }

    free(old_keys);
    free(old_values);
    free(old_hashes);
    return DSC_ERROR_OK;
}

dsc_unordered_map *unordered_map_create(size_t key_size, size_t value_size,
                                          size_t (*hash_fn)(void const *),
                                          int (*compare_fn)(void const *,
                                                            void const *)) {
    dsc_unordered_map *map = malloc(sizeof(dsc_unordered_map));
    if (!map) return NULL;

    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_fn = hash_fn;
    map->compare_fn = compare_fn;

    map->keys = calloc(map->capacity, key_size);
    map->values = calloc(map->capacity, value_size);
    map->hashes = calloc(map->capacity, sizeof(size_t));

    if (!map->keys || !map->values || !map->hashes) {
        free(map->keys);
        free(map->values);
        free(map->hashes);
        free(map);
        return NULL;
    }

    return map;
}

void unordered_map_destroy(dsc_unordered_map *map) {
    if (!map) return;
    free(map->keys);
    free(map->values);
    free(map->hashes);
    free(map);
}

size_t unordered_map_size(dsc_unordered_map const *map) {
    return map ? map->size : 0;
}

bool unordered_map_empty(dsc_unordered_map const *map) {
    return !map || map->size == 0;
}

dsc_error unordered_map_insert(dsc_unordered_map *map, void const *key,
                                 void const *value) {
    if (!map || !key || !value) return DSC_ERROR_INVALID_ARGUMENT;

    if ((float)map->size / map->capacity >= LOAD_FACTOR) {
        dsc_error err = rehash(map);
        if (err != DSC_ERROR_OK) return err;
    }

    size_t hash = map->hash_fn(key);
    size_t idx = find_slot(map, key, hash);

    if (map->hashes[idx] == 0) {
        ++(map->size);
    }

    memcpy((char *)map->keys + idx * map->key_size, key, map->key_size);
    memcpy((char *)map->values + idx * map->value_size, value, map->value_size);
    map->hashes[idx] = hash;

    return DSC_ERROR_OK;
}

void *unordered_map_find(dsc_unordered_map *map, void const *key) {
    if (!map || !key) return NULL;

    size_t hash = map->hash_fn(key);
    size_t idx = find_slot(map, key, hash);

    if (map->hashes[idx] == 0) return NULL;

    return (char *)map->values + idx * map->value_size;
}

dsc_error unordered_map_erase(dsc_unordered_map *map, void const *key) {
    if (!map || !key) return DSC_ERROR_INVALID_ARGUMENT;

    size_t hash = map->hash_fn(key);
    size_t idx = find_slot(map, key, hash);

    if (map->hashes[idx] == 0) return DSC_ERROR_NOT_FOUND;

    map->hashes[idx] = 0;
    map->size--;

    // Rehash remaining elements
    size_t mask = map->capacity - 1;
    size_t next = (idx + 1) & mask;

    while (map->hashes[next] != 0) {
        size_t existing_hash = map->hashes[next];
        size_t new_idx = find_slot(
            map, (char *)map->keys + next * map->key_size, existing_hash);

        if (new_idx != next) {
            memcpy((char *)map->keys + new_idx * map->key_size,
                   (char *)map->keys + next * map->key_size, map->key_size);
            memcpy((char *)map->values + new_idx * map->value_size,
                   (char *)map->values + next * map->value_size,
                   map->value_size);
            map->hashes[new_idx] = existing_hash;
            map->hashes[next] = 0;
        }

        next = (next + 1) & mask;
    }

    return DSC_ERROR_OK;
}

void unordered_map_clear(dsc_unordered_map *map) {
    if (!map) return;

    memset(map->hashes, 0, map->capacity * sizeof(size_t));
    map->size = 0;
}

dsc_error unordered_map_reserve(dsc_unordered_map *map, size_t n) {
    if (!map) return DSC_ERROR_INVALID_ARGUMENT;

    if (n <= map->capacity) return DSC_ERROR_OK;

    size_t old_capacity = map->capacity;
    map->capacity = n;

    void *new_keys = calloc(map->capacity, map->key_size);
    void *new_values = calloc(map->capacity, map->value_size);
    size_t *new_hashes = calloc(map->capacity, sizeof(size_t));

    if (!new_keys || !new_values || !new_hashes) {
        free(new_keys);
        free(new_values);
        free(new_hashes);
        map->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (map->hashes[i] != 0) {
            size_t new_idx = find_slot(
                map, (char *)map->keys + i * map->key_size, map->hashes[i]);

            memcpy((char *)new_keys + new_idx * map->key_size,
                   (char *)map->keys + i * map->key_size, map->key_size);
            memcpy((char *)new_values + new_idx * map->value_size,
                   (char *)map->values + i * map->value_size, map->value_size);
            new_hashes[new_idx] = map->hashes[i];
        }
    }

    free(map->keys);
    free(map->values);
    free(map->hashes);

    map->keys = new_keys;
    map->values = new_values;
    map->hashes = new_hashes;

    return DSC_ERROR_OK;
}
