#pragma once

#include "pch.h"

struct PendingBlockState {
public:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    uint16_t voxel = 0;
    uint16_t previousVoxel = 0;

    bool spawnParticles = false;
    bool playSounds = false;
    bool dropItem = false;

    bool hasPriority = false;

    bool operator==(const PendingBlockState &other) const {
        return (
            other.x == x && 
            other.y == y && 
            other.z == z && 
            
            other.voxel == voxel && 
            other.previousVoxel == previousVoxel &&

            other.spawnParticles == spawnParticles &&
            other.playSounds == playSounds &&
            other.dropItem == dropItem &&

            other.hasPriority == hasPriority
        );
    }

    static size_t Hash(const PendingBlockState& obj) {
        std::size_t h = 0;
    
        h ^= std::hash<int32_t>{}(obj.x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.z) + 0x9e3779b9 + (h << 6) + (h >> 2);

        h ^= std::hash<int32_t>{}(obj.voxel) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.previousVoxel) + 0x9e3779b9 + (h << 6) + (h >> 2);

        h ^= std::hash<int32_t>{}(obj.spawnParticles) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.playSounds) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(obj.dropItem) + 0x9e3779b9 + (h << 6) + (h >> 2);
    
        h ^= std::hash<int32_t>{}(obj.hasPriority) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

struct PendingBlockStateHash {
    std::size_t operator()(const PendingBlockState& obj) const {
        return PendingBlockState::Hash(obj);
    }

    size_t hash(const PendingBlockState& obj) const {
        return PendingBlockState::Hash(obj);
    }

    bool equal(const PendingBlockState& a, const PendingBlockState& b) const {
        return a == b;
    }
};