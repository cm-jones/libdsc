/*
 * This file is part of the Data Structures for C (DSC) library.
 *
 * The Data Structures for C (DSC) library is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * The Data Structures for C (DSC) library is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * the Data Structures for C (DSC) library. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_ERROR_H__
#define __DSC_ERROR_H__

enum dsc_error_t {
    DSC_ERROR_NONE,
    DSC_ERROR_INVALID_ARGUMENT,
    DSC_ERROR_OUT_OF_MEMORY,
    DSC_ERROR_EMPTY_LIST,
    DSC_ERROR_EMPTY_SET,
    DSC_ERROR_DUPLICATE_VALUE,
    DSC_ERROR_INDEX_OUT_OF_BOUNDS,
    DSC_ERROR_VALUE_NOT_FOUND
};

#endif // __DSC_ERROR_H__
