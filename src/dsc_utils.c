// SPDX-License-Identifier: GPL-3.0-or-later

#include <string.h>
#include <stdbool.h>

#include "../include/dsc_utils.h"

bool dsc_type_is_valid(DSCType type) {
    return !dsc_type_invalid(type);
}

size_t dsc_size_of(DSCType type) {
    switch (type) {
        case DSC_TYPE_BOOL:
            return sizeof(bool);
        case DSC_TYPE_CHAR:
            return sizeof(char);
        case DSC_TYPE_INT:
            return sizeof(int);
        case DSC_TYPE_FLOAT:
            return sizeof(float);
        case DSC_TYPE_DOUBLE:
            return sizeof(double);
        case DSC_TYPE_STRING:
            return sizeof(char *);
        default:
            return 0; // Invalid type
    }
}

// The dsc_compare function has been moved to dsc_data.c to avoid duplicate symbols

uint32_t dsc_hash(void *key, DSCType key_type, size_t capacity) {
    uint32_t hash;

    switch (key_type) {
        case DSC_TYPE_UNKNOWN:
            // Handle unknown types or return an error
            return 0;
        case DSC_TYPE_CHAR:
            hash = *(char *) key;
            break;
        case DSC_TYPE_FLOAT:
            hash = *(uint32_t *) key;
            break;
        case DSC_TYPE_DOUBLE:
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
        case DSC_TYPE_INT:
            hash = *(int *) key;
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
