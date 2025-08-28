// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_QUEUE_H_
#define DSC_QUEUE_H_

#include <stdbool.h>
#include <stddef.h>

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief FIFO queue structure
///
/// A circular buffer-based FIFO queue that can store elements of any type.
/// The queue automatically manages memory allocation and provides efficient
/// enqueue and dequeue operations.
///
/// @note This structure should be treated as opaque.
typedef struct {
    void *elements;      ///< Pointer to the data buffer
    size_t front;        ///< Index of the front element
    size_t back;         ///< Index of the back element
    size_t size;         ///< Number of elements currently stored
    size_t capacity;     ///< Total capacity of the buffer
    size_t element_size; ///< Size of each element in bytes
} DSCQueue;

/// @brief Creates a new queue with the specified element size
///
/// Allocates and initializes a new queue that can store elements of the
/// specified size. The queue starts with an initial capacity and will
/// automatically grow as needed.
///
/// @param element_size Size of each element in bytes (must be > 0)
/// @return Pointer to the newly created queue, or NULL on failure
/// @note The caller is responsible for calling queue_destroy()
DSCQueue *queue_create(size_t element_size);

/// @brief Destroys the queue and frees its memory
///
/// Deallocates all memory associated with the queue, including the data
/// buffer and the queue structure itself. After calling this function,
/// the queue pointer becomes invalid and should not be used.
///
/// @param queue Pointer to the queue to destroy (can be NULL)
/// @note This function is safe to call with a NULL pointer
void queue_destroy(DSCQueue *queue);

/// @brief Returns the number of elements in the queue
///
/// @param queue Pointer to the queue (can be NULL)
/// @return Number of elements currently stored in the queue, or 0 if queue is NULL
/// @note This operation is O(1)
size_t queue_size(DSCQueue const *queue);

/// @brief Checks if the queue is empty
///
/// @param queue Pointer to the queue (can be NULL)
/// @return true if the queue is empty or NULL, false otherwise
/// @note This operation is O(1)
bool queue_empty(DSCQueue const *queue);

/// @brief Adds an element to the back of the queue
///
/// Enqueues a copy of the given element to the back of the queue.
/// The queue will automatically grow if necessary.
///
/// @param queue Pointer to the queue (must not be NULL)
/// @param element Pointer to the element to add (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully added element
/// @retval DSC_ERROR_INVALID_ARGUMENT queue or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed during growth
/// @note This operation is amortized O(1)
DSCError queue_push(DSCQueue *queue, void const *element);

/// @brief Removes an element from the front of the queue
///
/// Dequeues the element at the front of the queue.
///
/// @param queue Pointer to the queue (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT queue is NULL
/// @retval DSC_ERROR_EMPTY Queue is empty
/// @note This operation is O(1)
DSCError queue_pop(DSCQueue *queue);

/// @brief Returns a pointer to the front element
///
/// @param queue Pointer to the queue (must not be NULL)
/// @return Pointer to the front element, or NULL if queue is empty or NULL
/// @note This operation is O(1)
/// @note The returned pointer may become invalid after operations that
///       modify the queue's capacity (push, reserve, etc.)
void *queue_front(DSCQueue const *queue);

/// @brief Returns a pointer to the back element
///
/// @param queue Pointer to the queue (must not be NULL)
/// @return Pointer to the back element, or NULL if queue is empty or NULL
/// @note This operation is O(1)
/// @note The returned pointer may become invalid after operations that
///       modify the queue's capacity (push, reserve, etc.)
void *queue_back(DSCQueue const *queue);

/// @brief Removes all elements from the queue
///
/// Removes all elements from the queue, making it empty. The capacity
/// is not changed.
///
/// @param queue Pointer to the queue (can be NULL)
/// @note This function is safe to call with a NULL pointer
/// @note This operation is O(1)
void queue_clear(DSCQueue *queue);

/// @brief Reserves space for at least n elements
///
/// Ensures that the queue can hold at least n elements without
/// requiring reallocation. If n is less than or equal to the current
/// capacity, this function has no effect.
///
/// @param queue Pointer to the queue (must not be NULL)
/// @param n Minimum capacity to reserve
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully reserved space
/// @retval DSC_ERROR_INVALID_ARGUMENT queue is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
/// @note This function never reduces the capacity
DSCError queue_reserve(DSCQueue *queue, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // DSC_QUEUE_H_
