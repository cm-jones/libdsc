#include <libdsc/list.h>
#include <stdio.h>

int main() {
    // Create a list of integers
    dsc_list_t* list = list_create(sizeof(int));
    if (!list) {
        printf("Failed to create list\n");
        return 1;
    }
    
    // Push some values at the front
    printf("Pushing values at front:\n");
    for (int i = 1; i <= 3; ++i) {
        if (list_push_front(list, &i) != DSC_SUCCESS) {
            printf("Failed to push %d at front\n", i);
            continue;
        }
        printf("Pushed %d at front\n", i);
    }
    
    // Push some values at the back
    printf("\nPushing values at back:\n");
    for (int i = 4; i <= 6; ++i) {
        if (list_push_back(list, &i) != DSC_SUCCESS) {
            printf("Failed to push %d at back\n", i);
            continue;
        }
        printf("Pushed %d at back\n", i);
    }
    
    // Print list size
    printf("\nList size: %zu\n", list_size(list));
    
    // Print all values forward
    printf("\nList contents (forward):\n");
    list_node_t* current = list_begin(list);
    while (current) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Print all values backward
    printf("\nList contents (backward):\n");
    current = list_rbegin(list);
    while (current) {
        printf("%d ", *(int*)current->data);
        current = current->prev;
    }
    printf("\n");
    
    // Insert a value before the second node
    printf("\nInserting value before second node:\n");
    current = list_begin(list);
    current = current->next; // Move to second node
    int value = 42;
    if (list_insert(list, current, &value) == DSC_SUCCESS) {
        printf("Inserted %d\n", value);
    }
    
    // Print updated list
    printf("\nList after insertion:\n");
    current = list_begin(list);
    while (current) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Remove the inserted node
    printf("\nRemoving inserted node:\n");
    current = list_begin(list);
    current = current->next; // Move to inserted node
    if (list_erase(list, current) == DSC_SUCCESS) {
        printf("Node removed\n");
    }
    
    // Print updated list
    printf("\nList after removal:\n");
    current = list_begin(list);
    while (current) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
    printf("\n");
    
    // Pop from front and back
    printf("\nPopping from front and back:\n");
    int* front = (int*)list_front(list);
    int* back = (int*)list_back(list);
    if (front && back) {
        printf("Front: %d, Back: %d\n", *front, *back);
    }
    
    list_pop_front(list);
    list_pop_back(list);
    
    printf("After popping - Size: %zu\n", list_size(list));
    
    // Try to pop from empty list
    list_clear(list);
    printf("\nTrying to pop from empty list:\n");
    if (list_pop_front(list) == DSC_ERROR_EMPTY) {
        printf("Pop front failed - list is empty (expected)\n");
    }
    if (list_pop_back(list) == DSC_ERROR_EMPTY) {
        printf("Pop back failed - list is empty (expected)\n");
    }
    
    // Clean up
    list_destroy(list);
    return 0;
} 
