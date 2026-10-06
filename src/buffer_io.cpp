#include "pch.h"
#include "buffer_io.h"
#include "encoding_helper.h"
#include "protocol_constants.h"

void BufferIO::WriteBoolToBuffer(std::vector<uint8_t>& buffer, bool value) {
    uint8_t byteValue = static_cast<uint8_t>(value);
    WriteToBuffer(buffer, byteValue);
}

void BufferIO::WriteStringToBuffer(std::vector<uint8_t>& buffer, const std::string& str) {
    uint32_t length = static_cast<uint32_t>(str.size());

    WriteToBuffer(buffer, length);
    buffer.insert(buffer.end(), str.begin(), str.end());
}

void BufferIO::WriteVector3ToBuffer(std::vector<uint8_t>& buffer, Vector3 value) {
    BufferIO::WriteToBuffer(buffer, value.X());
    BufferIO::WriteToBuffer(buffer, value.Y());
    BufferIO::WriteToBuffer(buffer, value.Z());
    BufferIO::WriteToBuffer(buffer, value.Level());
}

void BufferIO::WriteByteListToBuffer(std::vector<uint8_t>& buffer, std::vector<uint8_t>& list) {
    uint32_t length = static_cast<uint32_t>(list.size());

    WriteToBuffer(buffer, length);
    buffer.insert(buffer.end(), list.begin(), list.end());
}

void BufferIO::WriteByteArrayToBuffer(std::vector<uint8_t>& buffer, std::array<uint8_t, VoxelConstants::BiomeMapSize>& array) {
    for(auto byte : array) {
        BufferIO::WriteToBuffer(buffer, byte);
    }
}

void BufferIO::WriteChunkCoordToBuffer(std::vector<uint8_t>& buffer, ChunkCoord& coord) {
    BufferIO::WriteToBuffer(buffer, coord.X());
    BufferIO::WriteToBuffer(buffer, coord.Z());
    BufferIO::WriteToBuffer(buffer, coord.Level());
}

void BufferIO::WritePendingChunkToBuffer(std::vector<uint8_t>& buffer, PendingChunk& chunk) {
    WriteChunkCoordToBuffer(buffer, chunk.coord);
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(std::max(chunk.voxelBytes.size(), chunk.lightBytes.size())));

    for(int32_t y = 0; y < VoxelConstants::ChunkSectionCountInChunk; y++) {
        if(y >= chunk.voxelBytes.size() || y >= chunk.lightBytes.size()) {
            continue;
        }

        WriteByteListToBuffer(buffer, chunk.voxelBytes[y]);
        WriteByteListToBuffer(buffer, chunk.lightBytes[y]);
    }

    WriteByteArrayToBuffer(buffer, chunk.biomeBytes);
    
    BufferIO::WriteBoolToBuffer(buffer, chunk.biomesBuilt);
    BufferIO::WriteBoolToBuffer(buffer, chunk.voxelsBuilt);
    BufferIO::WriteBoolToBuffer(buffer, chunk.lightBaked);
    BufferIO::WriteBoolToBuffer(buffer, chunk.featuresPlaced);
    BufferIO::WriteBoolToBuffer(buffer, chunk.finished);
}

void BufferIO::WriteItemStackToBuffer(std::vector<uint8_t>& buffer, ItemStack stack) {
    BufferIO::WriteToBuffer(buffer, stack.ID());
    BufferIO::WriteToBuffer(buffer, stack.Amount());
}

void BufferIO::WriteInventoryDataToBuffer(std::vector<uint8_t>& buffer, std::unordered_map<uint32_t, ItemStack> data) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(data.size()));

    for(auto pair : data) {
        auto slot = pair.first;
        auto stack = pair.second;

        BufferIO::WriteToBuffer(buffer, slot);
        WriteItemStackToBuffer(buffer, stack);
    }
}

void BufferIO::WriteInventoryChangesToBuffer(std::vector<uint8_t>& buffer, std::vector<ItemAction> actions) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(actions.size()));
    
    for(auto action : actions) {
        auto type = action.type;

        auto fromSlot = action.fromSlot;
        auto toSlot = action.toSlot;

        auto fromSlotType = action.fromSlotType;
        auto toSlotType = action.toSlotType;

        auto stack = action.stack;

        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(type));

        BufferIO::WriteToBuffer(buffer, fromSlot);
        BufferIO::WriteToBuffer(buffer, toSlot);

        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(fromSlotType));
        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(toSlotType));

        BufferIO::WriteItemStackToBuffer(buffer, stack);
    }
}

void BufferIO::WritePendingBlockStateToBuffer(std::vector<uint8_t>& buffer, PendingBlockState state) {
    BufferIO::WriteToBuffer(buffer, state.x);
    BufferIO::WriteToBuffer(buffer, state.y);
    BufferIO::WriteToBuffer(buffer, state.z);

    BufferIO::WriteToBuffer(buffer, state.voxel);
    BufferIO::WriteToBuffer(buffer, state.previousVoxel);

    BufferIO::WriteBoolToBuffer(buffer, state.playSounds);
    BufferIO::WriteBoolToBuffer(buffer, state.spawnParticles);
}

void BufferIO::WriteDispatchedBlockStatesToBuffer(std::vector<uint8_t>& buffer, std::vector<DispatchedBlockState> states) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(states.size()));

    for(auto state : states) {
        auto pendingStatesRaw = state.PendingBlockStatesRaw();
        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(pendingStatesRaw.size()));

        for(auto value : pendingStatesRaw) {
            WritePendingBlockStateToBuffer(buffer, value);
        }

        auto chunkCoordsRaw = state.ChunkCoordsRaw();
        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(chunkCoordsRaw.size()));

        for(auto value : chunkCoordsRaw) {
            WriteChunkCoordToBuffer(buffer, value);
        }

        auto originalChunkCoordsRaw = state.OriginalChunkCoordsRaw();
        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(originalChunkCoordsRaw.size()));

        for(auto value : originalChunkCoordsRaw) {
            WriteChunkCoordToBuffer(buffer, value);
        }

        auto relativeChunkCoordsRaw = state.RelativeChunkCoordsRaw();
        BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(relativeChunkCoordsRaw.size()));

        for(auto value : relativeChunkCoordsRaw) {
            WriteChunkCoordToBuffer(buffer, value);
        }
    }
}

void BufferIO::WriteGameModeTypeToBuffer(std::vector<uint8_t>& buffer, GameModeType gameModeType) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(gameModeType));
}

void BufferIO::WriteSoundTypeToBuffer(std::vector<uint8_t>& buffer, SoundType soundType) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(soundType));
}

void BufferIO::WriteInventoryScreenTypeToBuffer(std::vector<uint8_t>& buffer, InventoryScreenType screenType) {
    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(screenType));
}

void BufferIO::WriteNBTToBuffer(std::vector<uint8_t>& buffer, NBT nbt) {
    std::vector<uint8_t> rawNBTData{};
    nbt.WriteToVector(rawNBTData);

    BufferIO::WriteToBuffer(buffer, static_cast<uint32_t>(rawNBTData.size()));

    for(auto byte : rawNBTData) {
        BufferIO::WriteToBuffer(buffer, byte);
    }
}

void BufferIO::WriteAABBToBuffer(std::vector<uint8_t>& buffer, AABB aabb) {
    BufferIO::WriteVector3ToBuffer(buffer, aabb.min);
    BufferIO::WriteVector3ToBuffer(buffer, aabb.max);
    BufferIO::WriteVector3ToBuffer(buffer, aabb.pos);
    BufferIO::WriteVector3ToBuffer(buffer, aabb.size);
}

void BufferIO::ReadBoolFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, bool& value) {
    uint8_t byteValue = 0;
    ReadFromBuffer(buffer, offset, byteValue);

    value = static_cast<bool>(byteValue);
}

void BufferIO::ReadStringFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::string& str) {
    uint32_t length = 0;
    ReadFromBuffer(buffer, offset, length);

    if(length + offset > buffer.size()) {
        Log::Warning(
            "Overflow detected when trying to read string from buffer: " + 
            std::to_string(length + offset) + 
            " > " + 
            std::to_string(buffer.size())
        );
            
        offset += length;
        return;
    }

    str.assign(reinterpret_cast<const char*>(buffer.data() + offset), length);
    offset += length;
}

void BufferIO::ReadVector3romBuffer(const std::vector<uint8_t>& buffer, size_t& offset, Vector3& vector) {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    uint32_t i = 0;

    BufferIO::ReadFromBuffer(buffer, offset, x);
    BufferIO::ReadFromBuffer(buffer, offset, y);
    BufferIO::ReadFromBuffer(buffer, offset, z);
    BufferIO::ReadFromBuffer(buffer, offset, i);

    vector = Vector3{x, y, z};
    vector.SetLevel(i);
}

void BufferIO::ReadByteListFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<uint8_t>& list) {
    uint32_t length = 0;
    ReadFromBuffer(buffer, offset, length);

    if(length + offset > buffer.size()) {
        Log::Warning(
            "Overflow detected when trying to read byte list from buffer: " + 
            std::to_string(length + offset) + 
            " > " + 
            std::to_string(buffer.size())
        );
            
        offset += length;
        return;
    }

    list.insert(list.begin(), buffer.begin() + offset, buffer.begin() + offset + length);
    offset += length;
}

void BufferIO::ReadByteArrayFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::array<uint8_t, VoxelConstants::BiomeMapSize>& array) {
    for(size_t i = 0; i < array.size(); i++) {
        uint8_t byte = 0;
        BufferIO::ReadFromBuffer(buffer, offset, byte);

        array[i] = byte;
    }
}

void BufferIO::ReadChunkCoordFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, ChunkCoord& coord) {
    int32_t x = 0;
    int32_t z = 0;
    uint32_t i = 0;

    BufferIO::ReadFromBuffer(buffer, offset, x);
    BufferIO::ReadFromBuffer(buffer, offset, z);
    BufferIO::ReadFromBuffer(buffer, offset, i);

    coord.SetX(x);
    coord.SetZ(z);
    coord.SetLevel(i);
}

void BufferIO::ReadPendingChunkFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, PendingChunk& chunk) {
    ReadChunkCoordFromBuffer(buffer, offset, chunk.coord);

    int32_t sectionsSize = 0;
    BufferIO::ReadFromBuffer(buffer, offset, sectionsSize);

    for(int32_t y = 0; y < sectionsSize; y++) {
        std::vector<uint8_t> compressedVoxelMap{};
        std::vector<uint8_t> compressedLightMap{};

        ReadByteListFromBuffer(buffer, offset, compressedVoxelMap);
        ReadByteListFromBuffer(buffer, offset, compressedLightMap);

        chunk.voxelBytes.push_back(compressedVoxelMap);
        chunk.lightBytes.push_back(compressedLightMap);
    }

    std::array<uint8_t, VoxelConstants::BiomeMapSize> uncompressedBiomeMap{};
    ReadByteArrayFromBuffer(buffer, offset, uncompressedBiomeMap);

    chunk.biomeBytes = uncompressedBiomeMap;

    BufferIO::ReadBoolFromBuffer(buffer, offset, chunk.biomesBuilt);
    BufferIO::ReadBoolFromBuffer(buffer, offset, chunk.voxelsBuilt);
    BufferIO::ReadBoolFromBuffer(buffer, offset, chunk.lightBaked);
    BufferIO::ReadBoolFromBuffer(buffer, offset, chunk.featuresPlaced);
    BufferIO::ReadBoolFromBuffer(buffer, offset, chunk.finished);
}

void BufferIO::ReadItemStackFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, ItemStack& stack) {
    uint16_t id = 0;
    uint16_t amount = 0;

    BufferIO::ReadFromBuffer(buffer, offset, id);
    BufferIO::ReadFromBuffer(buffer, offset, amount);

    stack.SetID(id);
    stack.SetAmount(amount);
}

void BufferIO::ReadInventoryDataFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::unordered_map<uint32_t, ItemStack>& data) {
    uint32_t size = 0;
    BufferIO::ReadFromBuffer(buffer, offset, size);

    for(uint32_t i = 0; i < size; i++) {
        uint32_t slot = 0;
        ItemStack stack{};

        BufferIO::ReadFromBuffer(buffer, offset, slot);
        ReadItemStackFromBuffer(buffer, offset, stack);

        data.emplace(slot, stack);
    }
}

void BufferIO::ReadInventoryChangesFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<ItemAction>& actions) {
    uint32_t size = 0;
    BufferIO::ReadFromBuffer(buffer, offset, size);

    for(uint32_t i = 0; i < size; i++) {
        uint32_t type = 0;

        uint32_t fromSlot = 0;
        uint32_t toSlot = 0;

        uint32_t fromSlotType = 0;
        uint32_t toSlotType = 0;

        ItemStack stack{};

        BufferIO::ReadFromBuffer(buffer, offset, type);

        BufferIO::ReadFromBuffer(buffer, offset, fromSlot);
        BufferIO::ReadFromBuffer(buffer, offset, toSlot);

        BufferIO::ReadFromBuffer(buffer, offset, fromSlotType);
        BufferIO::ReadFromBuffer(buffer, offset, toSlotType);

        BufferIO::ReadItemStackFromBuffer(buffer, offset, stack);

        if(type >= ItemActionType::ItemActionTypesSize) {
            Log::Warning(
                "Skipping over an item whilst reading packet, expected an action type index of below " + 
                std::to_string(ItemActionType::ItemActionTypesSize) + 
                ", but got " + 
                std::to_string(type) + 
                " instead"
            );

            continue;
        }

        if(fromSlotType >= ItemSlotType::ItemSlotTypesSize || toSlotType >= ItemSlotType::ItemSlotTypesSize) {
            Log::Warning(
                "Skipping over an item whilst reading packet, expected a slot type index of below " + 
                std::to_string(ItemSlotType::ItemSlotTypesSize) + 
                ", but got " + 
                std::to_string(fromSlotType) + 
                ", and " + 
                std::to_string(toSlotType) + 
                " instead"
            );

            continue;
        }

        actions.push_back({
            static_cast<ItemActionType>(type),

            fromSlot,
            toSlot,

            static_cast<ItemSlotType>(fromSlotType),
            static_cast<ItemSlotType>(toSlotType),

            stack
        });
    }
}

void BufferIO::ReadPendingBlockStateFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, PendingBlockState& state) {
    BufferIO::ReadFromBuffer(buffer, offset, state.x);
    BufferIO::ReadFromBuffer(buffer, offset, state.y);
    BufferIO::ReadFromBuffer(buffer, offset, state.z);

    BufferIO::ReadFromBuffer(buffer, offset, state.voxel);
    BufferIO::ReadFromBuffer(buffer, offset, state.previousVoxel);

    BufferIO::ReadBoolFromBuffer(buffer, offset, state.playSounds);
    BufferIO::ReadBoolFromBuffer(buffer, offset, state.spawnParticles);
}

void BufferIO::ReadDispatchedBlockStatesFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, std::vector<DispatchedBlockState>& states) {
    uint32_t statesSize = 0;
    BufferIO::ReadFromBuffer(buffer, offset, statesSize);

    for(uint32_t i = 0; i < statesSize; i++) {
        DispatchedBlockState dispatchedState{};

        uint32_t pendingStatesSize = 0;
        BufferIO::ReadFromBuffer(buffer, offset, pendingStatesSize);

        for(uint32_t j = 0; j < pendingStatesSize; j++) {
            PendingBlockState pendingState{};
            ReadPendingBlockStateFromBuffer(buffer, offset, pendingState);

            dispatchedState.PushPendingBlockState(pendingState);
        }

        uint32_t chunkCoordsSize = 0;
        BufferIO::ReadFromBuffer(buffer, offset, chunkCoordsSize);

        for(uint32_t j = 0; j < chunkCoordsSize; j++) {
            ChunkCoord coord{};
            ReadChunkCoordFromBuffer(buffer, offset, coord);

            dispatchedState.PushChunkCoord(coord);
        }

        uint32_t originalChunkCoordsSize = 0;
        BufferIO::ReadFromBuffer(buffer, offset, originalChunkCoordsSize);

        for(uint32_t j = 0; j < originalChunkCoordsSize; j++) {
            ChunkCoord coord{};
            ReadChunkCoordFromBuffer(buffer, offset, coord);

            dispatchedState.PushOriginalChunkCoord(coord);
        }

        uint32_t relativeChunkCoordsSize = 0;
        BufferIO::ReadFromBuffer(buffer, offset, relativeChunkCoordsSize);

        for(uint32_t j = 0; j < relativeChunkCoordsSize; j++) {
            ChunkCoord coord{};
            ReadChunkCoordFromBuffer(buffer, offset, coord);

            dispatchedState.PushRelativeChunkCoord(coord);
        }

        states.push_back(dispatchedState);
    }
}

void BufferIO::ReadGameModeTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, GameModeType& gameModeType) {
    uint32_t index = 0;
    BufferIO::ReadFromBuffer(buffer, offset, index);

    if(index >= GameModeType::GameModeTypeCount) {
        Log::Warning(
            "Read an invalid game mode type index: " + 

            std::to_string(index) + " >= " + 
            std::to_string(GameModeType::GameModeTypeCount)
        );
    
        return;
    }

    gameModeType = static_cast<GameModeType>(index);
}

void BufferIO::ReadSoundTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, SoundType& soundType) {
    uint32_t index = 0;
    BufferIO::ReadFromBuffer(buffer, offset, index);

    if(index >= SoundType::SoundTypeCount) {
        Log::Warning(
            "Read an invalid sound type type index: " + 

            std::to_string(index) + " >= " + 
            std::to_string(SoundType::SoundTypeCount)
        );
    
        return;
    }

    soundType = static_cast<SoundType>(index);
}

void BufferIO::ReadInventoryScreenTypeFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, InventoryScreenType& screenType) {
    uint32_t index = 0;
    BufferIO::ReadFromBuffer(buffer, offset, index);

    if(index >= InventoryScreenType::InventoryScreenTypeCount) {
        Log::Warning(
            "Read an invalid inventory screen type index: " + 

            std::to_string(index) + " >= " + 
            std::to_string(InventoryScreenType::InventoryScreenTypeCount)
        );
    
        return;
    }

    screenType = static_cast<InventoryScreenType>(index);
}

void BufferIO::ReadNBTFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, NBT& nbt) {
    uint32_t rawNBTDataSize = 0;
    BufferIO::ReadFromBuffer(buffer, offset, rawNBTDataSize);

    std::vector<uint8_t> rawNBTData{};

    for(auto i = 0; i < rawNBTDataSize; i++) {
        uint8_t byte = 0;
        BufferIO::ReadFromBuffer(buffer, offset, byte);

        rawNBTData.push_back(byte);
    }

    nbt.ReadFromVector(rawNBTData);
}

void BufferIO::ReadAABBFromBuffer(const std::vector<uint8_t>& buffer, size_t& offset, AABB& aabb) {
    BufferIO::ReadVector3romBuffer(buffer, offset, aabb.min);
    BufferIO::ReadVector3romBuffer(buffer, offset, aabb.max);
    BufferIO::ReadVector3romBuffer(buffer, offset, aabb.pos);
    BufferIO::ReadVector3romBuffer(buffer, offset, aabb.size);
}