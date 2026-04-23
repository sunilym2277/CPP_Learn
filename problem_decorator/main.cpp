#include "decorator.hpp"
#include <memory>

int main() {
    auto consoleLogger = std::make_shared<ConsoleLogger>();
    auto fileLogger = std::make_shared<FileLogger>();

    // Add timestamp decorator to console logger
    auto decoratedConsole = std::make_shared<TimestampDecorator>(consoleLogger);

    decoratedConsole->log("user_login", "user_id=12345");
    fileLogger->log("page_view", "page=dashboard");

    return 0;
}
