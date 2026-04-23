#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "simple_sdk.h"
using namespace std;

class ILogging {
public:
    virtual ~ILogging() = default;
    virtual int log(const string& name, const string& data) = 0;
};

//Concrete Logger: prints to console 
class ConsoleLogger : public ILogging {
public:
    int log(const string& name , const string& data) override {
        cout<<"[Console]"<<endl;
        sdk_result_t rc = sdk_log(name.c_str(),data.c_str());
        return static_cast<int>(rc);
    }
};

class FileLogger : public ILogging {
public:
    int log(const string& name , const string& data) override {
        cout<<"[File]"<<endl;
        sdk_result_t rc = sdk_log(name.c_str(),data.c_str());
        return static_cast<int>(rc);
    }
};

// Base decorator
class LoggerDecorator : public ILogging {
protected:
    shared_ptr<ILogging> wrappee;
public:
    LoggerDecorator(shared_ptr<ILogging> logger) : wrappee(logger) {}
};

class TimestampDecorator : public LoggerDecorator {
public:
    TimestampDecorator(shared_ptr<ILogging> logger) : LoggerDecorator(logger) {}
    int log(const string& name, const string& data) override {
        string newData = "Timestap " + data;
        return wrappee->log(name,newData);
    }
};