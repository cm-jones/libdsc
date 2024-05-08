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

#include "../include/dsc_type.h"

bool dsc_type_is_valid(DSCType type) {
    return type > DSC_TYPE_UNKNOWN && type < DSC_TYPE_COUNT;
}

size_t dsc_size_of(DSCType type) {
    switch (type) {
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
        case DSC_TYPE_BOOL:
            return sizeof(bool);
        default:
            return 0;
    }
}
