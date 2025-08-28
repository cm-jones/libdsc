// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UNORDERED_SET_H_
#define DSC_UNORDERED_SET_H_

#include <stdbool.h>
#include <stddef.h>

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Hash table-based unordered set structure
///
/// A hash table that stores unique elements with O(1) average time
/// complexity for insertions, lookups, and deletions. Uses open
/// addressing with linear probing for collision resolution.
///
/// @note This structure should be treated as opaque.
typedef struct {
    void *elements;                                ///< Array of elements
    size_t *hashes;                                ///< Array of hash values
    size_t size;                                   ///< Number of elements
    size_t capacity;                               ///< Total capacity
    size_t element_size;                           ///< Size of each element in bytes
    size_t (*hash_fn)(void const *);               ///< Hash function for elements
    int (*compare_fn)(void const *, void const *); ///< Comparison function for elements
} DSCUnorderedSet;

/// @brief Creates a new unordered set
///
/// Allocates and initializes a new unordered set that can store elements
/// of the specified size using the provided hash and comparison functions.
///
/// @param element_size Size of each element in bytes (must be > 0)
/// @param hash_fn Hash function for elements (must not be NULL)
/// @param compare_fn Comparison function for elements (must not be NULL)
/// @return Pointer to the newly created set, or NULL on failure
/// @note The caller is responsible for calling unordered_set_destroy()
DSCUnorderedSet *unordered_set_create(size_t element_size,
                                       size_t (*hash_fn)(void const *),
                                       int (*compare_fn)(void const *,
                                                         void const *));

/// @brief Destroys the unordered set and frees its memory
///
/// Deallocates all memory associated with the set, including the data
/// buffers and the set structure itself.
///
/// @param set Pointer to the set to destroy (can be NULL)
/// @note This function is safe to call with a NULL pointer
void unordered_set_destroy(DSCUnorderedSet *set);

/// @brief Returns the number of elements in the set
///
/// @param set Pointer to the set (can be NULL)
/// @return Number of elements currently stored, or 0 if set is NULL
/// @note This operation is O(1)
size_t unordered_set_size(DSCUnorderedSet const *set);

/// @brief Checks if the set is empty
///
/// @param set Pointer to the set (can be NULL)
/// @return true if the set is empty or NULL, false otherwise
/// @note This operation is O(1)
bool unordered_set_empty(DSCUnorderedSet const *set);

/// @brief Inserts an element into the set
///
/// Inserts the element into the set. If the element already exists,
/// no operation is performed.
///
/// @param set Pointer to the set (must not be NULL)
/// @param element Pointer to the element to insert (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully inserted element
/// @retval DSC_ERROR_INVALID_ARGUMENT set or element is NULL
/// @retval DSC_ERROR_DUPLICATE Element already exists in set
/// @retval DSC_ERROR_MEMORY Memory allocation failed during growth
/// @note Average time complexity is O(1)
DSCError unordered_set_insert(DSCUnorderedSet *set, void const *element);

/// @brief Finds an element in the set
///
/// Searches for the specified element in the set.
///
/// @param set Pointer to the set (must not be NULL)
/// @param element Pointer to the element to search for (must not be NULL)
/// @return Pointer to the element if found, NULL if not found or parameters are invalid
/// @note Average time complexity is O(1)
/// @note The returned pointer may become invalid after operations that
///       modify the set's capacity (insert, reserve, etc.)
void *unordered_set_find(DSCUnorderedSet *set, void const *element);

/// @brief Removes an element from the set
///
/// Removes the specified element from the set.
///
/// @param set Pointer to the set (must not be NULL)
/// @param element Pointer to the element to remove (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT set or element is NULL
/// @retval DSC_ERROR_NOT_FOUND Element not found in set
/// @note Average time complexity is O(1)
DSCError unordered_set_erase(DSCUnorderedSet *set, void const *element);

/// @brief Removes all elements from the set
///
/// Removes all elements from the set, making it empty. The capacity
/// is not changed.
///
/// @param set Pointer to the set (can be NULL)
/// @note This function is safe to call with a NULL pointer
/// @note This operation is O(1)
void unordered_set_clear(DSCUnorderedSet *set);

/// @brief Reserves space for at least n elements
///
/// Ensures that the set can hold at least n elements without
/// requiring reallocation. If n is less than or equal to the current
/// capacity, this function has no effect.
///
/// @param set Pointer to the set (must not be NULL)
/// @param n Minimum capacity to reserve
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully reserved space
/// @retval DSC_ERROR_INVALID_ARGUMENT set is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This function never reduces the capacity
DSCError unordered_set_reserve(DSCUnorderedSet *set, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_UNORDERED_SET_H_
