#include "pch.h"
#include "encoding_helper.h"
#include "block_id.h"

std::vector<uint8_t> EncodingHelper::CompressUShorts(
    std::array<uint16_t, VoxelConstants::VoxelMapSectionSize>& data) {

    auto rleCompressed = RLECompressUShorts(data);
    std::vector<uint8_t> bytes{};

    for(const auto& pair : rleCompressed) {
        uint16_t first = pair.first;
        uint16_t second = pair.second;

        bytes.push_back(static_cast<uint8_t>(first >> 8));
        bytes.push_back(static_cast<uint8_t>(first & 0xFF));
        bytes.push_back(static_cast<uint8_t>(second >> 8));
        bytes.push_back(static_cast<uint8_t>(second & 0xFF));
    }

    return bytes;
}


std::array<uint16_t, VoxelConstants::VoxelMapSectionSize> EncodingHelper::DecompressUShorts(
    std::vector<uint8_t>& compressed, std::unordered_set<uint16_t> allowedIDs) {

    std::vector<std::pair<uint16_t, uint16_t>> pairs{};

    for(size_t i = 0; i < compressed.size(); i += 4) {
        uint16_t first = (
            static_cast<uint16_t>(compressed[i]) << 8
        ) | compressed[i + 1];

        uint16_t second = (
            static_cast<uint16_t>(compressed[i + 2]) << 8
        ) | compressed[i + 3];

        pairs.emplace_back(first, second);
    }

    return RLEDecompressUShorts(pairs, allowedIDs);
}

std::vector<uint8_t> EncodingHelper::CompressBytes(
    std::array<uint8_t, VoxelConstants::VoxelMapSectionSize>& data) {

    auto rleCompressed = RLECompressBytes(data);
    std::vector<uint8_t> bytes;

    for(const auto& pair : rleCompressed) {
        uint16_t first = pair.first;
        uint16_t second = pair.second;

        bytes.push_back(static_cast<uint8_t>(first));
        bytes.push_back(static_cast<uint8_t>(second >> 8));
        bytes.push_back(static_cast<uint8_t>(second & 0xFF));
    }

    return bytes;
}


std::array<uint8_t, VoxelConstants::VoxelMapSectionSize> EncodingHelper::DecompressBytes(
    std::vector<uint8_t>& compressed) {

    std::vector<std::pair<uint8_t, uint16_t>> pairs{};

    for(size_t i = 0; i < compressed.size(); i += 3) {
        uint8_t first = compressed[i];

        uint16_t second = (
            static_cast<uint16_t>(compressed[i + 1]) << 8
        ) | compressed[i + 2];

        pairs.emplace_back(first, second);
    }

    return RLEDecompressBytes(pairs);
}

std::vector<std::pair<uint16_t, uint16_t>> EncodingHelper::RLECompressUShorts(
    std::array<uint16_t, VoxelConstants::VoxelMapSectionSize>& data) {

    std::vector<std::pair<uint16_t, uint16_t>> compressed{};

    if(data.empty()) {
        return compressed;
    }

    uint16_t currentValue = data[0];
    uint16_t count = 1;

    for(size_t i = 1; i < data.size(); i++) {
        if(data[i] == currentValue) {
            ++count;
        } 
    
        else {
            compressed.push_back({currentValue, count});
            currentValue = data[i];
            count = 1;
        }
    }

    compressed.push_back({currentValue, count});
    return compressed;
}

std::array<uint16_t, VoxelConstants::VoxelMapSectionSize> EncodingHelper::RLEDecompressUShorts(
    const std::vector<std::pair<uint16_t, uint16_t>>& compressed, std::unordered_set<uint16_t> allowedIDs) {

    std::array<uint16_t, VoxelConstants::VoxelMapSectionSize> decompressed{};
    size_t index = 0;

    for(const auto& pair : compressed) {
        auto key = pair.first;

        if(allowedIDs.count(BlockID::Convert(key)) < 1) {
            key = BlockID::PackEmpty();
        }

        for(uint16_t i = 0; i < pair.second; i++) {
            if(index >= decompressed.size()) {
                Log::Error(
                    "UShorts decompression exceeds the size of the array: " + 
                    std::to_string(index) + " >= " + 
                    std::to_string(decompressed.size())
                );

                break;
            }
                
            decompressed[index] = key;
            index++;
        }
    }

    return decompressed;
}

std::vector<std::pair<uint8_t, uint16_t>> EncodingHelper::RLECompressBytes(
    std::array<uint8_t, VoxelConstants::VoxelMapSectionSize>& data) {

    std::vector<std::pair<uint8_t, uint16_t>> compressed{};

    uint8_t currentValue = data[0];
    uint16_t count = 1;

    for(size_t i = 1; i < data.size(); i++) {
        if(data[i] == currentValue) {
            ++count;
        } 
    
        else {
            compressed.push_back({currentValue, count});
            currentValue = data[i];
            count = 1;
        }
    }

    compressed.push_back({currentValue, count});
    return compressed;
}

std::array<uint8_t, VoxelConstants::VoxelMapSectionSize> EncodingHelper::RLEDecompressBytes(
    const std::vector<std::pair<uint8_t, uint16_t>>& compressed) {

    std::array<uint8_t, VoxelConstants::VoxelMapSectionSize> decompressed{};
    size_t index = 0;

    for(const auto& pair : compressed) {
        for(uint16_t i = 0; i < pair.second; i++) {
            if(index >= decompressed.size()) {
                Log::Error(
                    "Bytes decompression exceeds the size of the array: " + 
                    std::to_string(index) + " >= " + 
                    std::to_string(decompressed.size())
                );

                break;
            }
                
            decompressed[index] = pair.first;
            index++;
        }
    }

    return decompressed;
}