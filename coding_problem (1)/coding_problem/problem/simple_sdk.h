#ifndef SIMPLE_SDK_H
#define SIMPLE_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

// Error codes
typedef enum {
    SDK_SUCCESS = 0,
    SDK_ERROR_NETWORK_FAILED = -1,
    SDK_ERROR_QUEUE_FULL = -2
} sdk_result_t;

// Examples:
//   sdk_log("user_login", "user_id=123")          // event with data
//   sdk_log("response_time", "45.6")              // metric
//   sdk_log("button_click", NULL)                 // simple event
sdk_result_t sdk_log(const char* name, const char* data);

// Cleanup function (called automatically at exit, but can be called manually)
void sdk_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif // SIMPLE_SDK_H
