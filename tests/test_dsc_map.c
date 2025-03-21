// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../include/dsc_map.h"

// Basic initialization test
void test_dsc_map_init_deinit(void) {
    DSCMap *map = NULL;
    map = (DSCMap*)malloc(sizeof(DSCMap));
    assert(map != NULL);
    assert(dsc_map_init(map, DSC_TYPE_INT, DSC_TYPE_STRING) == DSC_ERROR_OK);
    assert(dsc_map_deinit(map) == DSC_ERROR_OK);
    free(map);
}

int main(void) {
    test_dsc_map_init_deinit();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
