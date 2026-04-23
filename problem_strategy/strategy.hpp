#pragma once
#include <iostream>
#include <memory>
#include "simple_sdk.h"
using namespace std;

class ILoggingStrategy {
public:
    virtual ~ILoggingStrategy() = default;
    virtual int onlog(const string& name , const string& data) = 0;
};

class ConsoleLogger : public ILoggingStrategy {
    int onlog(const string& name, const string& data) override {
        cout<<"[Console]";
        sdk_result_t rc = sdk_log(name.c_str(), data.c_str());
        return static_cast<int>(rc);
    }
};

class FileLogger : public ILoggingStrategy {
public:
    int onlog(const string& name, const string& data) override {
        cout<<"[File]";
        sdk_result_t rc = sdk_log(name.c_str(), data.c_str());
        return static_cast<int>(rc);
    }
};


class Logger {
    unique_ptr<ILoggingStrategy> strategy;

public:
    enum class Result {
        Success = 0,
        NetworkFailed = 1,
        QueueFull = 2,
        Unknown = 3
    };
    Logger();
    void setStrategy(unique_ptr<ILoggingStrategy> strat);
    Result log(const string& name, const string& data);
    static Result from_sdk_result(int sdkRes);
};