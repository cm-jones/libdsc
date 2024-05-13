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

#ifndef DSC_SET_H
#define DSC_SET_H

#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_SET_INITIAL_CAPACITY 16

#define DSC_SET_LOAD_FACTOR 0.75

typedef struct DSCSet DSCSet;

DSCError dsc_set_init(DSCSet *new_set, DSCType type);

DSCError dsc_set_deinit(DSCSet *set);

DSCError dsc_set_size(const DSCSet *set, size_t *size);

DSCError dsc_set_capacity(const DSCSet *set, size_t *capacity);

DSCError dsc_set_load_factor(const DSCSet *set, double *load_factor);

DSCError dsc_set_is_empty(const DSCSet *set, bool *is_empty);

DSCError dsc_set_contains(const DSCSet *set, void *data, bool *contains);

DSCError dsc_set_insert(DSCSet *set, void *data);

DSCError dsc_set_erase(DSCSet *set, void *data);

#endif // DSC_SET_H
