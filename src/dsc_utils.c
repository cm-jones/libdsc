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

#include <stdint.h>

#include "../include/dsc_utils.h"

uint32_t dsc_hash(int key, int capacity) {
    /* Cast the key to an unsigned 32-bit integer */
    uint32_t hash = (uint32_t) key;

    /* Mix the bits of the hash value */
    /* Use a prime number (0x45d9f3b) for better distribution */
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;

    /* Ensure the hash value falls within the valid range */
    return hash % capacity;
}
