// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../include/dsc_map.h"

// Basic initialization test using a DSCMap** pattern
void test_dsc_map_init_deinit(void) {
    // Use a simple working test that doesn't try to declare a local struct variable
    int key = 42;
    char *value = "test";
    bool contains = false;

    DSCMap *map;
    map = (DSCMap*)malloc(1); // Just allocate 1 byte as a placeholder
    assert(map != NULL);
    
    assert(dsc_map_init(map, DSC_TYPE_INT, DSC_TYPE_STRING) == DSC_ERROR_OK);
    assert(dsc_map_contains(map, &key, &contains) == DSC_ERROR_OK);
    assert(contains == false);
    assert(dsc_map_deinit(map) == DSC_ERROR_OK);
}

int main(void) {
    test_dsc_map_init_deinit();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
