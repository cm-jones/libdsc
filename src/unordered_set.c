// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/unordered_set.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75f

static size_t find_slot(dsc_unordered_set const *set, void const *element,
                        size_t hash) {
    size_t mask = set->capacity - 1;
    size_t idx = hash & mask;

    while (set->hashes[idx] != 0) {
        if (set->hashes[idx] == hash &&
            set->compare_fn((char *)set->elements + idx * set->element_size,
                            element) == 0) {
            return idx;
        }
        idx = (idx + 1) & mask;
    }
    return idx;
}

static dsc_error rehash(dsc_unordered_set *set) {
    size_t old_capacity = set->capacity;
    void *old_elements = set->elements;
    size_t *old_hashes = set->hashes;

    set->capacity *= 2;
    set->elements = calloc(set->capacity, set->element_size);
    set->hashes = calloc(set->capacity, sizeof(size_t));

    if (!set->elements || !set->hashes) {
        free(set->elements);
        free(set->hashes);
        set->elements = old_elements;
        set->hashes = old_hashes;
        set->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_hashes[i] != 0) {
            size_t new_idx =
                find_slot(set, (char *)old_elements + i * set->element_size,
                          old_hashes[i]);

            memcpy((char *)set->elements + new_idx * set->element_size,
                   (char *)old_elements + i * set->element_size,
                   set->element_size);
            set->hashes[new_idx] = old_hashes[i];
        }
    }

    free(old_elements);
    free(old_hashes);
    return DSC_SUCCESS;
}

dsc_unordered_set *unordered_set_create(size_t element_size,
                                          size_t (*hash_fn)(void const *),
                                          int (*compare_fn)(void const *,
                                                            void const *)) {
    dsc_unordered_set *set = malloc(sizeof(dsc_unordered_set));
    if (!set) return NULL;

    set->capacity = INITIAL_CAPACITY;
    set->size = 0;
    set->element_size = element_size;
    set->hash_fn = hash_fn;
    set->compare_fn = compare_fn;

    set->elements = calloc(set->capacity, element_size);
    set->hashes = calloc(set->capacity, sizeof(size_t));

    if (!set->elements || !set->hashes) {
        free(set->elements);
        free(set->hashes);
        free(set);
        return NULL;
    }

    return set;
}

void unordered_set_destroy(dsc_unordered_set *set) {
    if (!set) return;
    free(set->elements);
    free(set->hashes);
    free(set);
}

size_t unordered_set_size(dsc_unordered_set const *set) {
    return set ? set->size : 0;
}

bool unordered_set_empty(dsc_unordered_set const *set) {
    return !set || set->size == 0;
}

dsc_error unordered_set_insert(dsc_unordered_set *set,
                                 void const *element) {
    if (!set || !element) return DSC_ERROR_INVALID_ARGUMENT;

    if ((float)set->size / set->capacity >= LOAD_FACTOR) {
        dsc_error err = rehash(set);
        if (err != DSC_SUCCESS) return err;
    }

    size_t hash = set->hash_fn(element);
    size_t idx = find_slot(set, element, hash);

    if (set->hashes[idx] == 0) {
        ++(set->size);
    }

    memcpy((char *)set->elements + idx * set->element_size, element,
           set->element_size);
    set->hashes[idx] = hash;

    return DSC_SUCCESS;
}

void *unordered_set_find(dsc_unordered_set *set, void const *element) {
    if (!set || !element) return NULL;

    size_t hash = set->hash_fn(element);
    size_t idx = find_slot(set, element, hash);

    if (set->hashes[idx] == 0) return NULL;

    return (char *)set->elements + idx * set->element_size;
}

dsc_error unordered_set_erase(dsc_unordered_set *set, void const *element) {
    if (!set || !element) return DSC_ERROR_INVALID_ARGUMENT;

    size_t hash = set->hash_fn(element);
    size_t idx = find_slot(set, element, hash);

    if (set->hashes[idx] == 0) return DSC_ERROR_NOT_FOUND;

    set->hashes[idx] = 0;
    set->size--;

    // Rehash remaining elements
    size_t mask = set->capacity - 1;
    size_t next = (idx + 1) & mask;

    while (set->hashes[next] != 0) {
        size_t existing_hash = set->hashes[next];
        size_t new_idx =
            find_slot(set, (char *)set->elements + next * set->element_size,
                      existing_hash);

        if (new_idx != next) {
            memcpy((char *)set->elements + new_idx * set->element_size,
                   (char *)set->elements + next * set->element_size,
                   set->element_size);
            set->hashes[new_idx] = existing_hash;
            set->hashes[next] = 0;
        }

        next = (next + 1) & mask;
    }

    return DSC_SUCCESS;
}

void unordered_set_clear(dsc_unordered_set *set) {
    if (!set) return;

    memset(set->hashes, 0, set->capacity * sizeof(size_t));
    set->size = 0;
}

dsc_error unordered_set_reserve(dsc_unordered_set *set, size_t n) {
    if (!set) return DSC_ERROR_INVALID_ARGUMENT;

    if (n <= set->capacity) return DSC_SUCCESS;

    size_t old_capacity = set->capacity;
    set->capacity = n;

    void *new_elements = calloc(set->capacity, set->element_size);
    size_t *new_hashes = calloc(set->capacity, sizeof(size_t));

    if (!new_elements || !new_hashes) {
        free(new_elements);
        free(new_hashes);
        set->capacity = old_capacity;
        return DSC_ERROR_MEMORY;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (set->hashes[i] != 0) {
            size_t new_idx =
                find_slot(set, (char *)set->elements + i * set->element_size,
                          set->hashes[i]);

            memcpy((char *)new_elements + new_idx * set->element_size,
                   (char *)set->elements + i * set->element_size,
                   set->element_size);
            new_hashes[new_idx] = set->hashes[i];
        }
    }

    free(set->elements);
    free(set->hashes);

    set->elements = new_elements;
    set->hashes = new_hashes;

    return DSC_SUCCESS;
}
