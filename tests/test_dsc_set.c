// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../include/dsc_set.h"

// Basic initialization test
void test_dsc_set_init_deinit(void) {
    DSCSet *set = NULL;
    
    // Just allocate 1 byte as a placeholder to avoid sizeof of incomplete type
    set = (DSCSet*)malloc(1);
    assert(set != NULL);
    
    assert(dsc_set_init(set, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_set_deinit(set) == DSC_ERROR_OK);
}

int main(void) {
    test_dsc_set_init_deinit();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
