#include "libdsc/stack.h"

#include <stdio.h>

int main() {
    // Create a stack of integers
    dsc_stack_t* stack = stack_create(sizeof(int));
    if (!stack) {
        printf("Failed to create stack\n");
        return 1;
    }
    
    // Push some values
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        if (stack_push(stack, &values[i]) != DSC_SUCCESS) {
            printf("Failed to push %d\n", values[i]);
            continue;
        }
        printf("Pushed %d\n", values[i]);
    }
    
    // Print stack size
    printf("\nStack size: %zu\n", stack_size(stack));
    
    // Print top element
    int* top = (int*)dsc_stack_top(stack);
    if (top) {
        printf("Top element: %d\n", *top);
    }
    
    // Pop and print all values
    printf("\nPopping values:\n");
    while (!stack_empty(stack)) {
        top = (int*)dsc_stack_top(stack);
        if (top) {
            printf("Popping %d\n", *top);
        }
        stack_pop(stack);
    }
    
    // Try to pop from empty stack
    printf("\nTrying to pop from empty stack: ");
    if (stack_pop(stack) == DSC_ERROR_EMPTY) {
        printf("Stack is empty (expected)\n");
    }
    
    // Push more values
    printf("\nPushing more values:\n");
    for (int i = 6; i <= 10; ++i) {
        if (stack_push(stack, &i) == DSC_SUCCESS) {
            printf("Pushed %d\n", i);
        }
    }
    
    // Reserve space
    printf("\nReserving space for 100 elements: ");
    if (stack_reserve(stack, 100) == DSC_SUCCESS) {
        printf("Success\n");
    }
    
    // Clear stack
    printf("\nClearing stack\n");
    stack_clear(stack);
    printf("Stack size after clear: %zu\n", stack_size(stack));
    
    // Clean up
    stack_destroy(stack);
    return 0;
}
