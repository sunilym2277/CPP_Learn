#pragma once
#include "simple_sdk.h"
#include <string>
#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>

class ISimpleSDK { // To Mock classes
public:
    virtual ~ISimpleSDK() = default;

    // Initialize the SDK
    virtual int init() = 0;

    // Log an event (name + optional data)
    virtual int log_event(const std::string& name, const std::string& data) = 0;

    // Cleanup resources
    virtual void cleanup() = 0;
};


class Logger {
public:
    enum class Result {
        Success = 0,
        NetworkFailed = 1,
        QueueFull = 2,
        Unknown = 3
    };

    // Constructor takes any implementation of ISimpleSDK
    explicit Logger(std::shared_ptr<ISimpleSDK> sdk);
    ~Logger();
    Result log(const std::string& name, const std::string& data = "");

private:
    static Result from_sdk_result(int sdkRes);

    std::shared_ptr<ISimpleSDK> sdk_;
};
