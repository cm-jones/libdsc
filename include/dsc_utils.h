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

#ifndef __DSC_UTILS_H__
#define __DSC_UTILS_H__

/**
 * @brief Calculates the hash value for a given key and capacity.
 *
 * This function uses a simple modulo-based hash function to calculate the hash
 * value for a given key and capacity.
 *
 * @param key The key to calculate the hash value for.
 * @param capacity The capacity of the hash table.
 * @return The calculated hash value.
 */
uint32_t dsc_hash(int key, int capacity);

#endif // __DSC_UTILS_H__
