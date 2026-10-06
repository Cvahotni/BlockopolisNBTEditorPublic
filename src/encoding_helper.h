#pragma once

#include "pch.h"

#include "voxel_constants.h"
#include "log.h"

class EncodingHelper {
public:
    static std::vector<uint8_t> CompressUShorts(
        std::array<uint16_t, VoxelConstants::VoxelMapSectionSize>& data);

    static std::array<uint16_t, VoxelConstants::VoxelMapSectionSize> DecompressUShorts(
        std::vector<uint8_t>& compressed, std::unordered_set<uint16_t> allowedIDs);

    static std::vector<uint8_t> CompressBytes(
        std::array<uint8_t, VoxelConstants::VoxelMapSectionSize>& data);

    static std::array<uint8_t, VoxelConstants::VoxelMapSectionSize> DecompressBytes(
        std::vector<uint8_t>& compressed);

    static std::vector<std::pair<uint16_t, uint16_t>> RLECompressUShorts(
        std::array<uint16_t, VoxelConstants::VoxelMapSectionSize>& data);

    static std::array<uint16_t, VoxelConstants::VoxelMapSectionSize> RLEDecompressUShorts(
        const std::vector<std::pair<uint16_t, uint16_t>>& compressed, std::unordered_set<uint16_t> allowedIDs);

    static std::vector<std::pair<uint8_t, uint16_t>> RLECompressBytes(
        std::array<uint8_t, VoxelConstants::VoxelMapSectionSize>& data);

    static std::array<uint8_t, VoxelConstants::VoxelMapSectionSize> RLEDecompressBytes(
        const std::vector<std::pair<uint8_t, uint16_t>>& compressed);
};