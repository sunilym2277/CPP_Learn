#include "observer.hpp"
#include <iostream>
using namespace std;

class ConsoleLogger : public ILogObserver {
    int id;
public :
    ConsoleLogger(int id) : id(id) {}
    int onLog(const string& name , const string& data) override {
        cout<<"[Console]"<< id;
        sdk_result_t rc = sdk_log(name.c_str(), data.empty() ? nullptr : data.c_str());
        return static_cast<int>(rc);
    }
};

class FileLogger : public ILogObserver {
public:
    int onLog(const string& name , const string& data) override {
        cout<<"[File]";
        sdk_result_t rc = sdk_log(name.c_str(), data.empty() ? nullptr : data.c_str());
        return static_cast<int>(rc);
    }
};

int main () 
{
    shared_ptr<ConsoleLogger> consolerLoggerPtr = make_shared<ConsoleLogger>(1);
    shared_ptr<ConsoleLogger> consolerLoggerPtr2 = make_shared<ConsoleLogger>(2);
    shared_ptr<ConsoleLogger> consolerLoggerPtr3 = make_shared<ConsoleLogger>(3);
    shared_ptr<FileLogger> fileLoggerPtr = make_shared<FileLogger>();

    Logger logger;
    logger.addObserver(consolerLoggerPtr);
    logger.addObserver(consolerLoggerPtr2);
    logger.addObserver(consolerLoggerPtr3);
    logger.addObserver(fileLoggerPtr);

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
