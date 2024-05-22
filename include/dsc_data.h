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

/**
 * @file dsc_data.h
 * @brief Definitions for generic data storage and comparison.
 */

#ifndef DSC_DATA_H
#define DSC_DATA_H

#include "dsc_type.h"
#include "dsc_error.h"

/**
 * @brief Union for storing generic data.
 *
 * The DSCData union provides a way to store generic data of different types.
 * It allows containers to hold elements of various types without the need for
 * explicit type casting.
 */
typedef union DSCData DSCData;

union DSCData {
    bool b;        /** Boolean value. */
    bool *b_ptr;   /** Dynamically allocated boolean array. */
    char c;        /** Character value. */
    char *c_ptr;   /** Dynamically allocated character array. */
    int i;         /** Integer value. */
    int *i_ptr;    /** Dynamically allocated integer array. */
    float f;       /** Single-precision floating-point value. */
    float *f_ptr;  /** Dynamically allocated single-precision floating-point array. */
    double d;      /** Double-precision floating-point value. */
    double *d_ptr; /** Dynamically allocated double-precision floating-point array. */
    char *s;       /** String value (character pointer). */
    char **s_ptr;  /** Dynamically allocated array of strings (character pointers). */
};

/**
 * @brief Compare two DSCData values of the specified type.
 *
 * This function compares the values stored in `data1` and `data2` based on the
 * specified `type`. The comparison follows the same rules as the standard
 * comparison operators for the respective types.
 *
 * @param data1 The first DSCData value to compare.
 * @param data2 A pointer to the second value to compare.
 * @param type The type of the values being compared.
 * @return An integer indicating the result of the comparison:
 *         - A negative value if `data1` is less than `data2`.
 *         - Zero if `data1` is equal to `data2`.
 *         - A positive value if `data1` is greater than `data2`.
 *         - INT32_MIN if an invalid type is specified.
 */
int dsc_compare(DSCData data1, void *data2, DSCType type);

#endif // DSC_DATA_H
