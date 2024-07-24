// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DSC_UTILS
#define DSC_UTILS

#include <stddef.h>
#include <stdint.h>

#include "dsc_error.h"
#include "dsc_type.h"

uint32_t dsc_hash(void *key, DSCType key_type, size_t capacity);

#endif  // DSC_UTILS
