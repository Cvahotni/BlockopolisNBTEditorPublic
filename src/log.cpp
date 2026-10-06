#include "pch.h"
#include "log.h"

void Log::Info(const std::string& message) {
    std::cout << message << std::endl;
}

void Log::Warning(const std::string& message) {
    std::cout << message << std::endl;
}

void Log::Error(const std::string& message) {
    std::cout << message << std::endl;
}