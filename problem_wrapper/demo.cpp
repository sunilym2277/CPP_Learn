#include "simple_sdk.h"
#include <iostream>

int main() {
    std::cout << "=== Analytics SDK Demo ===" << std::endl;

    // That's it! No initialization needed - constructor runs automatically
    std::cout << "\n--- Logging Examples ---" << std::endl;

    // Log events with data
    if (sdk_log("user_login", "user_id=12345") == SDK_SUCCESS) {
        std::cout << "✓ Logged user login event" << std::endl;
    }

    if (sdk_log("page_view", "page=dashboard") == SDK_SUCCESS) {
        std::cout << "✓ Logged page view event" << std::endl;
    }

    // Log simple events (no data)
    if (sdk_log("button_click", nullptr) == SDK_SUCCESS) {
        std::cout << "✓ Logged button click event" << std::endl;
    }

    // Log metrics (as strings)
    if (sdk_log("response_time_ms", "156.7") == SDK_SUCCESS) {
        std::cout << "✓ Logged response time metric" << std::endl;
    }

    if (sdk_log("cpu_usage_percent", "23.4") == SDK_SUCCESS) {
        std::cout << "✓ Logged CPU usage metric" << std::endl;
    }

    if (sdk_log("memory_usage_mb", "512.0") == SDK_SUCCESS) {
        std::cout << "✓ Logged memory usage metric" << std::endl;
    }

    std::cout << "\n--- That's it! ---" << std::endl;
    std::cout << "\n=== Demo completed! ===" << std::endl;

    // No cleanup needed - sdk_cleanup() is called automatically via atexit()
    return 0;
}