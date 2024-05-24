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

#ifndef DSC_LIST_H
#define DSC_LIST_H

#include "dsc_data.h"
#include "dsc_type.h"
#include "dsc_error.h"

typedef struct DSCList DSCList;

DSCError dsc_list_init(DSCList *new_list, DSCType type);

DSCError dsc_list_deinit(DSCList *list);

DSCError dsc_list_size(const DSCList *list, size_t *result);

DSCError dsc_list_empty(const DSCList *list, bool *result);

DSCError dsc_list_front(const DSCList *list, void *result);

DSCError dsc_list_back(const DSCList *list, void *result);

DSCError dsc_list_at(const DSCList *list, size_t index, void *result);

DSCError dsc_list_push_front(DSCList *list, void *data);

DSCError dsc_list_pop_front(DSCList *list, void *result);

DSCError dsc_list_push_back(DSCList *list, void *data);

DSCError dsc_list_pop_back(DSCList *list, void *result);

DSCError dsc_list_insert(DSCList *list, void *data, size_t index);

DSCError dsc_list_erase(DSCList *list, size_t index);

#endif // DSC_LIST_H
