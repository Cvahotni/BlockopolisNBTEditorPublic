#pragma once

#include "pch.h"

class FeatureInstance {
public:
    FeatureInstance() {}

    FeatureInstance(int32_t _x, int32_t _y, int32_t _z, uint8_t _f) :
        x(_x), y(_y), z(_z), f(_f) {}

    int32_t X() const {
        return x;
    }

    int32_t Y() const {
        return y;
    }

    int32_t Z() const {
        return z;
    }

    int32_t F() const {
        return f;
    }

    void SetX(int32_t _x) {
        x = _x;
    }

    void SetY(int32_t _y) {
        y = _y;
    }

    void SetZ(int32_t _z) {
        z = _z;
    }

    void SetF(int32_t _f) {
        f = _f;
    }

    bool operator==(const FeatureInstance &other) const noexcept {
        return other.x == x && other.y == y && other.z == z && other.f == f;
    }

private:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint8_t f = 0;
};

struct FeatureInstanceHash {
    std::size_t operator()(const FeatureInstance& obj) const {
        std::size_t h = 0;

        h ^= std::hash<int32_t>{}(obj.X()) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.Y()) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.Z()) + 0x9e3779b9 + (h << 6) + (h >> 2);

        return h;
    }
};