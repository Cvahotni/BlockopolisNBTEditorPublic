#pragma once

#include "pch.h"

class Vector3Int {
public:
    Vector3Int() : x(0), y(0), z(0) {}
    Vector3Int(int32_t value) : x(value), y(value), z(value) {}
    Vector3Int(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z) {}

    int32_t X() const { 
        return x; 
    }

    int32_t Y() const { 
        return y; 
    }

    int32_t Z() const { 
        return z; 
    }

    uint32_t Level() const { 
        return level; 
    }

    void SetX(const int32_t _x) { 
        x = _x; 
    }

    void SetY(const int32_t _y) { 
        y = _y; 
    }

    void SetZ(const int32_t _z) { 
        z = _z; 
    }

    void SetLevel(const uint32_t _level) { 
        level = _level; 
    }

    void ModifyX(const int32_t _x) { 
        x += _x; 
    }

    void ModifyY(const int32_t _y) { 
        y += _y; 
    }

    void ModifyZ(const int32_t _z) { 
        z += _z; 
    }

    bool operator==(const Vector3Int &other) const {
        return (
            other.x == x && 
            other.y == y && 
            other.z == z
        );
    }

    bool operator!=(const Vector3Int &other) const {
        return (
            other.x != x ||
            other.y != y ||
            other.z != z
        );
    }

    bool operator<(const Vector3Int& other) const {
        if(x != other.x) return x < other.x;
        if(y != other.y) return y < other.y;

        return z < other.z;
    }

    Vector3Int operator+(Vector3Int& other) const {
        return {
            x + other.X(), 
            y + other.Y(), 
            z + other.Z()
        };
    }

    const Vector3Int operator+(const Vector3Int& other) const {
        return {
            x + other.X(), 
            y + other.Y(), 
            z + other.Z()
        };
    }

    Vector3Int operator-(Vector3Int& other) const {
        return {
            x - other.X(), 
            y - other.Y(), 
            z - other.Z()
        };
    }

    const Vector3Int operator-(const Vector3Int& other) const {
        return {
            x - other.X(), 
            y - other.Y(), 
            z - other.Z()
        };
    }

    Vector3Int operator*(Vector3Int& other) const {
        return {
            x * other.X(), 
            y * other.Y(), 
            z * other.Z()
        };
    }

    Vector3Int operator*(double scalar) const {
        return {
            x * (int32_t) scalar, 
            y * (int32_t) scalar, 
            z * (int32_t) scalar
        };
    }

    Vector3Int operator/(Vector3Int& other) const {
        return {
            x / other.X(), 
            y / other.Y(), 
            z / other.Z()
        };
    }

    Vector3Int operator/(double divider) const {
        return {
            x / (int32_t) divider, 
            y / (int32_t) divider, 
            z / (int32_t) divider
        };
    }

    Vector3Int& operator+=(Vector3Int& other) {
        x += other.X();
        y += other.Y();
        z += other.Z();

        return *this;
    }

    Vector3Int& operator-=(Vector3Int& other) {
        x -= other.X();
        y -= other.Y();
        z -= other.Z();

        return *this;
    }

    Vector3Int& operator*=(Vector3Int& other) {
        x *= other.X();
        y *= other.Y();
        z *= other.Z();

        return *this;
    }

    Vector3Int& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    Vector3Int& operator/=(Vector3Int& other) {
        x /= other.X();
        y /= other.Y();
        z /= other.Z();

        return *this;
    }

    Vector3Int& operator/=(double divider) {
        x /= divider;
        y /= divider;
        z /= divider;

        return *this;
    }

    double Distance(Vector3Int other) {
        return sqrt(
            pow(abs(static_cast<double>(x - other.X())), 2.0) + 
            pow(abs(static_cast<double>(y - other.Y())), 2.0) +
            pow(abs(static_cast<double>(z - other.Z())), 2.0)
        );
    };

    std::string ToString() {
        return (
            std::to_string(x) + ", " + 
            std::to_string(y) + ", " + 
            std::to_string(z) + ", " + 
            std::to_string(level)
        );
    }

private:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint32_t level = 0;
};

struct Vector3IntHash {
    std::size_t operator()(const Vector3Int& obj) const {
        std::size_t h = 0;

        h ^= std::hash<int32_t>{}(obj.X()) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.Y()) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.Z()) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<uint32_t>{}(obj.Level()) + 0x9e3779b9 + (h << 6) + (h >> 2);

        return h;
    }
};