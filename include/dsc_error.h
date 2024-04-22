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
 * @constant DSC_ERROR_NONE                       No error occurred.
 * @constant DSC_ERROR_INVALID_ARGUMENT           An invalid argument was passed to a function.
 * @constant DSC_ERROR_OUT_OF_RANGE               The index is out of bounds.
 * @constant DSC_ERROR_OUT_OF_MEMORY              Failed to allocate memory.
 * @constant DSC_ERROR_EMPTY_CONTAINER            The container is empty.
 * @constant DSC_ERROR_KEY_NOT_FOUND              The key was not found in the associative container.
 * @constant DSC_ERROR_VECTOR_CAPACITY_EXCEEDED   The vector capacity has been exceeded.
 * @constant DSC_ERROR_HASHMAP_KEY_ALREADY_EXISTS The key already exists in the hash map.
 * @constant DSC_ERROR_QUEUE_FULL                 The queue is full.
 */
typedef enum DSCError {
    DSC_ERROR_NONE,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_OUT_OF_RANGE,
    DSC_ERROR_OUT_OF_MEMORY,
    DSC_ERROR_EMPTY_CONTAINER,
    DSC_ERROR_KEY_NOT_FOUND,
    DSC_ERROR_VECTOR_CAPACITY_EXCEEDED,
    DSC_ERROR_HASHMAP_KEY_ALREADY_EXISTS,
    DSC_ERROR_QUEUE_FULL
} DSCError;

/**
 * @brief Sets the last error code.
 *
 * @param error The error code to set.
 */
void dsc_set_error(DSCError error);

/**
 * @brief Gets the last error code.
 *
 * @return The last error code.
 */
DSCError dsc_get_error(void);

#endif // __DSC_ERROR_H__
