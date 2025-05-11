#include <libdsc/unordered_set.h>
#include <stdio.h>
#include <string.h>

// Hash function for strings
static size_t string_hash(const void* key) {
    const char* str = *(const char**)key;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Compare function for strings
static int string_compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

int main() {
    // Create a set of strings
    dsc_unordered_set_t* set = unordered_set_create(sizeof(char*), string_hash, string_compare);
    if (!set) {
        printf("Failed to create set\n");
        return 1;
    }
    
    // Insert some elements
    const char* elements[] = {"apple", "banana", "orange", "grape", "kiwi"};
    
    for (int i = 0; i < 5; ++i) {
        if (unordered_set_insert(set, &elements[i]) != DSC_SUCCESS) {
            printf("Failed to insert %s\n", elements[i]);
            continue;
        }
        printf("Inserted %s\n", elements[i]);
    }
    
    // Find and print elements
    printf("\nFinding elements:\n");
    for (int i = 0; i < 5; ++i) {
        const char** found = (const char**)unordered_set_find(set, &elements[i]);
        if (found) {
            printf("Found %s\n", *found);
        } else {
            printf("Not found: %s\n", elements[i]);
        }
    }
    
    // Try to find a non-existent element
    const char* non_existent = "mango";
    const char** found = (const char**)unordered_set_find(set, &non_existent);
    printf("\nLooking for non-existent element 'mango': %s\n", 
           found ? "Found (unexpected)" : "Not found (expected)");
    
    // Try to insert a duplicate
    if (unordered_set_insert(set, &elements[0]) == DSC_SUCCESS) {
        printf("\nInserted duplicate %s\n", elements[0]);
    }
    
    // Erase an element
    if (unordered_set_erase(set, &elements[2]) == DSC_SUCCESS) {
        printf("\nErased %s\n", elements[2]);
        found = (const char**)unordered_set_find(set, &elements[2]);
        printf("Looking for erased element: %s\n", 
               found ? "Found (unexpected)" : "Not found (expected)");
    }
    
    // Print final size
    printf("\nFinal set size: %zu\n", unordered_set_size(set));
    
    // Clean up
    unordered_set_destroy(set);
    return 0;
} 
