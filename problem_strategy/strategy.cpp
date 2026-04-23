#include "strategy.hpp"
#include <iostream>
#include <memory>
using namespace std;


Logger::Logger() {}

void Logger::setStrategy(unique_ptr<ILoggingStrategy> strat) {
    strategy = move(strat);
}

Logger::Result Logger::log(const string& name, const string& data) {
    int rc =  strategy->onlog(name, data);
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
