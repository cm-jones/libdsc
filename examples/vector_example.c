#include <libdsc/vector.h>
#include <stdio.h>

void print_vector(dsc_vector_t* vec) {
    printf("Vector contents: ");
    for (size_t i = 0; i < vector_size(vec); ++i) {
        int* value = vector_at(vec, i);
        printf("%d ", *value);
    }
    printf("\n");
}

int main(void) {
    // Create a vector of integers
    dsc_vector_t* vec = vector_create(sizeof(int));
    if (!vec) {
        printf("Failed to create vector\n");
        return 1;
    }

    // Add some elements
    int values[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        vector_push_back(vec, &values[i]);
    }

    printf("Initial vector:\n");
    print_vector(vec);

    // Insert an element
    int new_value = 10;
    vector_insert(vec, 2, &new_value);
    printf("\nAfter inserting 10 at index 2:\n");
    print_vector(vec);

    // Remove an element
    vector_erase(vec, 3);
    printf("\nAfter removing element at index 3:\n");
    print_vector(vec);

    // Access elements
    printf("\nFirst element: %d\n", *(int*)vector_front(vec));
    printf("Last element: %d\n", *(int*)vector_back(vec));

    // Resize the vector
    vector_resize(vec, 3);
    printf("\nAfter resizing to 3 elements:\n");
    print_vector(vec);

    // Clear the vector
    vector_clear(vec);
    printf("\nAfter clearing:\n");
    print_vector(vec);

    // Clean up
    vector_destroy(vec);
    return 0;
} 
