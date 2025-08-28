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

/// @brief Error codes for libdsc
///
/// Enumeration of possible error codes returned by libdsc functions.
/// All functions that can fail return one of these error codes.
typedef enum {
    DSC_ERROR_OK = 0,
    DSC_ERROR_MEMORY,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_EMPTY,
    DSC_ERROR_NOT_FOUND,
    DSC_ERROR_DUPLICATE,
    DSC_ERROR_OVERFLOW,
} DSCError;

/// @brief Memory allocation wrapper with error checking
///
/// Allocates memory using malloc() with additional error handling.
/// Returns NULL if allocation fails.
///
/// @param size Number of bytes to allocate
/// @return Pointer to allocated memory, or NULL on failure
static inline void *dsc_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        return NULL;
    }

    return ptr;
}

/// @brief Memory reallocation wrapper with error checking
///
/// Reallocates memory using realloc() with additional error handling.
/// Returns NULL if reallocation fails.
///
/// @param ptr Pointer to previously allocated memory
/// @param size New size in bytes
/// @return Pointer to reallocated memory, or NULL on failure
static inline void *dsc_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        return NULL;
    }

    return new_ptr;
}

/// @brief Safe free() wrapper
///
/// Frees memory pointed to by ptr, but only if ptr is not NULL.
/// This prevents crashes from calling free() on NULL pointers.
///
/// @param ptr Pointer to memory to free (can be NULL)
static inline void dsc_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

/// @brief Default hash function for integers
///
/// Computes a hash value for an integer key. The key should point
/// to an int value.
///
/// @param key Pointer to an int value
/// @return Hash value for the integer
static inline size_t dsc_hash_int(void const *key) {
    return (size_t)*(int const *)key;
}

/// @brief Default hash function for strings
///
/// Computes a hash value for a string using the djb2 algorithm.
/// The key should point to a char* value.
///
/// @param key Pointer to a char* value (string)
/// @return Hash value for the string
static inline size_t dsc_hash_string(void const *key) {
    char const *str = *(char const **)key;
    size_t hash = 5381;
    int c;

    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/// @brief Default comparison function for integers
///
/// Compares two integer values. Both parameters should point to int values.
///
/// @param a Pointer to first int value
/// @param b Pointer to second int value
/// @return Negative if a < b, 0 if a == b, positive if a > b
static inline int dsc_compare_int(void const *a, void const *b) {
    return *(int const *)a - *(int const *)b;
}

/// @brief Default comparison function for strings
///
/// Compares two string values using strcmp(). Both parameters should
/// point to char* values.
///
/// @param a Pointer to first char* value
/// @param b Pointer to second char* value
/// @return Negative if a < b, 0 if a == b, positive if a > b
static inline int dsc_compare_string(void const *a, void const *b) {
    return strcmp(*(char const **)a, *(char const **)b);
}

/// @brief Safe memory copy with bounds checking
///
/// Copies memory from src to dest with bounds checking to prevent
/// buffer overflows. Only copies if dest_size >= src_size.
///
/// @param dest Destination buffer
/// @param src Source buffer
/// @param dest_size Size of destination buffer
/// @param src_size Number of bytes to copy
/// @return true on success, false if parameters are invalid or buffer too small
static inline bool dsc_safe_memcpy(void *dest, void const *src,
                                   size_t dest_size, size_t src_size) {
    if (!dest || !src || dest_size < src_size) {
        return false;
    }

    memcpy(dest, src, src_size);
    return true;
}

/// @brief Overflow-safe multiplication
///
/// Multiplies two size_t values while checking for overflow.
/// If overflow would occur, returns false and does not modify result.
///
/// @param a First operand
/// @param b Second operand
/// @param result Pointer to store the result
/// @return true if multiplication succeeded, false if overflow would occur
static inline bool dsc_safe_multiply(size_t a, size_t b, size_t *result) {
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }

    if (a > SIZE_MAX / b) {
        return false;  // Overflow would occur
    }

    *result = a * b;
    return true;
}

/// @brief Overflow-safe addition
///
/// Adds two size_t values while checking for overflow.
/// If overflow would occur, returns false and does not modify result.
///
/// @param a First operand
/// @param b Second operand
/// @param result Pointer to store the result
/// @return true if addition succeeded, false if overflow would occur
static inline bool dsc_safe_add(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return false;  // Overflow would occur
    }

    *result = a + b;
    return true;
}

/// @brief Safe capacity growth function
///
/// Computes a new capacity by doubling the current capacity, with
/// overflow checking. Used by dynamic data structures to grow their
/// internal buffers.
///
/// @param current_capacity Current capacity
/// @param new_capacity Pointer to store the new capacity
/// @return true if growth succeeded, false if already at maximum capacity
static inline bool dsc_safe_grow_capacity(size_t current_capacity,
                                          size_t *new_capacity) {
    // Check if doubling would overflow
    if (current_capacity > SIZE_MAX / 2) {
        // Try to grow to maximum possible size
        if (current_capacity == SIZE_MAX) {
            return false;  // Already at maximum
        }
        *new_capacity = SIZE_MAX;
        return true;
    }

    *new_capacity = current_capacity * 2;
    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // DSC_COMMON_H_
