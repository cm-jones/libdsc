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

#ifndef DSC_STACK_H
#define DSC_STACK_H

#include "dsc_data.h"
#include "dsc_error.h"
#include "dsc_type.h"

#define DSC_STACK_INITIAL_CAPACITY 16

typedef struct DSCStack DSCStack;

struct DSCStack {
    DSCData data;     // The data stored in the stack
    size_t size;      // The number of elements currently in the stack
    size_t capacity;  // The current capacity of the stack
    DSCType type;     // The type of the elements in the stack
};

/**
 * @brief Initialize a new stack.
 *
 * @param type The data type stored in the stack.
 * @return A pointer to the new stack, or NULL on failure.
 */
DSCStack *dsc_stack_init(DSCType type);

/**
 * @brief Deinitialize a stack, freeing all allocated memory.
 *
 * @param stack Pointer to the stack to deinitialize.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_deinit(DSCStack *stack);

/**
 * @brief Get the current size of the stack.
 *
 * @param stack Pointer to the stack.
 * @param result Pointer to store the size.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_size(const DSCStack *stack, size_t *result);

/**
 * @brief Get the current capacity of the stack.
 *
 * @param stack Pointer to the stack.
 * @param result Pointer to store the capacity.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_capacity(const DSCStack *stack, size_t *result);

/**
 * @brief Check if the stack is empty.
 *
 * @param stack Pointer to the stack.
 * @param result Pointer to store the boolean result.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_empty(const DSCStack *stack, bool *result);

/**
 * @brief Get the element at the top of the stack.
 *
 * @param stack Pointer to the stack.
 * @param result Pointer to store the element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_top(const DSCStack *stack, void *result);

/**
 * @brief Push an element onto the stack.
 *
 * @param stack Pointer to the stack.
 * @param value Pointer to the element data to push.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_push(DSCStack *stack, void *value);

/**
 * @brief Pop an element from the stack.
 *
 * @param stack Pointer to the stack.
 * @param result Pointer to store the popped element data.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_pop(DSCStack *stack, void *result);

#endif  // DSC_STACK_H
