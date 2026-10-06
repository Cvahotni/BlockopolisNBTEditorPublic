#pragma once

#include "pch.h"

struct CommittedBlock {
public:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint16_t block = 0;

    bool shouldPlaySound = false;
    bool shouldSpawnParticles = false;
    bool shouldDrop = false;

    bool operator==(const CommittedBlock &other) const {
        return (
            other.x == x && 
            other.y == y && 
            other.z == z && 
            other.block == block && 
            other.shouldPlaySound == shouldPlaySound && 
            other.shouldSpawnParticles == shouldSpawnParticles && 
            other.shouldDrop == shouldDrop
        );
    }

    static size_t Hash(const CommittedBlock& c) {
        std::size_t h1 = std::hash<int32_t>()(c.x);
        std::size_t h2 = std::hash<int32_t>()(c.y);
        std::size_t h3 = std::hash<int32_t>()(c.z);
        std::size_t h4 = std::hash<uint8_t>()(c.block);

        std::size_t seed = h1;

        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        return seed;
    }
};

struct CommittedBlockHash {
    std::size_t operator()(const CommittedBlock& c) const {
        return CommittedBlock::Hash(c);
    }

    size_t hash(const CommittedBlock& obj) const {
        return CommittedBlock::Hash(obj);
    }

    bool equal(const CommittedBlock& a, const CommittedBlock& b) const {
        return a == b;
    }
};

struct CommittedBlockBehaviour {
public:
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint8_t b = 0;

    bool operator==(const CommittedBlockBehaviour &other) const {
        return other.x == x && other.y == y && other.z == z && other.b == b;
    }

    static size_t Hash(const CommittedBlockBehaviour &other) {
        std::size_t h1 = std::hash<int32_t>()(other.x);
        std::size_t h2 = std::hash<int32_t>()(other.y);
        std::size_t h3 = std::hash<int32_t>()(other.z);
        std::size_t h4 = std::hash<uint8_t>()(other.b);

        std::size_t seed = h1;

        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= h4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        return seed;
    }
};

struct CommittedBlockBehaviourHash {
    std::size_t operator()(const CommittedBlockBehaviour& c) const {
        return CommittedBlockBehaviour::Hash(c);
    }

    size_t hash(const CommittedBlockBehaviour& obj) const {
        return CommittedBlockBehaviour::Hash(obj);
    }

    bool equal(const CommittedBlockBehaviour& a, const CommittedBlockBehaviour& b) const {
        return a == b;
    }
};