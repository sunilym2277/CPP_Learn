#include "Logger.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;
// Mock SDK implementation
class MockSimpleSDK : public ISimpleSDK {
public:
    MOCK_METHOD(int, log_event, (const string& name,const string& data),(override));
};

class LoggerIntegrationTest : public ::testing::Test {
protected:
    shared_ptr<MockSimpleSDK> mockSdk;
    Logger logger;
    LoggerIntegrationTest() : mockSdk(std::make_shared<MockSimpleSDK>()),logger(mockSdk) {}
    
};

// Test: LogsSuccessfully
TEST_F(LoggerIntegrationTest, LogsSuccessfully) {
    EXPECT_CALL(*mockSdk, log_event("user_login", "id=123"))
        .Times(1)
        .WillOnce(::testing::Return(SDK_SUCCESS));

    auto result = logger.log("user_login", "id=123");
    EXPECT_EQ(result, Logger::Result::Success);
}

// Test: HandlesQueueFull
TEST_F(LoggerIntegrationTest, HandlesQueueFull) {
    EXPECT_CALL(*mockSdk, log_event("event", "data"))
        .Times(1000)
        .WillRepeatedly(::testing::Return(SDK_SUCCESS));

    EXPECT_CALL(*mockSdk, log_event("event_overflow", "too much"))
        .Times(1)
        .WillOnce(::testing::Return(SDK_ERROR_QUEUE_FULL));

    for (int i = 0; i < 1000; i++) {
        logger.log("event", "data");
    }
    auto result = logger.log("event_overflow", "too much");
    EXPECT_EQ(result, Logger::Result::QueueFull);
}

// Test: HandlesNetworkFailure
TEST_F(LoggerIntegrationTest, HandlesNetworkFailure) {
    EXPECT_CALL(*mockSdk, log_event("network_test", "simulate failure"))
        .Times(1)
        .WillOnce(::testing::Return(SDK_ERROR_NETWORK_FAILED));

    auto result = logger.log("network_test", "simulate failure");
    EXPECT_EQ(result, Logger::Result::NetworkFailed);
}
