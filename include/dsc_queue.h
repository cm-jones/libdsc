/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_QUEUE_H__
#define __DSC_QUEUE_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * @def DSC_QUEUE_INITIAL_CAPACITY
 * @brief The initial capacity of the queue.
 */
#define DSC_QUEUE_INITIAL_CAPACITY 16

// Forward declaration of the queue structure
typedef struct DSCQueue *DSCQueue;

/**
 * @brief Creates a new empty queue.
 *
 * @return A pointer to the newly created queue, or NULL if memory allocation fails.
 */
DSCQueue dsc_queue_init(void);

/**
 * @brief Destroys the queue and frees its memory.
 *
 * @param queue The queue to destroy.
 * 
 * @return true if the queue was destroyed successfully, false otherwise.
 */
bool dsc_queue_deinit(DSCQueue queue);

/**
 * @brief Inserts an element at the end of the queue.
 *
 * @param queue The queue to push the element into.
 * @param value The value to push.
 * 
 * @return true if the element was inserted successfully, false otherwise.
 */
bool dsc_queue_push(DSCQueue queue, int value);

/**
 * @brief Removes the element at the front of the queue.
 *
 * @param queue The queue to pop from.
 * 
 * @return The popped value, or -1 if the queue is NULL.
 */
int dsc_queue_pop(DSCQueue queue);

/**
 * @brief Retrieves the value of the element at the front of the queue without removing it.
 *
 * @param queue The queue to get the front element from.
 *
 * @return The value of the front element, or -1 on failure.
 */
int dsc_queue_front(const DSCQueue queue);

/**
 * @brief Retrieves the value of the element at the back of the queue without removing it.
 *
 * @param queue The queue to get the back element from.
 *
 * @return The value of the back element, or -1 on failure.
 */
int dsc_queue_back(const DSCQueue queue);

/**
 * @brief Checks if the queue is empty.
 *
 * @param queue The queue to check.
 *
 * @return true if the queue is empty, false otherwise.
 */
bool dsc_queue_is_empty(const DSCQueue queue);

/**
 * @brief Gets the number of elements in the queue.
 *
 * @param queue The queue to get the size of.
 *
 * @return The number of elements in the queue, -1 if the queue is NULL.
 */
int dsc_queue_size(const DSCQueue queue);

#endif // __DSC_QUEUE_H__
