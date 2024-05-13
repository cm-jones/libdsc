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

#ifndef DSC_STACK_H
#define DSC_STACK_H

#include "dsc_type.h"
#include "dsc_error.h"

#define DSC_STACK_INITIAL_CAPACITY 16

typedef struct DSCStack DSCStack;

DSCError dsc_stack_init(DSCStack *new_stack, DSCType type);

DSCError dsc_stack_deinit(DSCStack *stack);

DSCError dsc_stack_size(const DSCStack *stack, size_t *size);

DSCError dsc_stack_capacity(const DSCStack *stack, size_t *capacity);

DSCError dsc_stack_is_empty(const DSCStack *stack, bool *is_empty);

DSCError dsc_stack_top(const DSCStack *stack, void *top);

DSCError dsc_stack_push(DSCStack *stack, void *data);

DSCError dsc_stack_pop(DSCStack *stack, void *top);

#endif // DSC_STACK_H
