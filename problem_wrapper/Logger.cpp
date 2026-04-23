#include "Logger.hpp"
#include "simple_sdk.h"
#include <mutex>
#include <iostream>

Logger::Logger(shared_ptr<ISimpleSDK> sdk)  : sdk_(move(sdk)) { }

Logger::~Logger() { }

Logger::Result Logger::log(const string& name, const string& data) {
    lock_guard<mutex> lock(mtx_);
    if (!sdk_) return Result::Unknown;

    int rc = sdk_->log_event(name, data);
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
