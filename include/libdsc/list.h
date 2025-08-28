// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_LIST_H_
#define DSC_LIST_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Node structure for doubly-linked list
///
/// Each node contains data and pointers to the previous and next nodes.
/// This structure should be treated as opaque.
typedef struct list_node {
    void *data;             ///< Pointer to the stored data
    struct list_node *prev; ///< Pointer to the previous node
    struct list_node *next; ///< Pointer to the next node
} DSCListNode;

/// @brief Doubly-linked list structure
///
/// A doubly-linked list that provides efficient insertion and deletion
/// at both ends. This structure should be treated as opaque.
typedef struct {
    DSCListNode *head;   ///< Pointer to the first node
    DSCListNode *tail;   ///< Pointer to the last node
    size_t size;         ///< Number of elements in the list
    size_t element_size; ///< Size of each element in bytes
} DSCList;

/// @brief Creates a new doubly-linked list
///
/// Allocates and initializes a new doubly-linked list that can store
/// elements of the specified size.
///
/// @param element_size Size of each element in bytes (must be > 0)
/// @return Pointer to the newly created list, or NULL on failure
/// @note The caller is responsible for calling list_destroy()
DSCList *list_create(size_t element_size);

/// @brief Destroys the list and frees its memory
///
/// Deallocates all memory associated with the list, including
/// all nodes and the list structure itself.
///
/// @param list Pointer to the list to destroy (can be NULL)
/// @note This function is safe to call with a NULL pointer
void list_destroy(DSCList *list);

/// @brief Returns the number of elements in the list
///
/// @param list Pointer to the list (can be NULL)
/// @return Number of elements currently stored in the list, or 0 if list is NULL
/// @note This operation is O(1)
size_t list_size(DSCList const *list);

/// @brief Checks if the list is empty
///
/// @param list Pointer to the list (can be NULL)
/// @return true if the list is empty or NULL, false otherwise
/// @note This operation is O(1)
bool list_empty(DSCList const *list);

/// @brief Inserts an element at the front of the list
///
/// Adds a copy of the given element to the front of the list.
///
/// @param list Pointer to the list (must not be NULL)
/// @param element Pointer to the element to add (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully added element
/// @retval DSC_ERROR_INVALID_ARGUMENT list or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This operation is O(1)
DSCError list_push_front(DSCList *list, void const *element);

/// @brief Inserts an element at the back of the list
///
/// Adds a copy of the given element to the back of the list.
///
/// @param list Pointer to the list (must not be NULL)
/// @param element Pointer to the element to add (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully added element
/// @retval DSC_ERROR_INVALID_ARGUMENT list or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This operation is O(1)
DSCError list_push_back(DSCList *list, void const *element);

/// @brief Removes the first element from the list
///
/// @param list Pointer to the list (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT list is NULL
/// @retval DSC_ERROR_EMPTY List is empty
/// @note This operation is O(1)
DSCError list_pop_front(DSCList *list);

/// @brief Removes the last element from the list
///
/// @param list Pointer to the list (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT list is NULL
/// @retval DSC_ERROR_EMPTY List is empty
/// @note This operation is O(1)
DSCError list_pop_back(DSCList *list);

/// @brief Returns a pointer to the first element
///
/// @param list Pointer to the list (must not be NULL)
/// @return Pointer to the first element, or NULL if list is empty or NULL
/// @note This operation is O(1)
void *list_front(DSCList const *list);

/// @brief Returns a pointer to the last element
///
/// @param list Pointer to the list (must not be NULL)
/// @return Pointer to the last element, or NULL if list is empty or NULL
/// @note This operation is O(1)
void *list_back(DSCList const *list);

/// @brief Inserts an element before the specified position
///
/// Inserts a copy of the element before the given node position.
///
/// @param list Pointer to the list (must not be NULL)
/// @param pos Node before which to insert (must not be NULL)
/// @param element Pointer to the element to insert (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully inserted element
/// @retval DSC_ERROR_INVALID_ARGUMENT list, pos, or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This operation is O(1)
DSCError list_insert(DSCList *list, DSCListNode *pos, void const *element);

/// @brief Removes the element at the specified position
///
/// Removes the node at the given position.
///
/// @param list Pointer to the list (must not be NULL)
/// @param pos Node to remove (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT list or pos is NULL
/// @note This operation is O(1)
DSCError list_erase(DSCList *list, DSCListNode *pos);

/// @brief Removes all elements from the list
///
/// Removes all elements from the list, making it empty.
///
/// @param list Pointer to the list (can be NULL)
/// @note This function is safe to call with a NULL pointer
/// @note This operation is O(n) where n is the number of elements
void list_clear(DSCList *list);

/// @brief Returns the first node of the list
///
/// Returns a pointer to the first node for forward iteration.
///
/// @param list Pointer to the list (can be NULL)
/// @return Pointer to the first node, or NULL if list is empty or NULL
/// @note Use this with list_end() for forward iteration
DSCListNode *list_begin(DSCList const *list);

/// @brief Returns the end marker of the list
///
/// Returns NULL to indicate the end of the list for forward iteration.
///
/// @param list Pointer to the list (can be NULL)
/// @return Always returns NULL
/// @note Use this with list_begin() for forward iteration
DSCListNode *list_end(DSCList const *list);

/// @brief Returns the last node of the list
///
/// Returns a pointer to the last node for reverse iteration.
///
/// @param list Pointer to the list (can be NULL)
/// @return Pointer to the last node, or NULL if list is empty or NULL
/// @note Use this with list_rend() for reverse iteration
DSCListNode *list_rbegin(DSCList const *list);

/// @brief Returns the reverse end marker of the list
///
/// Returns NULL to indicate the end of the list for reverse iteration.
///
/// @param list Pointer to the list (can be NULL)
/// @return Always returns NULL
/// @note Use this with list_rbegin() for reverse iteration
DSCListNode *list_rend(DSCList const *list);

#ifdef __cplusplus
}
#endif

#endif  // DSC_LIST_H_
