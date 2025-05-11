#include <libdsc/unordered_map.h>
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
    // Create a map with string keys and integer values
    dsc_unordered_map_t* map = unordered_map_create(sizeof(char*), sizeof(int), string_hash, string_compare);
    if (!map) {
        printf("Failed to create map\n");
        return 1;
    }
    
    // Insert some key-value pairs
    const char* keys[] = {"apple", "banana", "orange", "grape", "kiwi"};
    int values[] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; ++i) {
        if (unordered_map_insert(map, &keys[i], &values[i]) != DSC_SUCCESS) {
            printf("Failed to insert %s\n", keys[i]);
            continue;
        }
        printf("Inserted %s: %d\n", keys[i], values[i]);
    }
    
    // Find and print values
    printf("\nFinding values:\n");
    for (int i = 0; i < 5; ++i) {
        int* value = (int*)unordered_map_find(map, &keys[i]);
        if (value) {
            printf("Found %s: %d\n", keys[i], *value);
        } else {
            printf("Not found: %s\n", keys[i]);
        }
    }
    
    // Try to find a non-existent key
    const char* non_existent = "mango";
    int* value = (int*)unordered_map_find(map, &non_existent);
    printf("\nLooking for non-existent key 'mango': %s\n", 
           value ? "Found (unexpected)" : "Not found (expected)");
    
    // Update a value
    int new_value = 42;
    if (unordered_map_insert(map, &keys[0], &new_value) == DSC_SUCCESS) {
        value = (int*)unordered_map_find(map, &keys[0]);
        printf("\nUpdated %s: %d\n", keys[0], *value);
    }
    
    // Erase a key
    if (unordered_map_erase(map, &keys[2]) == DSC_SUCCESS) {
        printf("\nErased %s\n", keys[2]);
        value = (int*)unordered_map_find(map, &keys[2]);
        printf("Looking for erased key: %s\n", 
               value ? "Found (unexpected)" : "Not found (expected)");
    }
    
    // Print final size
    printf("\nFinal map size: %zu\n", unordered_map_size(map));
    
    // Clean up
    unordered_map_destroy(map);
    return 0;
} 
