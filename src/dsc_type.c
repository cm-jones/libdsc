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

#include <stddef.h>
#include <stdbool.h>

#include "../include/dsc_type.h"

#define CHECK_TYPE(type, enum_type) \
    if (sizeof(*(type *)data) == sizeof(type)) { \
        return enum_type; \
    }

bool dsc_type_is_valid(DSCType type) {
    return type > 0 && type < DSC_TYPE_COUNT;
}

size_t dsc_sizeof(DSCType type) {
    switch (type) {
        case DSC_TYPE_CHAR:
            return sizeof(char);
        case DSC_TYPE_UCHAR:
            return sizeof(unsigned char);
        case DSC_TYPE_SHORT:
            return sizeof(short);
        case DSC_TYPE_USHORT:
            return sizeof(unsigned short);
        case DSC_TYPE_INT:
            return sizeof(int);
        case DSC_TYPE_UINT:
            return sizeof(unsigned int);
        case DSC_TYPE_LONG:
            return sizeof(long);
        case DSC_TYPE_ULONG:
            return sizeof(unsigned long);
        case DSC_TYPE_LLONG:
            return sizeof(long long);
        case DSC_TYPE_ULLONG:
            return sizeof(unsigned long long);
        case DSC_TYPE_FLOAT:
            return sizeof(float);
        case DSC_TYPE_DOUBLE:
            return sizeof(double);
        case DSC_TYPE_LDOUBLE:
            return sizeof(long double);
        case DSC_TYPE_STRING:
            return sizeof(char *);
        case DSC_TYPE_BOOL:
            return sizeof(bool);
        case DSC_TYPE_POINTER:
            return sizeof(void *);
        default:
            // Unknown type
            return 0;
    }
}

DSCType dsc_typeof(void *data) {
    CHECK_TYPE(char, DSC_TYPE_CHAR)
    CHECK_TYPE(unsigned char, DSC_TYPE_UCHAR)
    CHECK_TYPE(short, DSC_TYPE_SHORT)
    CHECK_TYPE(unsigned short, DSC_TYPE_USHORT)
    CHECK_TYPE(int, DSC_TYPE_INT)
    CHECK_TYPE(unsigned int, DSC_TYPE_UINT)
    CHECK_TYPE(long, DSC_TYPE_LONG)
    CHECK_TYPE(unsigned long, DSC_TYPE_ULONG)
    CHECK_TYPE(long long, DSC_TYPE_LLONG)
    CHECK_TYPE(unsigned long long, DSC_TYPE_ULLONG)
    CHECK_TYPE(float, DSC_TYPE_FLOAT)
    CHECK_TYPE(double, DSC_TYPE_DOUBLE)
    CHECK_TYPE(long double, DSC_TYPE_LDOUBLE)
    CHECK_TYPE(char *, DSC_TYPE_STRING)
    CHECK_TYPE(bool, DSC_TYPE_BOOL)
    CHECK_TYPE(void *, DSC_TYPE_POINTER)

    // Unknown type
    return DSC_TYPE_UNKNOWN;
}
