#pragma once
#include "simple_sdk.h"
#include <string>
#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>
using namespace std;

class ISimpleSDK {
public:
    virtual ~ISimpleSDK() = default;
    virtual int log_event(const string& name, const string& data) = 0;
};

class Logger {
public:
    enum class Result {
        Success = 0,
        NetworkFailed = 1,
        QueueFull = 2,
        Unknown = 3
    };

    Logger(shared_ptr<ISimpleSDK> sdk);
    ~Logger();
    Result log(const string& name, const string& data = "");

private:
    static Result from_sdk_result(int sdkRes);
    shared_ptr<ISimpleSDK> sdk_;
    mutable mutex mtx_;
};
