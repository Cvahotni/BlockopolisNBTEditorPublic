#pragma once

#include "pch.h"

class Log {
public:
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
};