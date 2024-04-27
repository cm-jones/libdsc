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

#include <string.h>
#include <stdbool.h>

#include "../include/dsc_utils.h"

int dsc_utils_compare(void *ptr1, void *ptr2, DSCType type) {
    if (!dsc_type_is_valid(type)) {
        return -1;
    }

    switch (type) {
        case DSC_TYPE_CHAR:
            return (*(char *) ptr1 - *(char *) ptr2);
        case DSC_TYPE_UCHAR:
            return (*(unsigned char *) ptr1 - *(unsigned char *) ptr2);
        case DSC_TYPE_SHORT:
            return (*(short *) ptr1 - *(short *) ptr2);
        case DSC_TYPE_USHORT:
            return (*(unsigned short *) ptr1 - *(unsigned short *) ptr2);
        case DSC_TYPE_INT:
            return (*(int *) ptr1 - *(int *) ptr2);
        case DSC_TYPE_UINT:
            return (*(unsigned int *) ptr1 - *(unsigned int *) ptr2);
        case DSC_TYPE_LONG:
            return (*(long *) ptr1 - *(long *) ptr2);
        case DSC_TYPE_ULONG:
            return (*(unsigned long *) ptr1 - *(unsigned long *) ptr2);
        case DSC_TYPE_LLONG:
            return (*(long long *) ptr1 - *(long long *) ptr2);
        case DSC_TYPE_ULLONG:
            return (*(unsigned long long *) ptr1 - *(unsigned long long *) ptr2);
        case DSC_TYPE_FLOAT:
            return (*(float *) ptr1 > *(float *) ptr2) - (*(float *) ptr1 < *(float *) ptr2);
        case DSC_TYPE_DOUBLE:
            return (*(double *) ptr1 > *(double *) ptr2) - (*(double *) ptr1 < *(double *) ptr2);
        case DSC_TYPE_LDOUBLE:
            return (*(long double *) ptr1 > *(long double *) ptr2) - (*(long double *) ptr1 < *(long double *) ptr2);
        case DSC_TYPE_BOOL:
            return (*(bool *) ptr1 - *(bool *) ptr2);
        case DSC_TYPE_POINTER:
            return ((uintptr_t) ptr1 - (uintptr_t) ptr2);
        case DSC_TYPE_STRING:
            return strcmp((const char *) ptr1, (const char *) ptr2);
        default:
            // Unknown type
            return -1;
    }
}

uint32_t dsc_utils_hash(void *key, DSCType key_type, size_t capacity) {
    uint32_t hash;

    switch (key_type) {
        case DSC_TYPE_UNKNOWN:
            // Handle unknown types or return an error
            return 0;
        case DSC_TYPE_CHAR:
            hash = *(char *) key;
            break;
        case DSC_TYPE_UCHAR:
            hash = *(unsigned char *) key;
            break;
        case DSC_TYPE_SHORT:
            hash = *(short *) key;
            break;
        case DSC_TYPE_USHORT:
            hash = *(unsigned short *) key;
            break;
        case DSC_TYPE_INT:
            hash = *(int *) key;
            break;
        case DSC_TYPE_UINT:
            hash = *(unsigned int *) key;
            break;
        case DSC_TYPE_LONG:
            hash = *(long *) key;
            break;
        case DSC_TYPE_ULONG:
            hash = *(unsigned long *) key;
            break;
        case DSC_TYPE_LLONG:
            hash = *(long long *) key;
            break;
        case DSC_TYPE_ULLONG:
            hash = *(unsigned long long *) key;
            break;
        case DSC_TYPE_FLOAT:
            hash = *(uint32_t *) key;
            break;
        case DSC_TYPE_DOUBLE:
            hash = *(uint32_t *) key;
            break;
        case DSC_TYPE_LDOUBLE:
            hash = *(uint32_t *) key;
            break;
        case DSC_TYPE_STRING:
            // Use the DJB2 string hashing algorithm
            hash = 5381;
            const char *str = (const char *) key;
            int c;
            while ((c = *str++)) {
                hash = ((hash << 5) + hash) + c;
            }
            break;
        case DSC_TYPE_BOOL:
            hash = *(bool *) key;
            break;
        case DSC_TYPE_POINTER:
            hash = (uint32_t) (uintptr_t) key;
            break;
        default:
            // Handle unknown types or return an error
            return 0;
    }

    // Mix the bits of the hash value and use a prime number for better distribution
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;

    return hash % capacity;
}
