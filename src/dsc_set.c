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

#include <stdlib.h>
#include <stdbool.h>

#include "../include/dsc_set.h"

struct dsc_set_t *dsc_set_create()
{
    return NULL;
}

enum dsc_error_t dsc_set_destroy(struct dsc_set_t *set)
{
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_add(struct dsc_set_t *set, int value)
{
    return DSC_ERROR_NONE;
}

enum dsc_error_t dsc_set_remove(struct dsc_set_t *set, int value)
{
    return DSC_ERROR_NONE;
}

bool dsc_set_contains(struct dsc_set_t *set, int value)
{
    return false;
}

int dsc_set_get_size(struct dsc_set_t *set)
{
    return 0;
}

bool dsc_set_is_empty(struct dsc_set_t *set)
{
    return false;
}

enum dsc_error_t dsc_set_clear(struct dsc_set_t *set)
{
    return DSC_ERROR_NONE;
}
