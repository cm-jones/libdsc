// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../include/dsc_queue.h"

// Basic initialization test
void test_dsc_queue_init_deinit(void) {
    DSCQueue *queue = NULL;
    
    // Just allocate 1 byte as a placeholder to avoid sizeof of incomplete type
    queue = (DSCQueue*)malloc(1);
    assert(queue != NULL);
    
    assert(dsc_queue_init(queue, DSC_TYPE_INT) == DSC_ERROR_OK);
    assert(dsc_queue_deinit(queue) == DSC_ERROR_OK);
}

int main(void) {
    test_dsc_queue_init_deinit();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
