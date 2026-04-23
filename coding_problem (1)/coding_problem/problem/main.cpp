#include "Logger.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Concrete implementation of ISimpleSDK using your existing C SDK
class SimpleSDKWrapper : public ISimpleSDK {
public:
    int init() override {
        // Optional: call sdk_auto_init() if needed
        return 0; 
    }

    int log_event(const std::string& name, const std::string& data) override {
        sdk_result_t rc = sdk_log(name.c_str(), data.empty() ? nullptr : data.c_str());
        return static_cast<int>(rc);
    }

    void cleanup() override {
        sdk_cleanup();
    }
};

int main() {
    auto sdk = std::make_shared<SimpleSDKWrapper>();
    Logger logger(sdk);


    cout << "=== Analytics SDK Demo ===\n" << endl;

    cout << "--- Logging Examples ---" << endl;

    // Store events and metrics in a vector
    vector<pair<string, string>> logs = {
        {"user_login", "user_id=12345"},
        {"page_view", "page=dashboard"},
        {"button_click", ""},           // empty string → no data
        {"response_time_ms", "156.7"},
        {"cpu_usage_percent", "23.4"},
        {"memory_usage_mb", "512.0"}
    };

    // Loop through them
    for (const auto& [name, data] : logs) 
    {
        Logger::Result result = logger.log(name, data);
    
        // Handle the result
        switch(result) 
        {
            case Logger::Result::Success:
                 std::cout << name << " logged successfully.\n";
                 break;
            case Logger::Result::NetworkFailed:
                 std::cout << name << " failed due to network.\n";
                 break;
            case Logger::Result::QueueFull:
                 std::cout << name << " could not be logged: queue full.\n";
                 break;
            case Logger::Result::Unknown:
            default:
                 std::cout << name << " logging result unknown.\n";
        }
    }

    cout << "\n--- That's it! ---\n" << endl;
    cout << "=== Demo completed! ===" << endl;

    return 0;
}
