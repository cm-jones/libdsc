/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

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
