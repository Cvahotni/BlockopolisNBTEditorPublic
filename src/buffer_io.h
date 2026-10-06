#pragma once

#include "pch.h"

#include "vector3.h"
#include "global_defines.h"
#include "coord.h"
#include "item_action.h"
#include "item_stack.h"
#include "inventory_constants.h"
#include "pending_block_state.h"
#include "dispatched_block_state.h"
#include "game_mode_type.h"
#include "nbt.h"
#include "aabb.h"
#include "sound_types.h"
#include "inventory_types.h"
#include "pending_chunk.h"
#include "log.h"

class BufferIO {
public:
    template<typename T>
    static void WriteToBuffer(std::vector<uint8_t>& buffer, const T& value) {
        const uint8_t* data = reinterpret_cast<const uint8_t*>(&value);
        buffer.insert(buffer.end(), data, data + sizeof(T));
    }

    template<typename T>
    static void ReadFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, T& value) {
        if(sizeof(T) + offset > buffer.size()) {
            Log::Warning(
                "Overflow detected when trying to read from buffer: " + 
                std::to_string(sizeof(T) + offset) + 
                " > " + 
                std::to_string(buffer.size())
            );
            
            offset += sizeof(T);
            return;
        }

        std::memcpy(&value, buffer.data() + offset, sizeof(T));
        offset += sizeof(T);
    }
    
    static void WriteBoolToBuffer(std::vector<uint8_t>& buffer, bool value);
    static void WriteStringToBuffer(std::vector<uint8_t>& buffer, const std::string& str);
    static void WriteVector3ToBuffer(std::vector<uint8_t>& buffer, Vector3 value);
    static void WriteByteListToBuffer(std::vector<uint8_t>& buffer, std::vector<uint8_t>& list);
    static void WriteByteArrayToBuffer(std::vector<uint8_t>& buffer, std::array<uint8_t, VoxelConstants::BiomeMapSize>& array);
    static void WriteChunkCoordToBuffer(std::vector<uint8_t>& buffer, ChunkCoord& coord);
    static void WritePendingChunkToBuffer(std::vector<uint8_t>& buffer, PendingChunk& chunk);
    static void WriteItemStackToBuffer(std::vector<uint8_t>& buffer, ItemStack stack);
    static void WriteInventoryDataToBuffer(std::vector<uint8_t>& buffer, std::unordered_map<uint32_t, ItemStack> data);
    static void WriteInventoryChangesToBuffer(std::vector<uint8_t>& buffer, std::vector<ItemAction> actions);
    static void WritePendingBlockStateToBuffer(std::vector<uint8_t>& buffer, PendingBlockState state);
    static void WriteDispatchedBlockStatesToBuffer(std::vector<uint8_t>& buffer, std::vector<DispatchedBlockState> states);
    static void WriteGameModeTypeToBuffer(std::vector<uint8_t>& buffer, GameModeType gameModeType);
    static void WriteSoundTypeToBuffer(std::vector<uint8_t>& buffer, SoundType soundType);
    static void WriteInventoryScreenTypeToBuffer(std::vector<uint8_t>& buffer, InventoryScreenType screenType);
    static void WriteNBTToBuffer(std::vector<uint8_t>& buffer, NBT nbt);
    static void WriteAABBToBuffer(std::vector<uint8_t>& buffer, AABB aabb);

    static void ReadStringFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::string& str);
    static void ReadBoolFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, bool& value);
    static void ReadVector3romBuffer(const std::vector<uint8_t>& buffer, size_t& offset, Vector3& vector);
    static void ReadByteListFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<uint8_t>& list);
    static void ReadByteArrayFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::array<uint8_t, VoxelConstants::BiomeMapSize>& array);
    static void ReadChunkCoordFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, ChunkCoord& coord);
    static void ReadPendingChunkFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, PendingChunk& chunk);
    static void ReadItemStackFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, ItemStack& stack);
    static void ReadInventoryDataFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::unordered_map<uint32_t, ItemStack>& data);
    static void ReadInventoryChangesFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<ItemAction>& actions);
    static void ReadPendingBlockStateFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, PendingBlockState& state);
    static void ReadDispatchedBlockStatesFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<DispatchedBlockState>& states);
    static void ReadGameModeTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, GameModeType& gameModeType);
    static void ReadSoundTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, SoundType& soundType);
    static void ReadInventoryScreenTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, InventoryScreenType& screenType);
    static void ReadNBTFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, NBT& nbt);
    static void ReadAABBFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, AABB& aabb);
};