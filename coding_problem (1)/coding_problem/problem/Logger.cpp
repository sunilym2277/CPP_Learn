#include "Logger.hpp"
#include "simple_sdk.h"  // for sdk_log
#include <mutex>
#include <iostream>

Logger::Logger(std::shared_ptr<ISimpleSDK> sdk)  : sdk_(std::move(sdk)) 
{
    if (sdk_) { sdk_->init(); }
}
Logger::~Logger() {
    if (sdk_) { sdk_->cleanup(); }
}

Logger::Result Logger::log(const std::string& name, const std::string& data) {
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
