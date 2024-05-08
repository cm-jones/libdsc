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

#ifndef __DSC_TYPE_H__
#define __DSC_TYPE_H__

/**
 * @brief Represents the data types available in the DSC library.
 *
 * The DSCType enum defines a set of constants representing different data types
 * that can be used with the containers in the DSC library. It includes commonly
 * used primitive types, as well as some additional types like strings and
 * booleans.
 */
typedef enum DSCType DSCType;

enum DSCType {
    DSC_TYPE_UNKNOWN,   /** Unknown or unrecognized type. */
    DSC_TYPE_CHAR,      /** Character type. */
    DSC_TYPE_INT,       /** Integer type. */
    DSC_TYPE_FLOAT,     /** Single-precision floating-point type. */
    DSC_TYPE_DOUBLE,    /** Double-precision floating-point type. */
    DSC_TYPE_STRING,    /** String type (character pointer). */
    DSC_TYPE_BOOL,      /** Boolean type. */
    DSC_TYPE_COUNT      /** The total number of types. */
};

/**
 * @brief Union for storing generic data.
 *
 * The DSCData union provides a way to store generic data of different types.
 * It allows containers to hold elements of various types without the need for
 * explicit type casting.
 */
typedef union DSCData DSCData;

union DSCData {
    char c;     /** Character value. */
    int i;      /** Integer value. */
    float f;    /** Single-precision floating-point value. */
    double d;   /** Double-precision floating-point value. */
    char *s;    /** String value (character pointer). */
    bool b;     /** Boolean value. */
};

/**
 * @brief Checks if the specified data type is valid.
 *
 * The dsc_type_is_valid function takes a DSCType value representing a data
 * type and returns a boolean value indicating whether the type is a valid
 * type defined in the DSCType enum.
 *
 * @param type The DSCType value representing the data type.
 * @return true if the type is a valid type, false otherwise.
 */
bool dsc_type_is_valid(DSCType type);

/**
 * @brief Returns the size of the specified data type.
 *
 * The dsc_size_of function takes a DSCType value representing a data type and
 * returns the size of that type in bytes. This function is used when
 * initializing a new container to determine the size of the elements based on
 * the provided data type.
 *
 * @param type The DSCType value representing the data type.
 * @return The size of the specified data type in bytes, or 0 if the type is
 * unknown.
 */
size_t dsc_size_of(DSCType type);

#endif // __DSC_TYPE_H__
