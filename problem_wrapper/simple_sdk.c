#include "simple_sdk.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int is_initialized = 0;
static int pending_count = 0;
static const int MAX_EVENTS = 100;

// Internal constructor - called automatically on first use
static void sdk_auto_init(void) {
    if (!is_initialized) {
        atexit(sdk_cleanup);
        pending_count = 0;
        is_initialized = 1;
        printf("[SDK] Auto-initialized\n");
    }
}

// Single simplified API function
sdk_result_t sdk_log(const char* name, const char* data) {
    // Auto-initialize on first use (constructor pattern)
    if (!is_initialized) {
        sdk_auto_init();
    }
    if (pending_count >= MAX_EVENTS) {
        return SDK_ERROR_QUEUE_FULL;
    }
    printf("[SDK] Logging: %s", name);
    if (data) {
        printf(" = %s", data);
    }
    printf("\n");
    if (rand() % 20 == 0) {
        return SDK_ERROR_NETWORK_FAILED;
    }
    pending_count++;
    if (pending_count > 0) {
        pending_count--;
    }
    return SDK_SUCCESS;
}

// Cleanup function (destructor - called automatically at exit)
void sdk_cleanup(void) {
    if (is_initialized) {
        printf("[SDK] Cleaning up... processed %d events total.\n", pending_count);
        is_initialized = 0;
        pending_count = 0;
    }
}
