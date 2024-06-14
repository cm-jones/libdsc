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

#include "dsc_error.h"
#include "dsc_type.h"

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
    float *f_ptr;  /** Dynamically allocated single-precision floating-point
                      array. */
    double d;      /** Double-precision floating-point value. */
    double *d_ptr; /** Dynamically allocated double-precision floating-point
                      array. */
    char *s;       /** String value (character pointer). */
    char **s_ptr;  /** Dynamically allocated array of strings (character
                      pointers). */
};

/**
 * @brief Allocate memory for a DSCData value of the specified type.
 *
 * This function allocates memory for a DSCData value of the specified `type`
 * and `capacity`. The allocated memory is stored in the `data` parameter.
 *
 * @param data A pointer to the DSCData value to allocate memory for.
 * @param type The type of the DSCData value to allocate memory for.
 * @param capacity The number of elements to allocate memory for.
 * @return A DSCError value indicating the result of the operation:
 *         - DSC_ERROR_OK if the operation was successful.
 *         - DSC_ERROR_OUT_OF_MEMORY if memory allocation failed.
 */
DSCError dsc_data_malloc(DSCData *data, DSCType type, size_t capacity);

/**
 * @brief Reallocate memory for a DSCData value of the specified type.
 *
 * This function reallocates memory for a DSCData value of the specified `type`
 * and `capacity`. The memory to be reallocated is stored in the `data`
 * parameter.
 *
 * @param data A pointer to the DSCData value to reallocate memory for.
 * @param type The type of the DSCData value to reallocate memory for.
 * @param capacity The new number of elements to reallocate memory for.
 * @return A DSCError value indicating the result of the operation:
 *         - DSC_ERROR_OK if the operation was successful.
 *         - DSC_ERROR_INVALID_ARGUMENT if an invalid type is specified.
 *         - DSC_ERROR_OUT_OF_MEMORY if memory reallocation failed.
 */
DSCError dsc_data_realloc(DSCData *data, DSCType type, size_t capacity);

/**
 * @brief Free memory allocated for a DSCData value of the specified type.
 *
 * This function frees the memory allocated for a DSCData value of the specified
 * `type` and `size`. The memory to be freed is stored in the `data` parameter.
 *
 * @param data A pointer to the DSCData value to free memory for.
 * @param type The type of the DSCData value to free memory for.
 * @param size The number of elements to free memory for.
 * @return A DSCError value indicating the result of the operation:
 *         - DSC_ERROR_OK if the operation was successful.
 *         - DSC_ERROR_INVALID_ARGUMENT if an invalid type is specified.
 */
DSCError dsc_data_free(DSCData *data, DSCType type, size_t size);

/**
 * @brief Copy data from a source buffer to a DSCData value.
 *
 * This function copies the data stored in the `src` buffer to the `dest`
 * DSCData value. The data is copied based on the specified `type`.
 *
 * @param dest A pointer to the destination DSCData value to copy data to.
 * @param src A pointer to the source buffer to copy data from.
 * @param type The type of the data to copy.
 * @return A DSCError value indicating the result of the operation:
 *         - DSC_ERROR_OK if the operation was successful.
 *         - DSC_ERROR_INVALID_ARGUMENT if an invalid type is specified.
 */
DSCError dsc_data_copy(DSCData *dest, void *src, DSCType type);

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

#endif  // DSC_DATA_H
