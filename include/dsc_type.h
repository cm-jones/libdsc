// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_TYPE_H
#define DSC_TYPE_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Represents the data types available in libdsc.
 *
 * The DSCType enum defines a set of constants representing different data types
 * that can be used with the containers in libdsc. It includes commonly used
 * primitive types, as well as some additional types like strings and
 * booleans.
 */
typedef enum DSCType {
    DSC_TYPE_UNKNOWN, /** Unknown or unrecognized type. */
    DSC_TYPE_BOOL,    /** Boolean type. */
    DSC_TYPE_CHAR,    /** Character type. */
    DSC_TYPE_INT,     /** Integer type. */
    DSC_TYPE_FLOAT,   /** Single-precision floating-point type. */
    DSC_TYPE_DOUBLE,  /** Double-precision floating-point type. */
    DSC_TYPE_STRING,  /** String type (character pointer). */
    DSC_TYPE_COUNT    /** The total number of types. */
} DSCType;

/**
 * @brief Checks if the specified data type is invalid.
 *
 * The dsc_type_invalid function takes a DSCType value representing a data type
 * and returns a boolean value indicating whether the type is an invalid type,
 * i.e., not defined in the DSCType enum.
 *
 * @param type The DSCType value representing the data type.
 * @return true if the type is invalid, false otherwise.
 */
bool dsc_type_invalid(DSCType type);

#endif  // DSC_TYPE_H
