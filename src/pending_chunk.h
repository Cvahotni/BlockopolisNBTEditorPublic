#pragma once

#include "pch.h"

#include "coord.h"
#include "voxel_constants.h"

struct PendingChunk {
public:
    ChunkCoord coord{};

    std::vector<std::vector<uint8_t>> voxelBytes{};
    std::vector<std::vector<uint8_t>> lightBytes{};
    std::array<uint8_t, VoxelConstants::BiomeMapSize> biomeBytes{};

    bool biomesBuilt = false;
    bool voxelsBuilt = false;
    bool featuresPlaced = false;
    bool lightBaked = false;
    bool wasPreviouslySaved = false;
    bool finished = false;
};