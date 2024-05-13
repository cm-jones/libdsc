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

#ifndef DSC_MAP_H
#define DSC_MAP_H

#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_MAP_INITIAL_CAPACITY 16

#define DSC_MAP_LOAD_FACTOR 0.75

typedef struct DSCMap DSCMap;

DSCError dsc_map_init(DSCMap *new_map, DSCType key_type, DSCType value_type);

DSCError dsc_map_deinit(DSCMap *map);

DSCError dsc_map_size(const DSCMap *map, size_t *size);

DSCError dsc_map_capacity(const DSCMap *map, size_t *capacity);

DSCError dsc_map_is_empty(const DSCMap *map, bool *is_empty);

DSCError dsc_map_get(const DSCMap *map, void *key, void *value);

DSCError dsc_map_contains(const DSCMap *map, void *key, bool *contains);

DSCError dsc_map_insert(DSCMap *map, void *key, void *value);

DSCError dsc_map_erase(DSCMap *map, void *key);

DSCError dsc_map_clear(DSCMap *map);

#endif // DSC_MAP_H
