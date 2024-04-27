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

#ifndef __DSC_MAP_H__
#define __DSC_MAP_H__

#include <stdbool.h>
#include <stddef.h>

#include "dsc_type.h"
#include "dsc_error.h"

/**
 * @def DSC_MAP_INITIAL_CAPACITY
 * @brief The initial capacity of the hash map.
 */
#define DSC_MAP_INITIAL_CAPACITY 16

/**
 * @def DSC_MAP_LOAD_FACTOR
 * @brief The load factor threshold for resizing the hash map.
 */
#define DSC_MAP_LOAD_FACTOR 0.75

/* Forward declaration of the map structure */

typedef struct DSCMap *DSCMap;

/* Constructor and destructor for a DSCMap */

DSCMap dsc_map_init(DSCType key_type, DSCType value_type);

bool dsc_map_free(DSCMap map);

/* Capacity */

bool dsc_map_empty(const DSCMap map);

int dsc_map_size(const DSCMap map);

int dsc_map_capacity(const DSCMap map);

/* Element access */

void *dsc_map_get(const DSCMap map, void *key);

bool dsc_map_contains(const DSCMap map, void *key);

/* Modifiers */

bool dsc_map_insert(DSCMap map, void *key, void *value);

bool dsc_map_erase(DSCMap map, void *key);

bool dsc_map_clear(DSCMap map);

/* Error handling */

DSCError dsc_error_get(const DSCMap map);

#endif // __DSC_MAP_H__
