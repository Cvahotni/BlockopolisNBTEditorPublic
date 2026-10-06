#pragma once

#include "pch.h"

#include "pending_block_state.h"
#include "coord.h"

class DispatchedBlockState {
public:
    void PushRelativeChunkCoord(ChunkCoord _chunkCoord) {
        relativeChunkCoords.push_back(_chunkCoord);
    }

    std::vector<ChunkCoord>& RelativeChunkCoordsRaw() {
        return relativeChunkCoords;
    }
    
    void PushChunkCoord(ChunkCoord _chunkCoord) {
        chunkCoords.push_back(_chunkCoord);
    }

    std::vector<ChunkCoord>& ChunkCoordsRaw() {
        return chunkCoords;
    }

    void PushOriginalChunkCoord(ChunkCoord _chunkCoord) {
        originalChunkCoords.push_back(_chunkCoord);
    }

    std::vector<ChunkCoord>& OriginalChunkCoordsRaw() {
        return originalChunkCoords;
    }

    void PushPendingBlockState(PendingBlockState _pendingBlockState) {
        pendingBlockStates.push_back(_pendingBlockState);
    }

    void PopPendingBlockState() {
        pendingBlockStates.pop_front();
    }

    PendingBlockState PendingBlockStatesFront() {
        return pendingBlockStates.front();
    }

    bool IsPendingBlockStatesEmpty() {
        return pendingBlockStates.empty();
    }

    size_t PendingBlockStatesCount() {
        return pendingBlockStates.size();
    }

    void SetPendingBlockStates(std::deque<PendingBlockState>& _pendingBlockStates) {
        pendingBlockStates = _pendingBlockStates;
    }

    std::deque<PendingBlockState>& PendingBlockStatesRaw() {
        return pendingBlockStates;
    }

    bool HasPriority() {
        for(auto state : pendingBlockStates) {
            if(state.hasPriority) {
                return true;
            }
        }

        return false;
    }

    bool operator==(DispatchedBlockState blockState) const {
        return (
            pendingBlockStates == blockState.pendingBlockStates &&
            chunkCoords == blockState.chunkCoords
        );
    }

private:
    std::deque<PendingBlockState> pendingBlockStates{};

    std::vector<ChunkCoord> chunkCoords{};
    std::vector<ChunkCoord> originalChunkCoords{};
    std::vector<ChunkCoord> relativeChunkCoords{};
};