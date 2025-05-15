#include <libdsc/unordered_set.h>
#include <stdio.h>
#include <string.h>

// Hash function for strings
static size_t string_hash(void const *key) {
    char const *str = *(char const **)key;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Compare function for strings
static int string_compare(void const *a, void const *b) {
    char const *str1 = *(char const **)a;
    char const *str2 = *(char const **)b;
    return strcmp(str1, str2);
}

int main() {
    // Create a set of strings
    dsc_unordered_set *set =
        unordered_set_create(sizeof(char *), string_hash, string_compare);
    if (!set) {
        printf("Failed to create set\n");
        return EXIT_FAILURE;
    }

    // Insert some elements
    char const *elements[] = {"apple", "banana", "orange", "grape", "kiwi"};

    for (size_t i = 0; i < 5; ++i) {
        if (unordered_set_insert(set, &elements[i]) != DSC_ERROR_OK) {
            printf("Failed to insert %s\n", elements[i]);
            continue;
        }
        printf("Inserted %s\n", elements[i]);
    }

    // Find and print elements
    printf("\nFinding elements:\n");
    for (size_t i = 0; i < 5; ++i) {
        char const **found =
            (char const **)unordered_set_find(set, &elements[i]);
        if (found) {
            printf("Found %s\n", *found);
        } else {
            printf("Not found: %s\n", elements[i]);
        }
    }

    // Try to find a non-existent element
    char const *non_existent = "mango";
    char const **found = (char const **)unordered_set_find(set, &non_existent);
    printf("\nLooking for non-existent element 'mango': %s\n",
           found ? "Found (unexpected)" : "Not found (expected)");

    // Try to insert a duplicate
    if (unordered_set_insert(set, &elements[0]) == DSC_ERROR_OK) {
        printf("\nInserted duplicate %s\n", elements[0]);
    }

    // Erase an element
    if (unordered_set_erase(set, &elements[2]) == DSC_ERROR_OK) {
        printf("\nErased %s\n", elements[2]);
        found = (char const **)unordered_set_find(set, &elements[2]);
        printf("Looking for erased element: %s\n",
               found ? "Found (unexpected)" : "Not found (expected)");
    }

    // Print final size
    printf("\nFinal set size: %zu\n", unordered_set_size(set));

    // Clean up
    unordered_set_destroy(set);
    return EXIT_SUCCESS;
}
