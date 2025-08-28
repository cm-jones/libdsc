// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_FORWARD_LIST_H_
#define DSC_FORWARD_LIST_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Node structure for forward list
///
/// Each node contains data and a pointer to the next node.
/// This structure should be treated as opaque.
typedef struct forward_list_node {
    void *data;                      ///< Pointer to the stored data
    struct forward_list_node *next;  ///< Pointer to the next node
} DSCForwardListNode;

/// @brief Forward list structure
///
/// A singly-linked list that provides efficient insertion and deletion
/// at the front. This structure should be treated as opaque.
typedef struct {
    DSCForwardListNode *head; ///< Pointer to the first node
    size_t size;              ///< Number of elements in the list
    size_t element_size;      ///< Size of each element in bytes
} DSCForwardList;

/// @brief Creates a new forward list
///
/// Allocates and initializes a new forward list that can store elements
/// of the specified size.
///
/// @param element_size Size of each element in bytes (must be > 0)
/// @return Pointer to the newly created forward list, or NULL on failure
/// @note The caller is responsible for calling forward_list_destroy()
DSCForwardList *forward_list_create(size_t element_size);

/// @brief Destroys the forward list and frees its memory
///
/// Deallocates all memory associated with the forward list, including
/// all nodes and the list structure itself.
///
/// @param list Pointer to the forward list to destroy (can be NULL)
/// @note This function is safe to call with a NULL pointer
void forward_list_destroy(DSCForwardList *list);

/// @brief Returns the number of elements in the forward list
///
/// @param list Pointer to the forward list (can be NULL)
/// @return Number of elements currently stored in the list, or 0 if list is NULL
/// @note This operation is O(1)
size_t forward_list_size(DSCForwardList const *list);

/// @brief Checks if the forward list is empty
///
/// @param list Pointer to the forward list (can be NULL)
/// @return true if the list is empty or NULL, false otherwise
/// @note This operation is O(1)
bool forward_list_empty(DSCForwardList const *list);

/// @brief Inserts an element at the front of the forward list
///
/// Adds a copy of the given element to the front of the list.
///
/// @param list Pointer to the forward list (must not be NULL)
/// @param element Pointer to the element to add (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully added element
/// @retval DSC_ERROR_INVALID_ARGUMENT list or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This operation is O(1)
DSCError forward_list_push_front(DSCForwardList *list, void const *element);

/// @brief Removes the first element from the forward list
///
/// @param list Pointer to the forward list (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT list is NULL
/// @retval DSC_ERROR_EMPTY List is empty
/// @note This operation is O(1)
DSCError forward_list_pop_front(DSCForwardList *list);

/// @brief Returns a pointer to the first element
///
/// @param list Pointer to the forward list (must not be NULL)
/// @return Pointer to the first element, or NULL if list is empty or NULL
/// @note This operation is O(1)
void *forward_list_front(DSCForwardList const *list);

/// @brief Inserts an element after the specified position
///
/// Inserts a copy of the element after the given node position.
///
/// @param list Pointer to the forward list (must not be NULL)
/// @param pos Node after which to insert (must not be NULL)
/// @param element Pointer to the element to insert (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully inserted element
/// @retval DSC_ERROR_INVALID_ARGUMENT list, pos, or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This operation is O(1)
DSCError forward_list_insert_after(DSCForwardList *list,
                                    DSCForwardListNode *pos,
                                    void const *element);

/// @brief Removes the element after the specified position
///
/// Removes the node that comes after the given position.
///
/// @param list Pointer to the forward list (must not be NULL)
/// @param pos Node after which to remove (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT list or pos is NULL
/// @retval DSC_ERROR_NOT_FOUND No element after pos to remove
/// @note This operation is O(1)
DSCError forward_list_erase_after(DSCForwardList *list,
                                   DSCForwardListNode *pos);

/// @brief Removes all elements from the forward list
///
/// Removes all elements from the list, making it empty.
///
/// @param list Pointer to the forward list (can be NULL)
/// @note This function is safe to call with a NULL pointer
/// @note This operation is O(n) where n is the number of elements
void forward_list_clear(DSCForwardList *list);

/// @brief Returns the first node of the forward list
///
/// Returns a pointer to the first node for iteration purposes.
///
/// @param list Pointer to the forward list (can be NULL)
/// @return Pointer to the first node, or NULL if list is empty or NULL
/// @note Use this with forward_list_end() for iteration
DSCForwardListNode *forward_list_begin(DSCForwardList const *list);

/// @brief Returns the end marker of the forward list
///
/// Returns NULL to indicate the end of the list for iteration.
///
/// @param list Pointer to the forward list (can be NULL)
/// @return Always returns NULL
/// @note Use this with forward_list_begin() for iteration
DSCForwardListNode *forward_list_end(DSCForwardList const *list);

#ifdef __cplusplus
}
#endif

#endif  // DSC_FORWARD_LIST_H_
