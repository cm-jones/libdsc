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
 * @file dsc_error.h
 * @brief This file defines the error codes used in libdsc.
 */

#ifndef __DSC_ERROR_H__
#define __DSC_ERROR_H__

/**
 * @brief The DSCError type represents the various error codes used in libdsc.
 */
typedef enum DSCError DSCError;

/**
 * @brief The enumeration of error codes used in libdsc.
 */
enum DSCError {
    DSC_ERROR_OK,               /** No error. */
    DSC_ERROR_INVALID_ARGUMENT, /** Invalid argument. */
    DSC_ERROR_INVALID_TYPE,     /** Invalid type. */
    DSC_ERROR_EMPTY_CONTAINER,  /** Empty container. */
    DSC_ERROR_OUT_OF_MEMORY,    /** Out of memory. */
    DSC_ERROR_OUT_OF_RANGE,     /** Out of range. */
    DSC_ERROR_NOT_FOUND,        /** Element not found. */
    DSC_ERROR_ALREADY_EXISTS    /** Element already exists. */
};

#endif // __DSC_ERROR_H__
