#include <libdsc/queue.h>
#include <stdio.h>

int main() {
    // Create a queue of integers
    dsc_queue_t* queue = queue_create(sizeof(int));
    if (!queue) {
        printf("Failed to create queue\n");
        return 1;
    }
    
    // Push some values
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i) {
        if (queue_push(queue, &values[i]) != DSC_SUCCESS) {
            printf("Failed to push %d\n", values[i]);
            continue;
        }
        printf("Pushed %d\n", values[i]);
    }
    
    // Print queue size
    printf("\nQueue size: %zu\n", queue_size(queue));
    
    // Print front and back
    int* front = (int*)queue_front(queue);
    int* back = (int*)queue_back(queue);
    if (front && back) {
        printf("Front: %d, Back: %d\n", *front, *back);
    }
    
    // Pop and print all values
    printf("\nPopping values:\n");
    while (!queue_empty(queue)) {
        front = (int*)queue_front(queue);
        if (front) {
            printf("Popping %d\n", *front);
        }
        queue_pop(queue);
    }
    
    // Try to pop from empty queue
    printf("\nTrying to pop from empty queue: ");
    if (queue_pop(queue) == DSC_ERROR_EMPTY) {
        printf("Queue is empty (expected)\n");
    }
    
    // Push more values
    printf("\nPushing more values:\n");
    for (int i = 6; i <= 10; ++i) {
        if (queue_push(queue, &i) == DSC_SUCCESS) {
            printf("Pushed %d\n", i);
        }
    }
    
    // Reserve space
    printf("\nReserving space for 100 elements: ");
    if (queue_reserve(queue, 100) == DSC_SUCCESS) {
        printf("Success\n");
    }
    
    // Clear queue
    printf("\nClearing queue\n");
    queue_clear(queue);
    printf("Queue size after clear: %zu\n", queue_size(queue));
    
    // Clean up
    queue_destroy(queue);
    return 0;
} 
