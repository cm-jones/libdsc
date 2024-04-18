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

#ifndef __DSC_STACK_H__
#define __DSC_STACK_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * @def DSC_STACK_INITIAL_CAPACITY
 * @brief The initial capacity of the stack.
 */
#define DSC_STACK_INITIAL_CAPACITY 16

/* Forward declaration of the stack structure */
typedef struct dsc_stack_t dsc_stack_t;

/**
 * @brief Creates a new empty stack.
 *
 * @return A pointer to the newly created stack, or NULL if memory allocation fails.
 */
struct dsc_stack_t *dsc_stack_create();

/**
 * @brief Destroys the stack and frees its memory.
 *
 * @param stack The stack to destroy.
 */
void dsc_stack_free(struct dsc_stack_t *stack);

/**
 * @brief Pushes an element onto the top of the stack.
 *
 * @param stack The stack to push the element onto.
 * @param value The value to push.
 */
void dsc_stack_push(struct dsc_stack_t *stack, int value);

/**
 * @brief Removes the top element from the stack.
 *
 * @param stack The stack to pop from.
 */
void dsc_stack_pop(struct dsc_stack_t *stack);

/**
 * @brief Retrieves the value of the top element on the stack without removing it.
 *
 * @param stack The stack to get the top element from.
 *
 * @return The value of the top element.
 */
int dsc_stack_top(const struct dsc_stack_t *stack);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack The stack to check.
 *
 * @return true if the stack is empty, false otherwise.
 */
bool dsc_stack_empty(const struct dsc_stack_t *stack);

/**
 * @brief Gets the number of elements in the stack.
 *
 * @param stack The stack to get the size of.
 *
 * @return The number of elements in the stack.
 */
size_t dsc_stack_size(const struct dsc_stack_t *stack);

#endif /* __DSC_STACK_H__ */
