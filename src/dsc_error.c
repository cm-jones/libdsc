#include "../include/dsc_error.h"

// Global variable to store the last error code
static enum dsc_error_t last_error = DSC_ERROR_NONE;

enum dsc_error_t dsc_get_last_error() {
    return last_error;
}

void dsc_set_last_error(enum dsc_error_t error) {
    last_error = error;
}
