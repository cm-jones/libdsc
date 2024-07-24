// SPDX-License-Identifier: GPL-3.0-or-later

#include "../include/dsc_type.h"

bool dsc_type_invalid(DSCType type) {
    return type <= DSC_TYPE_UNKNOWN || type >= DSC_TYPE_COUNT;
}
