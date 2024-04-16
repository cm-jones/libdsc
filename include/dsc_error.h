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

#ifndef __DSC_ERROR_H__
#define __DSC_ERROR_H__

/**
 * @enum dsc_error_t
 * @brief Represents the error codes used in the DSC library.
 *
 * @constant DSC_ERROR_NONE No error occurred.
 * @constant DSC_ERROR_INVALID_ARGUMENT An invalid argument was passed to a function.
 * @constant DSC_ERROR_OUT_OF_MEMORY Failed to allocate memory.
 * @constant DSC_ERROR_EMPTY_LIST The list is empty.
 * @constant DSC_ERROR_EMPTY_SET The set is empty.
 * @constant DSC_ERROR_VALUE_ALREADY_EXISTS The value already exists in the set.
 * @constant DSC_ERROR_INDEX_OUT_OF_BOUNDS The index is out of bounds.
 * @constant DSC_ERROR_VALUE_NOT_FOUND The value was not found.
 */
enum dsc_error_t {
    DSC_ERROR_NONE,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_OUT_OF_MEMORY,
    DSC_ERROR_EMPTY_LIST,
    DSC_ERROR_EMPTY_SET,
    DSC_ERROR_VALUE_ALREADY_EXISTS,
    DSC_ERROR_INDEX_OUT_OF_BOUNDS,
    DSC_ERROR_VALUE_NOT_FOUND
};

#endif // __DSC_ERROR_H__
