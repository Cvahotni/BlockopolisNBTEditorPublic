#pragma once

#include "pch.h"

#include "voxel_constants.h"

class ChunkCoord {
public:
    ChunkCoord() : x(0), z(0) {}
    ChunkCoord(int32_t _x, int32_t _z) : x(_x), z(_z) {}

    int32_t X() const { 
        return x; 
    }

    int32_t Z() const { 
        return z; 
    }

    uint32_t Level() const {
        return level;
    }

    void SetX(int32_t _x) { 
        x = _x; 
    }

    void SetZ(int32_t _z) {
        z = _z; 
    }

    void SetLevel(uint32_t _level) {
        level = _level;
    }

    static int32_t WorldX(ChunkCoord coord) { 
        return coord.X() << VoxelConstants::ChunkBitShift; 
    }

    static int32_t WorldZ(ChunkCoord coord) { 
        return coord.Z() << VoxelConstants::ChunkBitShift; 
    }

    static ChunkCoord FromPosition(const double x, const double z) { 
        return ChunkCoord{
            (int32_t) x >> VoxelConstants::ChunkBitShift,
            (int32_t) z >> VoxelConstants::ChunkBitShift
        };
    };

    static ChunkCoord FromBlockPos(const int32_t x, const int32_t z) { 
        return ChunkCoord{
            x >> VoxelConstants::ChunkBitShift,
            z >> VoxelConstants::ChunkBitShift
        };
    };

    static double Distance(ChunkCoord a, ChunkCoord b) {
        return std::sqrt(
            std::pow((static_cast<double>(b.X()) - static_cast<double>(a.X())), 2) + 
            std::pow((static_cast<double>(b.Z()) - static_cast<double>(a.Z())), 2)
        );
    }

    static ChunkCoord Modify(ChunkCoord coord, int32_t x, int32_t z) { 
        return ChunkCoord{
            coord.X() + x, 
            coord.Z() + z
        };
    }

    static size_t Hash(ChunkCoord coord) { 
        size_t h1 = std::hash<int32_t>()(coord.X());
        size_t h2 = std::hash<int32_t>()(coord.Z());

        return h1 ^ (h2 + 0x9e3779b974a7c15ULL + (h1 << 6) + (h1 >> 2)) + coord.Level();
    }

    bool operator==(const ChunkCoord &other) const noexcept {
        return other.x == x && other.z == z && other.level == level;
    }

    bool operator!=(const ChunkCoord &other) const {
        return other.x != x || other.z != z || other.level != level;
    }

    std::size_t operator()(const ChunkCoord &key) const {
        return Hash(key);
    }

    bool operator<(const ChunkCoord& other) const {
        if(x != other.x) {
            return x < other.x;
        }

        return z < other.z;
    }

    std::string ToString() {
        return (
            std::to_string(x) + ", " + 
            std::to_string(z) + ", " +
            std::to_string(level)
        );
    }

private:
    int32_t x = 0;
    int32_t z = 0;
    uint32_t level = 0;
};

struct ChunkCoordHash {
    std::size_t operator()(const ChunkCoord& obj) const noexcept {
        return ChunkCoord::Hash(obj);
    }

    size_t hash(const ChunkCoord& obj) const {
        return ChunkCoord::Hash(obj);
    }

    bool equal(const ChunkCoord& coord1, const ChunkCoord& coord2) const {
        return coord1 == coord2;
    }
};

class RegionCoord {
public:
    RegionCoord() : x(0), z(0) {}
    RegionCoord(int32_t _x, int32_t _z) : x(_x), z(_z) {}

    int32_t X() { 
        return x; 
    }

    int32_t Z() { 
        return z; 
    }

    uint32_t Level() {
        return level;
    }

    void SetX(int32_t _x) { 
        x = _x; 
    }

    void SetZ(int32_t _z) { 
        z = _z; 
    }

    void SetLevel(uint32_t _level) {
        level = _level;
    }

    static int32_t WorldX(RegionCoord coord) { 
        return coord.X() << VoxelConstants::RegionBitShift; 
    }

    static int32_t WorldZ(RegionCoord coord) { 
        return coord.Z() << VoxelConstants::RegionBitShift; 
    }

    static RegionCoord FromPosition(const double x, const double z) { 
        return RegionCoord{
            (int32_t) x >> VoxelConstants::RegionBitShift,
            (int32_t) z >> VoxelConstants::RegionBitShift
        };
    }

    static RegionCoord FromBlockPos(const int32_t x, const int32_t z) { 
        return RegionCoord{
            x >> VoxelConstants::RegionBitShift,
            z >> VoxelConstants::RegionBitShift
        };
    }

    static double Distance(RegionCoord a, RegionCoord b) {
        return std::sqrt(std::pow((b.X() - a.X()), 2) + std::pow((b.Z() - a.Z()), 2));
    }

    static RegionCoord Modify(RegionCoord coord, int32_t x, int32_t z) { 
        return RegionCoord{
            coord.X() + x, 
            coord.Z() + z
        }; 
    }

    static int32_t Hash(RegionCoord coord) { 
        return coord.X() + coord.Z() * 1000000;
    }

    bool operator==(const RegionCoord &other) const {
        return other.x == x && other.z == z && other.level == level;
    }

    bool operator!=(const RegionCoord &other) const {
        return other.x != x || other.z != z || other.level != level;
    }

    std::size_t operator()(const RegionCoord &key) const {
        return Hash(key);
    }

    bool operator<(const RegionCoord& other) const {
        if(x != other.x) {
            return x < other.x;
        }

        return z < other.z;
    }

    std::string ToString() {
        return (
            std::to_string(x) + ", " +
            std::to_string(z) + ", " +
            std::to_string(level)
        );
    }

private:
    int32_t x = 0;
    int32_t z = 0;
    uint32_t level = 0;
};

struct RegionCoordHash {
    std::size_t operator()(const RegionCoord& obj) const {
        return RegionCoord::Hash(obj);
    }
};

class ChunkSectionCoord {
public:
    ChunkSectionCoord() : x(0), y(0), z(0) {}
    ChunkSectionCoord(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z) {}

    int32_t X() const { 
        return x; 
    }

    int32_t Y() const {
        return y;
    }

    int32_t Z() const { 
        return z; 
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

    static int32_t WorldX(ChunkSectionCoord coord) { 
        return coord.X() << VoxelConstants::ChunkBitShift; 
    }

    static int32_t WorldY(ChunkSectionCoord coord) { 
        return coord.Y() << VoxelConstants::ChunkBitShift; 
    }

    static int32_t WorldZ(ChunkSectionCoord coord) { 
        return coord.Z() << VoxelConstants::ChunkBitShift; 
    }

    static ChunkSectionCoord FromPosition(const double x, const double y, const double z) { 
        return ChunkSectionCoord{
            (int32_t) x >> VoxelConstants::ChunkBitShift,
            (int32_t) y >> VoxelConstants::ChunkBitShift,
            (int32_t) z >> VoxelConstants::ChunkBitShift
        };
    };

    static ChunkSectionCoord FromBlockPos(const int32_t x, const int32_t y, const int32_t z) { 
        return ChunkSectionCoord{
            x >> VoxelConstants::ChunkBitShift,
            y >> VoxelConstants::ChunkBitShift,
            z >> VoxelConstants::ChunkBitShift
        };
    };

    static double Distance(ChunkSectionCoord a, ChunkSectionCoord b) {
        return std::sqrt(
            std::pow((static_cast<double>(b.X()) - static_cast<double>(a.X())), 2) + 
            std::pow((static_cast<double>(b.Y()) - static_cast<double>(a.Y())), 2) + 
            std::pow((static_cast<double>(b.Z()) - static_cast<double>(a.Z())), 2)
        );
    }

    static ChunkSectionCoord Modify(ChunkSectionCoord coord, int32_t x, int32_t y, int32_t z) { 
        return ChunkSectionCoord{
            coord.X() + x, 
            coord.Y() + y, 
            coord.Z() + z
        };
    }

    static size_t Hash(ChunkSectionCoord coord) {
        //Get a better hash function, please!

        return (
            coord.X() * 1000000 +
            coord.Y() * 2222 +
            coord.Z()
        );
    }

    static uint64_t SecureHash(ChunkSectionCoord coord) {
        uint64_t seed = (
            (uint64_t) coord.X() * 73856093ull ^
            (uint64_t) coord.Y() * 19349663ull ^
            (uint64_t) coord.Z() * 83492791ull
        );

        seed ^= (seed >> 30); seed *= 0xbf58476d1ce4e5b9ull;
        seed ^= (seed >> 27); seed *= 0x94d049bb133111ebull;
        seed ^= (seed >> 31);

        return seed;
    }

    bool operator==(const ChunkSectionCoord &other) const {
        return other.x == x && other.y == y && other.z == z;
    }

    bool operator!=(const ChunkSectionCoord &other) const {
        return other.x != x || other.y != y || other.z != z;
    }

    std::size_t operator()(const ChunkSectionCoord &key) const {
        return Hash(key);
    }

    bool operator<(const ChunkSectionCoord& other) const {
        if(x != other.x) {
            return x < other.x;
        }

        if(y != other.y) {
            return y < other.y;
        }

        return z < other.z;
    }

    std::string ToString() {
        return (
            std::to_string(x) + ", " + 
            std::to_string(y) + ", " + 
            std::to_string(z)
        );
    }

private:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
};

struct ChunkSectionCoordHash {
    std::size_t operator()(const ChunkSectionCoord& obj) const {
        return ChunkSectionCoord::Hash(obj);
    }

    size_t hash(const ChunkSectionCoord& obj) const {
        return ChunkSectionCoord::Hash(obj);
    }

    bool equal(const ChunkSectionCoord& coord1, const ChunkSectionCoord& coord2) const {
        return coord1 == coord2;
    }
};

class Coord {
public:
    static ChunkCoord FromRegionCoord(RegionCoord coord) {
        return ChunkCoord{
            (coord.X() << VoxelConstants::RegionBitShift) >> VoxelConstants::ChunkBitShift,
            (coord.Z() << VoxelConstants::RegionBitShift) >> VoxelConstants::ChunkBitShift
        };
    }

    static RegionCoord FromChunkCoord(ChunkCoord coord) {
        return RegionCoord{
            (coord.X() << VoxelConstants::ChunkBitShift) >> VoxelConstants::RegionBitShift,
            (coord.Z() << VoxelConstants::ChunkBitShift) >> VoxelConstants::RegionBitShift
        };
    }

    static bool CheckChunkCoord(ChunkCoord chunkCoord, RegionCoord regionCoord) {
        ChunkCoord fromRegionCoord = FromRegionCoord(regionCoord);

        return (
            chunkCoord.X() >= fromRegionCoord.X() && chunkCoord.X() <= (fromRegionCoord.X() + VoxelConstants::RegionWidth) &&
            chunkCoord.Z() >= fromRegionCoord.Z() && chunkCoord.Z() <= (fromRegionCoord.Z() + VoxelConstants::RegionWidth)
        );
    }
};