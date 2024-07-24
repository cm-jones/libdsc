// SPDX-License-Identifier: GPL-3.0-or-later

/**
 * @file dsc_error.h
 * @brief This file defines the error codes used in libdsc.
 */

#ifndef DSC_ERROR_H
#define DSC_ERROR_H

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

#endif // DSC_ERROR_H
