// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdlib.h>
#include <string.h>

#include "../include/dsc_data.h"

int dsc_compare(DSCData data1, void *data2, DSCType type) {
    switch (type) {
        case DSC_TYPE_BOOL:
            return data1.b - *(bool *) data2;

        case DSC_TYPE_CHAR:
            return data1.c - *(char *) data2;

        case DSC_TYPE_INT:
            return data1.i - *(int *) data2;

        case DSC_TYPE_FLOAT:
            return data1.f - *(float *) data2;

        case DSC_TYPE_DOUBLE:
            return data1.d - *(double *) data2;

        case DSC_TYPE_STRING:
            return strcmp(data1.s, *(const char **) data2);

        default:
            return INT32_MIN;
    }
}
