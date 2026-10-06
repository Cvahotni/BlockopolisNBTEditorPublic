#pragma once

#include "pch.h"

class ProtocolConstants {
public:
    static constexpr uint16_t ProtocolVersion = 0x00;

    static constexpr uint64_t UniversalSecretFirst = 6461023156136194470;
    static constexpr uint64_t UniversalSecretSecond = 1761893858735244653;

    static constexpr int32_t NetworkTimeoutMilliseconds = 3000;
    static constexpr uint32_t MaxChunksPerPacket = 4096;

    static constexpr uint32_t SimulationBufferSize = 40;
    static constexpr uint32_t SimulationBufferMaxSize = 64;

    static constexpr uint32_t MinMovementFramesCount = 3;

    static constexpr uint32_t MinUsernameCharCount = 3;
    static constexpr uint32_t MaxUsernameCharCount = 16;
};