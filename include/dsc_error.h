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
 * @enum DSCError
 * @brief Represents the error codes used in the DSC library.
 *
 * The DSCError enum defines a set of error codes that are used to indicate
 * the success or failure of operations in the DSC library. These error codes
 * provide a way to identify and handle specific error conditions that may
 * occur while using the library.
 *
 * The error codes are returned by DSC library functions to indicate the
 * success or failure of an operation. When a function encounters an error,
 * it sets the error code using the appropriate error constant from the
 * DSCError enum and returns an appropriate value (e.g., NULL, false, or an
 * invalid value) to indicate the failure. The user can then check the return
 * value and handle the error accordingly.
 *
 * It is the responsibility of the user to check the return values of the
 * library functions and handle the errors appropriately based on their
 * specific use case and requirements.
 *
 * @constant DSC_ERROR_OK
 *           No error occurred. The operation was successful.
 *
 * @constant DSC_ERROR_TYPE_MISMATCH
 *           There was a mismatch between the expected type and the actual type
 *           of the data.
 *
 * @constant DSC_ERROR_INVALID_ARGUMENT
 *           An invalid argument was passed to a function.
 *
 * @constant DSC_ERROR_OUT_OF_RANGE
 *           The specified index or position is out of the valid range.
 *
 * @constant DSC_ERROR_OUT_OF_MEMORY
 *           Memory allocation failed.
 *
 * @constant DSC_ERROR_EMPTY_CONTAINER
 *           The container is empty.
 *
 * @constant DSC_ERROR_KEY_NOT_FOUND
 *           The specified key was not found in the container.
 *
 * @constant DSC_ERROR_HASHMAP_KEY_ALREADY_EXISTS
 *           The specified key already exists in the hashmap.
 */
typedef enum DSCError {
    DSC_ERROR_OK,
    DSC_ERROR_TYPE_MISMATCH,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_OUT_OF_RANGE,
    DSC_ERROR_OUT_OF_MEMORY,
    DSC_ERROR_EMPTY_CONTAINER,
    DSC_ERROR_KEY_NOT_FOUND,
    DSC_ERROR_HASHMAP_KEY_ALREADY_EXISTS
} DSCError;

#endif // __DSC_ERROR_H__
