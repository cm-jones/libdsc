// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_STACK_H_
#define DSC_STACK_H_

#include "libdsc/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief LIFO stack structure
///
/// A generic LIFO stack that can store elements of any type.
/// The stack automatically manages memory allocation and provides
/// efficient push and pop operations.
///
/// @note This structure should be treated as opaque. Use the provided
///       functions to interact with the stack.
typedef struct {
    void *data;          ///< Pointer to the data buffer
    size_t size;         ///< Number of elements currently stored
    size_t capacity;     ///< Total capacity of the data buffer
    size_t element_size; ///< Size of each element in bytes
} DSCStack;

/// @brief Creates a new stack with the specified element size
///
/// Allocates and initializes a new stack that can store elements of the
/// specified size. The stack starts with an initial capacity and will
/// automatically grow as needed.
///
/// @param element_size Size of each element in bytes (must be > 0)
/// @return Pointer to the newly created stack, or NULL on failure
/// @note The caller is responsible for calling stack_destroy() to free
///       the allocated memory.
///
/// @example
/// ```c
/// // Create a stack of integers
/// dsc_stack *int_stack = stack_create(sizeof(int));
///
/// // Create a stack of custom structs
/// typedef struct { int x, y; } point_t;
/// dsc_stack *point_stack = stack_create(sizeof(point_t));
/// ```
///
/// @see stack_destroy()
DSCStack *stack_create(size_t element_size);

/// @brief Destroys the stack and frees its memory
///
/// Deallocates all memory associated with the stack, including the data
/// buffer and the stack structure itself. After calling this function,
/// the stack pointer becomes invalid and should not be used.
///
/// @param stack Pointer to the stack to destroy (can be NULL)
///
/// @note This function is safe to call with a NULL pointer.
/// @note This function does not call destructors for stored elements.
///       If elements require cleanup, iterate through the stack and
///       clean up each element before calling this function.
///
/// @see stack_create()
void stack_destroy(DSCStack *stack);

/// @brief Returns the number of elements in the stack
///
/// @param stack Pointer to the stack (can be NULL)
/// @return Number of elements currently stored in the stack, or 0 if stack is
/// NULL
///
/// @note This operation is O(1).
///
/// @example
/// ```c
/// dsc_stack *stack = stack_create(sizeof(int));
/// printf("Size: %zu\n", stack_size(stack)); // Output: Size: 0
/// ```
size_t stack_size(DSCStack const *stack);

/// @brief Checks if the stack is empty
///
/// @param stack Pointer to the stack (can be NULL)
/// @return true if the stack is empty or NULL, false otherwise
///
/// @note This operation is O(1).
/// @note Equivalent to `stack_size(stack) == 0`
bool stack_empty(DSCStack const *stack);

/// @brief Pushes an element onto the top of the stack
///
/// Adds a copy of the given element to the top of the stack.
/// The stack will automatically grow if necessary.
///
/// @param stack Pointer to the stack (must not be NULL)
/// @param element Pointer to the element to push (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully pushed element
/// @retval DSC_ERROR_INVALID_ARGUMENT stack or element is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed during growth
///
/// @note The element is copied into the stack
/// @note This operation is amortized O(1)
///
/// @example
/// ```c
/// int value = 42;
/// dsc_error err = stack_push(stack, &value);
/// if (err != DSC_ERROR_OK) {
///     // Handle error
/// }
/// ```
DSCError stack_push(DSCStack *stack, const void *element);

/// @brief Removes the top element from the stack
///
/// @param stack Pointer to the stack (must not be NULL)
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully removed element
/// @retval DSC_ERROR_INVALID_ARGUMENT stack is NULL
/// @retval DSC_ERROR_EMPTY Stack is empty
///
/// @note This operation is O(1)
/// @note The capacity is not reduced
/// @note Use stack_top() to access the element before popping
DSCError stack_pop(DSCStack *stack);

/// @brief Returns a pointer to the top element of the stack
///
/// @param stack Pointer to the stack (must not be NULL)
/// @return Pointer to the top element, or NULL if stack is empty or NULL
///
/// @note This operation is O(1)
/// @note The returned pointer may become invalid after operations that
///       modify the stack's capacity (push, reserve, etc.)
///
/// @example
/// ```c
/// int *top = (int*)stack_top(stack);
/// if (top) {
///     printf("Top element: %d\n", *top);
/// }
/// ```
void *stack_top(DSCStack const *stack);

/// @brief Removes all elements from the stack
///
/// Removes all elements from the stack, making it empty. The capacity
/// is not changed.
///
/// @param stack Pointer to the stack (can be NULL)
///
/// @note This operation is O(1)
/// @note This function is safe to call with a NULL pointer
/// @note To also reduce capacity, call stack_reserve() afterwards with size 0
void stack_clear(DSCStack *stack);

/// @brief Reserves space for at least the specified number of elements
///
/// Ensures that the stack can hold at least the specified number of elements
/// without requiring reallocation. If the requested capacity is less than or
/// equal to the current capacity, this function has no effect.
///
/// @param stack Pointer to the stack (must not be NULL)
/// @param capacity Minimum capacity to reserve
/// @return DSC_ERROR_OK on success, error code on failure
/// @retval DSC_ERROR_OK Successfully reserved space
/// @retval DSC_ERROR_INVALID_ARGUMENT stack is NULL
/// @retval DSC_ERROR_MEMORY Memory allocation failed
///
/// @note This function never reduces the capacity
/// @note Use this function to avoid multiple reallocations when the
///       final size is known in advance
DSCError stack_reserve(DSCStack *stack, size_t capacity);

#ifdef __cplusplus
}
#endif

#endif  // DSC_STACK_H_
