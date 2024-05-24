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
#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_STACK_INITIAL_CAPACITY 16

typedef struct DSCStack DSCStack;

/**
 * @brief Initialize a new stack.
 *
 * @param new_stack Pointer to the stack to initialize.
 * @param type The data type stored in the stack.
 * @return DSCError code indicating success or failure.
 */
DSCError dsc_stack_init(DSCStack *new_stack, DSCType type);

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

#endif // DSC_STACK_H
