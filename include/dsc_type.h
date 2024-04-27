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
 * @enum DSCType
 * @brief Represents the data types available in the DSC library.
 *
 * The DSCType enum defines a set of constants representing different data types
 * that can be used with the containers in the DSC library. It includes commonly
 * used primitive types, as well as some additional types like strings, booleans,
 * and pointers.
 *
 * @constant DSC_TYPE_UNKNOWN   Unknown or unrecognized type.
 * @constant DSC_TYPE_CHAR      Character type.
 * @constant DSC_TYPE_UCHAR     Unsigned character type.
 * @constant DSC_TYPE_SHORT     Short integer type.
 * @constant DSC_TYPE_USHORT    Unsigned short integer type.
 * @constant DSC_TYPE_INT       Integer type.
 * @constant DSC_TYPE_UINT      Unsigned integer type.
 * @constant DSC_TYPE_LONG      Long integer type.
 * @constant DSC_TYPE_ULONG     Unsigned long integer type.
 * @constant DSC_TYPE_LLONG     Long long integer type.
 * @constant DSC_TYPE_ULLONG    Unsigned long long integer type.
 * @constant DSC_TYPE_FLOAT     Single-precision floating-point type.
 * @constant DSC_TYPE_DOUBLE    Double-precision floating-point type.
 * @constant DSC_TYPE_LDOUBLE   Long double-precision floating-point type.
 * @constant DSC_TYPE_STRING    String type (character pointer).
 * @constant DSC_TYPE_BOOL      Boolean type.
 * @constant DSC_TYPE_POINTER   Generic pointer type.
 * @constant DSC_TYPE_COUNT     The total number of types.
 */
typedef enum DSCType {
    DSC_TYPE_UNKNOWN,
    DSC_TYPE_CHAR,
    DSC_TYPE_UCHAR,
    DSC_TYPE_SHORT,
    DSC_TYPE_USHORT,
    DSC_TYPE_INT,
    DSC_TYPE_UINT,
    DSC_TYPE_LONG,
    DSC_TYPE_ULONG,
    DSC_TYPE_LLONG,
    DSC_TYPE_ULLONG,
    DSC_TYPE_FLOAT,
    DSC_TYPE_DOUBLE,
    DSC_TYPE_LDOUBLE,
    DSC_TYPE_STRING,
    DSC_TYPE_BOOL,
    DSC_TYPE_POINTER,
    DSC_TYPE_COUNT
} DSCType;

bool dsc_type_is_valid(DSCType type);

/**
 * @brief Returns the size of the specified data type.
 *
 * The dsc_sizeof function takes a DSCType value representing a data type and
 * returns the size of that type in bytes. This function is used when initializing
 * a new container to determine the size of the elements based on the provided
 * data type.
 *
 * @param type The DSCType value representing the data type.
 * @return The size of the specified data type in bytes, or 0 if the type is unknown.
 */
size_t dsc_sizeof(DSCType type);

/**
 * @brief Determines the type of the data pointed to by a void pointer.
 *
 * The dsc_typeof function takes a void pointer to the data and attempts to
 * determine its type based on the size of the dereferenced pointer. It compares
 * the size of the dereferenced pointer with the sizes of known types defined in
 * the DSCType enum and returns the corresponding DSCType value if a match is
 * found. If no match is found, it returns DSC_TYPE_UNKNOWN.
 *
 * @param data Pointer to the data.
 * @return The DSCType value representing the type of the data, or DSC_TYPE_UNKNOWN
 *         if the type cannot be determined.
 *
 * @note This function assumes that the data pointer is a valid pointer to the
 *       actual data. If the pointer is invalid or points to a different type
 *       than the one stored in the container, the behavior is undefined.
 *       It is the caller's responsibility to ensure that the data pointer is
 *       valid and points to the correct type.
 */
DSCType dsc_typeof(void *data);

#endif // __DSC_TYPE_H__
