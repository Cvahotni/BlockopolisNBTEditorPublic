#pragma once

#include "pch.h"
#include "vector3int.h"

class Vector3 {
public:
    Vector3() {}
    Vector3(double value) : vectorX(value), vectorY(value), vectorZ(value) {}
    Vector3(double _x, double _y, double _z) : vectorX(_x), vectorY(_y), vectorZ(_z) {}
    
    double X() { 
        return vectorX; 
    }

    double Y() { 
        return vectorY; 
    }

    double Z() { 
        return vectorZ; 
    }

    uint32_t Level() {
        return level;
    }
    
    void SetX(const double x) { 
        vectorX = x; 
    }

    void SetY(const double y) { 
        vectorY = y; 
    }

    void SetZ(const double z) { 
        vectorZ = z; 
    }

    void SetLevel(const uint32_t _level) {
        level = _level;
    }

    void ModifyX(const double x) { 
        vectorX += x; 
    }

    void ModifyY(const double y) { 
        vectorY += y; 
    }

    void ModifyZ(const double z) { 
        vectorZ += z; 
    }

    bool operator==(Vector3 other) const {
        return (
            vectorX == other.X() &&
            vectorY == other.Y() &&
            vectorZ == other.Z()
        ) && level == other.level;
    }

    bool operator!=(Vector3 other) const {
        return (
            vectorX != other.X() ||
            vectorY != other.Y() ||
            vectorZ != other.Z()
        ) || level != other.Level();
    }

    Vector3 operator+(Vector3 other) const {
        return {
            vectorX + other.X(), 
            vectorY + other.Y(), 
            vectorZ + other.Z()
        };
    }

    Vector3 operator-(Vector3 other) const {
        return {
            vectorX - other.X(), 
            vectorY - other.Y(), 
            vectorZ - other.Z()
        };
    }

    Vector3 operator*(Vector3 other) const {
        return {
            vectorX * other.X(), 
            vectorY * other.Y(), 
            vectorZ * other.Z()
        };
    }

    Vector3 operator*(double scalar) const {
        return {
            vectorX * scalar, 
            vectorY * scalar, 
            vectorZ * scalar
        };
    }

    Vector3 operator/(Vector3 other) const {
        return {
            vectorX / other.X(), 
            vectorY / other.Y(), 
            vectorZ / other.Z()
        };
    }

    Vector3 operator/(double divider) const {
        return {
            vectorX / divider, 
            vectorY / divider, 
            vectorZ / divider
        };
    }

    Vector3 operator+=(Vector3 other) {
        vectorX += other.X();
        vectorY += other.Y();
        vectorZ += other.Z();

        return *this;
    }

    Vector3 operator-=(Vector3 other) {
        vectorX -= other.X();
        vectorY -= other.Y();
        vectorZ -= other.Z();

        return *this;
    }

    Vector3 operator+=(Vector3Int other) {
        vectorX += static_cast<double>(other.X());
        vectorY += static_cast<double>(other.Y());
        vectorZ += static_cast<double>(other.Z());

        return *this;
    }

    Vector3 operator-=(Vector3Int other) {
        vectorX -= static_cast<double>(other.X());
        vectorY -= static_cast<double>(other.Y());
        vectorZ -= static_cast<double>(other.Z());

        return *this;
    }

    Vector3 operator*=(Vector3Int other) {
        vectorX *= static_cast<double>(other.X());
        vectorY *= static_cast<double>(other.Y());
        vectorZ *= static_cast<double>(other.Z());

        return *this;
    }

    Vector3 operator/=(Vector3Int other) {
        vectorX /= static_cast<double>(other.X());
        vectorY /= static_cast<double>(other.Y());
        vectorZ /= static_cast<double>(other.Z());

        return *this;
    }

    Vector3 operator+(Vector3Int other) const {
        return {
            vectorX + static_cast<double>(other.X()), 
            vectorY + static_cast<double>(other.Y()), 
            vectorZ + static_cast<double>(other.Z())
        };
    }

    Vector3 operator-(Vector3Int other) const {
        return {
            vectorX - static_cast<double>(other.X()), 
            vectorY - static_cast<double>(other.Y()), 
            vectorZ - static_cast<double>(other.Z())
        };
    }

    Vector3 operator*(Vector3Int other) const {
        return {
            vectorX * static_cast<double>(other.X()), 
            vectorY * static_cast<double>(other.Y()), 
            vectorZ * static_cast<double>(other.Z())
        };
    }

    Vector3 operator/(Vector3Int other) const {
        return {
            vectorX / static_cast<double>(other.X()), 
            vectorY / static_cast<double>(other.Y()), 
            vectorZ / static_cast<double>(other.Z())
        };
    }

    Vector3 operator*=(Vector3 other) {
        vectorX *= other.X();
        vectorY *= other.Y();
        vectorZ *= other.Z();

        return *this;
    }

    Vector3 operator*=(double scalar) {
        vectorX *= scalar;
        vectorY *= scalar;
        vectorZ *= scalar;

        return *this;
    }

    Vector3 operator/=(Vector3 other) {
        vectorX /= other.X();
        vectorY /= other.Y();
        vectorZ /= other.Z();

        return *this;
    }

    Vector3 operator/=(double divider) {
        vectorX /= divider;
        vectorY /= divider;
        vectorZ /= divider;

        return *this;
    }

    Vector3 operator-() const {
        return Vector3{
            -vectorX,
            -vectorY,
            -vectorZ
        };
    }

    double Distance(Vector3 other) {
        return sqrt(
            std::pow(std::abs(vectorX - other.X()), 2.0) + 
            std::pow(std::abs(vectorY - other.Y()), 2.0) +
            std::pow(std::abs(vectorZ - other.Z()), 2.0)
        );
    };

    double SecondaryDistance(Vector3 other) {
        double dX = std::abs(other.X() - vectorX);
        double dY = std::abs(other.Y() - vectorY);
        double dZ = std::abs(other.Z() - vectorZ);

        return std::sqrt(dX * dX + dY * dY + dZ * dZ);
    }

    double HorizontalDistance(Vector3 other) {
        Vector3 first = {vectorX, 0.0, vectorZ};
        Vector3 second = {other.X(), 0.0, other.Z()};

        return first.Distance(second);
    }

    double Dot(Vector3 normal) {
        return (
            vectorX * normal.X() + 
            vectorY * normal.Y() + 
            vectorZ * normal.Z()
        );
    }

    double Length() {
        return sqrt(
            vectorX * vectorX + 
            vectorY * vectorY +
            vectorZ * vectorZ
        );
    }

    double LengthSquared() {
        return (
            std::pow(vectorX, 2) + 
            std::pow(vectorY, 2) + 
            std::pow(vectorZ, 2)
        );
    }

    double MaxComponent() {
        return std::max(vectorY, std::max(vectorX, vectorZ));
    }

    static Vector3 Normalize(Vector3& vector) {
        double length = sqrt(
            vector.X() * vector.X() + 
            vector.Y() * vector.Y() + 
            vector.Z() * vector.Z()
        );

        if(length > 0.0) {
            return Vector3(
                vector.X() / length, 
                vector.Y() / length, 
                vector.Z() / length
            );
        } 

        else {
            return vector;
        }
    }   

    std::string ToString() {
        return (
            std::to_string(vectorX) + ", " + 
            std::to_string(vectorY) + ", " + 
            std::to_string(vectorZ) + ", " +
            std::to_string(level)
        );
    }
    
private:
    double vectorX = 0.0;
    double vectorY = 0.0;
    double vectorZ = 0.0;
    
    uint32_t level = 0;
};