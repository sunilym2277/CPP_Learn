#include "simple_sdk.h"
#include<iostream>
#include<string>
#include<memory>
#include<vector>
using namespace std;

// Observer interface 
class ILogObserver{
public:
    virtual ~ILogObserver() = default;
    virtual int onLog(const string& name , const string& data) = 0;
};

// Subject 
class Logger {
    vector<shared_ptr<ILogObserver>> observers;
public:
    enum class Result {
        Success = 0,
        NetworkFailed = 1,
        QueueFull = 2,
        Unknown = 3
    };
    void addObserver(shared_ptr<ILogObserver> observer);
    Result log(const string& name , const string& data);
private:
    static Result from_sdk_result(int sdkRes);
};
