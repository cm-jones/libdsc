// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_QUEUE_H
#define DSC_QUEUE_H

#include "dsc_data.h"
#include "dsc_type.h" 
#include "dsc_error.h"
#include "dsc_utils.h"

#define DSC_QUEUE_INITIAL_CAPACITY 16

typedef struct DSCQueue DSCQueue;

/**
 * @brief Initialize a new queue.
 *
 * @param new_queue Pointer to the queue to initialize.
 * @param type The data type stored in the queue.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_init(DSCQueue *new_queue, DSCType type);

/**
 * @brief Deinitialize a queue, freeing all allocated memory.
 *
 * @param queue Pointer to the queue to deinitialize.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_deinit(DSCQueue *queue);

/**
 * @brief Get the current size of the queue.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the size.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_size(const DSCQueue *queue, size_t *result);

/**
 * @brief Get the current capacity of the queue.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the capacity.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_capacity(const DSCQueue *queue, size_t *result);

/**
 * @brief Check if the queue is empty.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the boolean result. 
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_empty(const DSCQueue *queue, bool *result);

/**
 * @brief Get the element at the front of the queue.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_front(const DSCQueue *queue, void *result);

/**
 * @brief Get the element at the back of the queue.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_back(const DSCQueue *queue, void *result);

/**
 * @brief Push an element onto the back of the queue.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the element data to push. 
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_push(DSCQueue *queue, void *data);

/**
 * @brief Pop an element from the front of the queue.
 *
 * @param queue Pointer to the queue.
 * @param result Pointer to store the popped element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_queue_pop(DSCQueue *queue, void *result);

#endif // DSC_QUEUE_H
