// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../include/dsc_list.h"

// Basic initialization test
void test_dsc_list_init_deinit(void) {
    DSCList *list = dsc_list_init(DSC_TYPE_INT);
    assert(list != NULL);
    assert(dsc_list_deinit(list) == DSC_ERROR_OK);
}

int main(void) {
    test_dsc_list_init_deinit();
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
