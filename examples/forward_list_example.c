#include <libdsc/forward_list.h>
#include <stdio.h>

int main() {
    // Create a forward list of integers
    dsc_forward_list *list = forward_list_create(sizeof(int));
    if (!list) {
        printf("Failed to create forward list\n");
        return EXIT_FAILURE;
    }

    // Push some values at the front
    int values[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; ++i) {
        if (forward_list_push_front(list, &values[i]) != DSC_ERROR_OK) {
            printf("Failed to push %d\n", values[i]);
            continue;
        }

        printf("Pushed %d at front\n", values[i]);
    }

    // Print list size
    printf("\nList size: %zu\n", forward_list_size(list));

    // Print all values (will be in reverse order: 5, 4, 3, 2, 1)
    printf("\nList contents:\n");
    forward_list_node_t *current = forward_list_begin(list);
    while (current) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");

    // Insert a value after the first node
    int value = 42;
    forward_list_node_t *pos = forward_list_begin(list);
    if (forward_list_insert_after(list, pos, &value) == DSC_ERROR_OK) {
        printf("\nInserted %d after first node\n", value);
    }

    // Print updated list
    printf("\nList after insertion:\n");
    current = forward_list_begin(list);
    while (current) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");

    // Remove the second node (the one we just inserted)
    pos = forward_list_begin(list);
    if (forward_list_erase_after(list, pos) == DSC_ERROR_OK) {
        printf("\nErased node after first node\n");
    }

    // Print updated list
    printf("\nList after erasure:\n");
    current = forward_list_begin(list);
    while (current) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");

    // Pop front until empty
    printf("\nPopping from front:\n");
    while (!forward_list_empty(list)) {
        int *front = (int *)forward_list_front(list);
        if (front) {
            printf("Popping %d\n", *front);
        }
        forward_list_pop_front(list);
    }

    // Try to pop from empty list
    printf("\nTrying to pop from empty list: ");
    if (forward_list_pop_front(list) == DSC_ERROR_EMPTY) {
        printf("List is empty (expected)\n");
    }

    // Push more values
    printf("\nPushing more values:\n");
    for (int i = 6; i <= 10; ++i) {
        if (forward_list_push_front(list, &i) == DSC_ERROR_OK) {
            printf("Pushed %d\n", i);
        }
    }

    // Clear list
    printf("\nClearing list\n");
    forward_list_clear(list);
    printf("List size after clear: %zu\n", forward_list_size(list));

    // Clean up
    forward_list_destroy(list);
    return EXIT_SUCCESS;
}
