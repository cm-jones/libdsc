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

#ifndef __DSC_SET_H__
#define __DSC_SET_H__

#include "dsc_error.h"

// Hash set structure
struct dsc_hash_set {
    /* data */
};

// Create a new hash set
struct dsc_set_t *dsc_set_create();

// Destroy the hash set and free its memory
void dsc_set_destroy(struct dsc_set_t *set);

// Add an element to the hash set
struct dsc_set_t *dsc_set_add(struct dsc_set_t *set, int value);

// Remove an element from the hash set
struct dsc_set_t *dsc_set_remove(struct dsc_set_t *set, int value);

// Check if an element exists in the hash set
struct dsc_set_t *dsc_set_contains(struct dsc_set_t *set, int value);

// Get the size of the hash set
int dsc_set_size(struct dsc_set_t *set);

// Check if the hash set is empty
struct dsc_set_t *dsc_set_is_empty(struct dsc_set_t *set);

// Clear all elements from the hash set
struct dsc_set_t *dsc_set_clear(struct dsc_set_t *set);

#endif // __DSC_SET_H__
