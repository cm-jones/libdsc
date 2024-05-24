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

#ifndef DSC_QUEUE_H
#define DSC_QUEUE_H

#include "dsc_data.h"
#include "dsc_type.h"
#include "dsc_error.h"
#include "dsc_utils.h"

#define DSC_QUEUE_INITIAL_CAPACITY 16

typedef struct DSCQueue DSCQueue;

DSCError dsc_queue_init(DSCQueue *new_queue, DSCType type);

DSCError dsc_queue_deinit(DSCQueue *queue);

DSCError dsc_queue_size(const DSCQueue *queue, size_t *result);

DSCError dsc_queue_capacity(const DSCQueue *queue, size_t *result);

DSCError dsc_queue_empty(const DSCQueue *queue, bool *result);

DSCError dsc_queue_front(const DSCQueue *queue, void *result);

DSCError dsc_queue_back(const DSCQueue *queue, void *result);

DSCError dsc_queue_push(DSCQueue *queue, void *data);

DSCError dsc_queue_pop(DSCQueue *queue, void *result);

#endif // DSC_QUEUE_H
