// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_COMMON_H_
#define DSC_COMMON_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum dsc_error
 * @brief Error codes for libdsc
 */
typedef enum {
    DSC_ERROR_OK = 0,
    DSC_ERROR_MEMORY,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_EMPTY,
    DSC_ERROR_NOT_FOUND,
    DSC_ERROR_DUPLICATE,
    DSC_ERROR_OVERFLOW,
} dsc_error;

// Memory allocation wrapper with error checking
static inline void *dsc_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        return NULL;
    }

    return ptr;
}

// Memory reallocation wrapper with error checking
static inline void *dsc_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        return NULL;
    }

    return new_ptr;
}

// Safe free wrapper
static inline void dsc_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

// Default hash function for integers
static inline size_t dsc_hash_int(void const *key) {
    return (size_t)*(int const *)key;
}

// Default hash function for strings
static inline size_t dsc_hash_string(void const *key) {
    char const *str = *(char const **)key;
    size_t hash = 5381;
    int c;

    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// Default comparison function for integers
static inline int dsc_compare_int(void const *a, void const *b) {
    return *(int const *)a - *(int const *)b;
}

// Default comparison function for strings
static inline int dsc_compare_string(void const *a, void const *b) {
    return strcmp(*(char const **)a, *(char const **)b);
}

static inline bool dsc_safe_memcpy(void *dest, const void *src,
                                   size_t dest_size, size_t src_size) {
    if (!dest || !src || dest_size < src_size) {
        return false;
    }

    memcpy(dest, src, src_size);
    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // DSC_COMMON_H_
