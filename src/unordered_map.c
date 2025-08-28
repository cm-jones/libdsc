// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/unordered_map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DSC_UNORDERED_MAP_INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75f

static size_t find_slot(DSCUnorderedMap const *map, void const *key,
                        size_t hash) {
    size_t mask = map->capacity - 1;
    size_t idx = hash & mask;

    while (map->hashes[idx] != 0) {
        size_t key_offset;

        if (!dsc_safe_multiply(idx, map->key_size, &key_offset)) {
            // This should not happen in practice as we control capacity
            return idx;
        }

        if (map->hashes[idx] == hash &&
            map->compare_fn((char *)map->keys + key_offset, key) == 0) {
            return idx;
        }

        idx = (idx + 1) & mask;
    }

    return idx;
}

static DSCError rehash(DSCUnorderedMap *map) {
    size_t old_capacity = map->capacity;
    void *old_keys = map->keys;
    void *old_values = map->values;
    size_t *old_hashes = map->hashes;

    size_t new_capacity;
    if (!dsc_safe_grow_capacity(map->capacity, &new_capacity)) {
        return DSC_ERROR_OVERFLOW;
    }
    map->capacity = new_capacity;

    size_t keys_size, values_size, hashes_size;
    if (!dsc_safe_multiply(map->capacity, map->key_size, &keys_size) ||
        !dsc_safe_multiply(map->capacity, map->value_size, &values_size) ||
        !dsc_safe_multiply(map->capacity, sizeof(size_t), &hashes_size)) {
        map->capacity = old_capacity;
        return DSC_ERROR_OVERFLOW;
    }

    map->keys = dsc_malloc(keys_size);
    map->values = dsc_malloc(values_size);
    map->hashes = dsc_malloc(hashes_size);

    if (!map->keys || !map->values || !map->hashes) {
        dsc_free(map->keys);
        dsc_free(map->values);
        dsc_free(map->hashes);
        map->keys = old_keys;
        map->values = old_values;
        map->hashes = old_hashes;
        map->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    // Initialize memory to zero
    memset(map->keys, 0, keys_size);
    memset(map->values, 0, values_size);
    memset(map->hashes, 0, hashes_size);

    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_hashes[i] != 0) {
            size_t old_key_offset, new_key_offset, old_value_offset,
                new_value_offset;
            if (!dsc_safe_multiply(i, map->key_size, &old_key_offset) ||
                !dsc_safe_multiply(i, map->value_size, &old_value_offset)) {
                // Cleanup and return error
                dsc_free(map->keys);
                dsc_free(map->values);
                dsc_free(map->hashes);
                map->keys = old_keys;
                map->values = old_values;
                map->hashes = old_hashes;
                map->capacity = old_capacity;
                return DSC_ERROR_OVERFLOW;
            }

            size_t new_idx = find_slot(map, (char *)old_keys + old_key_offset,
                                       old_hashes[i]);

            if (!dsc_safe_multiply(new_idx, map->key_size, &new_key_offset) ||
                !dsc_safe_multiply(new_idx, map->value_size,
                                   &new_value_offset)) {
                // Cleanup and return error
                dsc_free(map->keys);
                dsc_free(map->values);
                dsc_free(map->hashes);
                map->keys = old_keys;
                map->values = old_values;
                map->hashes = old_hashes;
                map->capacity = old_capacity;
                return DSC_ERROR_OVERFLOW;
            }

            memcpy((char *)map->keys + new_key_offset,
                   (char *)old_keys + old_key_offset, map->key_size);
            memcpy((char *)map->values + new_value_offset,
                   (char *)old_values + old_value_offset, map->value_size);
            map->hashes[new_idx] = old_hashes[i];
        }
    }

    dsc_free(old_keys);
    dsc_free(old_values);
    dsc_free(old_hashes);
    return DSC_ERROR_OK;
}

DSCUnorderedMap *unordered_map_create(size_t key_size, size_t value_size,
                                        size_t (*hash_fn)(void const *),
                                        int (*compare_fn)(void const *,
                                                          void const *)) {
    // Input validation
    if (key_size == 0 || value_size == 0 || !hash_fn || !compare_fn) {
        return NULL;
    }

    // Check for potential overflow in initial allocation
    size_t keys_size, values_size, hashes_size;
    if (!dsc_safe_multiply(DSC_UNORDERED_MAP_INITIAL_CAPACITY, key_size, &keys_size) ||
        !dsc_safe_multiply(DSC_UNORDERED_MAP_INITIAL_CAPACITY, value_size, &values_size) ||
        !dsc_safe_multiply(DSC_UNORDERED_MAP_INITIAL_CAPACITY, sizeof(size_t), &hashes_size)) {
        return NULL;  // Overflow would occur
    }

    DSCUnorderedMap *map = dsc_malloc(sizeof(DSCUnorderedMap));
    if (!map) return NULL;

    map->capacity = DSC_UNORDERED_MAP_INITIAL_CAPACITY;
    map->size = 0;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_fn = hash_fn;
    map->compare_fn = compare_fn;

    map->keys = dsc_malloc(keys_size);
    map->values = dsc_malloc(values_size);
    map->hashes = dsc_malloc(hashes_size);

    if (!map->keys || !map->values || !map->hashes) {
        dsc_free(map->keys);
        dsc_free(map->values);
        dsc_free(map->hashes);
        dsc_free(map);
        return NULL;
    }

    // Initialize memory to zero
    memset(map->keys, 0, keys_size);
    memset(map->values, 0, values_size);
    memset(map->hashes, 0, hashes_size);

    return map;
}

void unordered_map_destroy(DSCUnorderedMap *map) {
    if (!map) return;
    dsc_free(map->keys);
    dsc_free(map->values);
    dsc_free(map->hashes);
    dsc_free(map);
}

size_t unordered_map_size(DSCUnorderedMap const *map) {
    return map ? map->size : 0;
}

bool unordered_map_empty(DSCUnorderedMap const *map) {
    return !map || map->size == 0;
}

DSCError unordered_map_insert(DSCUnorderedMap *map, void const *key,
                               void const *value) {
    if (!map || !key || !value) return DSC_ERROR_INVALID_ARGUMENT;

    if ((float)map->size / map->capacity >= LOAD_FACTOR) {
        DSCError err = rehash(map);
        if (err != DSC_ERROR_OK) return err;
    }

    size_t hash = map->hash_fn(key);
    size_t idx = find_slot(map, key, hash);

    if (map->hashes[idx] == 0) {
        ++(map->size);
    }

    size_t key_offset, value_offset;
    if (!dsc_safe_multiply(idx, map->key_size, &key_offset) ||
        !dsc_safe_multiply(idx, map->value_size, &value_offset)) {
        return DSC_ERROR_OVERFLOW;
    }

    memcpy((char *)map->keys + key_offset, key, map->key_size);
    memcpy((char *)map->values + value_offset, value, map->value_size);
    map->hashes[idx] = hash;

    return DSC_ERROR_OK;
}

void *unordered_map_find(DSCUnorderedMap *map, void const *key) {
    if (!map || !key) return NULL;

    size_t hash = map->hash_fn(key);
    size_t idx = find_slot(map, key, hash);

    if (map->hashes[idx] == 0) return NULL;

    size_t value_offset;
    if (!dsc_safe_multiply(idx, map->value_size, &value_offset)) {
        return NULL;  // Overflow error
    }

    return (char *)map->values + value_offset;
}

DSCError unordered_map_erase(DSCUnorderedMap *map, void const *key) {
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
        size_t next_key_offset;
        if (!dsc_safe_multiply(next, map->key_size, &next_key_offset)) {
            return DSC_ERROR_OVERFLOW;
        }

        size_t new_idx =
            find_slot(map, (char *)map->keys + next_key_offset, existing_hash);

        if (new_idx != next) {
            size_t new_key_offset, next_value_offset, new_value_offset;
            if (!dsc_safe_multiply(new_idx, map->key_size, &new_key_offset) ||
                !dsc_safe_multiply(next, map->value_size, &next_value_offset) ||
                !dsc_safe_multiply(new_idx, map->value_size,
                                   &new_value_offset)) {
                return DSC_ERROR_OVERFLOW;
            }

            memcpy((char *)map->keys + new_key_offset,
                   (char *)map->keys + next_key_offset, map->key_size);
            memcpy((char *)map->values + new_value_offset,
                   (char *)map->values + next_value_offset, map->value_size);
            map->hashes[new_idx] = existing_hash;
            map->hashes[next] = 0;
        }

        next = (next + 1) & mask;
    }

    return DSC_ERROR_OK;
}

void unordered_map_clear(DSCUnorderedMap *map) {
    if (!map) return;

    size_t hashes_size;
    if (dsc_safe_multiply(map->capacity, sizeof(size_t), &hashes_size)) {
        memset(map->hashes, 0, hashes_size);
    }
    map->size = 0;
}

DSCError unordered_map_reserve(DSCUnorderedMap *map, size_t n) {
    if (!map) return DSC_ERROR_INVALID_ARGUMENT;

    if (n <= map->capacity) return DSC_ERROR_OK;

    size_t old_capacity = map->capacity;
    map->capacity = n;

    size_t keys_size, values_size, hashes_size;
    if (!dsc_safe_multiply(map->capacity, map->key_size, &keys_size) ||
        !dsc_safe_multiply(map->capacity, map->value_size, &values_size) ||
        !dsc_safe_multiply(map->capacity, sizeof(size_t), &hashes_size)) {
        map->capacity = old_capacity;
        return DSC_ERROR_OVERFLOW;
    }

    void *new_keys = dsc_malloc(keys_size);
    void *new_values = dsc_malloc(values_size);
    size_t *new_hashes = dsc_malloc(hashes_size);

    if (!new_keys || !new_values || !new_hashes) {
        dsc_free(new_keys);
        dsc_free(new_values);
        dsc_free(new_hashes);
        map->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    // Initialize memory to zero
    memset(new_keys, 0, keys_size);
    memset(new_values, 0, values_size);
    memset(new_hashes, 0, hashes_size);

    for (size_t i = 0; i < old_capacity; ++i) {
        if (map->hashes[i] != 0) {
            size_t old_key_offset, old_value_offset;
            if (!dsc_safe_multiply(i, map->key_size, &old_key_offset) ||
                !dsc_safe_multiply(i, map->value_size, &old_value_offset)) {
                dsc_free(new_keys);
                dsc_free(new_values);
                dsc_free(new_hashes);
                map->capacity = old_capacity;
                return DSC_ERROR_OVERFLOW;
            }

            size_t new_idx = find_slot(map, (char *)map->keys + old_key_offset,
                                       map->hashes[i]);

            size_t new_key_offset, new_value_offset;
            if (!dsc_safe_multiply(new_idx, map->key_size, &new_key_offset) ||
                !dsc_safe_multiply(new_idx, map->value_size,
                                   &new_value_offset)) {
                dsc_free(new_keys);
                dsc_free(new_values);
                dsc_free(new_hashes);
                map->capacity = old_capacity;
                return DSC_ERROR_OVERFLOW;
            }

            memcpy((char *)new_keys + new_key_offset,
                   (char *)map->keys + old_key_offset, map->key_size);
            memcpy((char *)new_values + new_value_offset,
                   (char *)map->values + old_value_offset, map->value_size);
            new_hashes[new_idx] = map->hashes[i];
        }
    }

    dsc_free(map->keys);
    dsc_free(map->values);
    dsc_free(map->hashes);

    map->keys = new_keys;
    map->values = new_values;
    map->hashes = new_hashes;

    return DSC_ERROR_OK;
}
