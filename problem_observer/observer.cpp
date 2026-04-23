#include "observer.hpp"
#include "simple_sdk.h"
void Logger::addObserver(shared_ptr<ILogObserver> observer) {
    observers.push_back(observer);
}

Logger::Result Logger::log(const string& name , const string& data) {
    int rc = SDK_SUCCESS; // default
    for (auto& obs : observers) {
        int rc = obs->onLog(name, data);
    }
    return from_sdk_result(rc);
}

Logger::Result Logger::from_sdk_result(int sdkRes) {
    switch(sdkRes) {
        case SDK_SUCCESS: return Result::Success;
        case SDK_ERROR_NETWORK_FAILED: return Result::NetworkFailed;
        case SDK_ERROR_QUEUE_FULL: return Result::QueueFull;
        default: return Result::Unknown;
    }
}
