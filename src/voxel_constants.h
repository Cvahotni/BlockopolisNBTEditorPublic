#pragma once

#include "pch.h"

class VoxelConstants {
public:
    static constexpr int32_t ChunkWidth = 16;
	static constexpr int32_t ChunkHeight = 256;

	static constexpr int32_t ChunkSectionCountInChunk = 16;

	static constexpr int32_t ChunkWidthHalf = 8;
	static constexpr int32_t ChunkWidthQuater = 4;

	static constexpr int32_t ChunkHeightHalf = 128;

    static constexpr int32_t ChunkBitShift = 4;
	static constexpr int32_t RegionBitShift = 8;

	static constexpr int32_t RegionWidth = 16;
	static constexpr int32_t TerrainHeight = 128;

	static constexpr int32_t ChunkScanMaxX = ChunkWidth * 3;
	static constexpr int32_t ChunkScanMaxY = ChunkHeight;
	static constexpr int32_t ChunkScanMaxZ = ChunkWidth * 3;

	static constexpr double MaximumWorldBorderX = 134217728.0;
	static constexpr double MaximumWorldBorderZ = 134217728.0;

	static constexpr uint32_t ChunkStatusWidth = 5;
	static constexpr int32_t ChunkStatusWidthBuffer = 2;
	static constexpr uint32_t ChunkStatusSize = ChunkStatusWidth * ChunkStatusWidth;

	static constexpr uint32_t ChunkScanOffset = ChunkWidth * 1;
	static constexpr uint32_t ChunkScanOffsetHalf = ChunkWidthHalf * 1;

	static constexpr uint8_t FaceCountPerBlock = 6;
	static constexpr uint32_t BlockModelRuleCount = 16;

	static constexpr uint32_t ChunkScanAmountXYZ = (
		(VoxelConstants::ChunkScanMaxX) * 
		(VoxelConstants::ChunkScanMaxY) * 
		(VoxelConstants::ChunkScanMaxZ)
	);

	static constexpr uint32_t ChunkScanAmountXZ = (
		(VoxelConstants::ChunkScanMaxX) * 
		(VoxelConstants::ChunkScanMaxZ)
	);

	static constexpr uint8_t FaceLookups[4][6] = {
        {0, 1, 2, 3, 4, 5},
		{4, 5, 2, 3, 1, 0},
        {1, 0, 2, 3, 5, 4},
        {5, 4, 2, 3, 0, 1}
    };

	static constexpr uint8_t ReverseFaceLookups[6] = {
		1, 0, 3, 2, 5, 4
    };

	static constexpr int32_t ChunkNeighborCount = 8;
	static constexpr int32_t ChunkBlockBufferSize = 2;
	static constexpr int32_t LocalChunkCount = ChunkNeighborCount + 1;

	static constexpr uint32_t TrackedLightMaximum = ChunkScanAmountXYZ;
	static constexpr int32_t ReservedThreadCount = LocalChunkCount * 16;

	static constexpr int32_t ViewDistanceBuffer = 3;
	static constexpr int32_t ExtendedViewDistanceBuffer = ViewDistanceBuffer + 3;

	static constexpr uint32_t TextureAtlasWidthInBlocks = 16;
	static constexpr int32_t PackedMultiplier = 16;

    static constexpr uint32_t VoxelMapSize = ChunkWidth * ChunkHeight * ChunkWidth;
	static constexpr uint32_t LightMapSize = ChunkWidth * ChunkHeight * ChunkWidth;
	static constexpr uint32_t BiomeMapSize = ChunkWidth * ChunkWidth;

	static constexpr uint32_t VoxelMapSectionSize = ChunkWidth * ChunkWidth * ChunkWidth;
	static constexpr uint32_t LightMapSectionSize = ChunkWidth * ChunkWidth * ChunkWidth;

	static constexpr uint32_t MaxLightLevel = 15;
	static constexpr uint32_t MaxAmbientOcclusionLightLevel = 15 - 1;
	static constexpr uint32_t MaxLightScanRadius = 7 + 1;
	static constexpr uint32_t LightFalloff = 2;

	static constexpr uint8_t MaxWaterLevel = 7;
	static constexpr double WaterLevelMultiplier = 0.125;

	static constexpr uint32_t MaxAnimatedBlockTextures = 4 + 1;
	static constexpr uint32_t FeaturePriorityLimit = 8;

	static constexpr uint32_t NoiseMapWidth = 16;
	static constexpr uint32_t NoiseMapHeight = 128;
	static constexpr uint32_t NoiseMapSize = NoiseMapWidth * NoiseMapHeight * NoiseMapWidth;
	static constexpr uint32_t NoiseMapFlatWidthExtended = 16 + 2;
	static constexpr uint32_t NoiseMapFlatWidthExtendedOffset = 1;
	static constexpr uint32_t NoiseMapFlatWidthExtendedAmount = NoiseMapFlatWidthExtended * NoiseMapFlatWidthExtended;

	static constexpr uint32_t NoiseMapQuaterWidth = 4 + 1;
	static constexpr uint32_t NoiseMapQuaterHeight = 16;
	static constexpr uint32_t NoiseMapQuaterSize = NoiseMapQuaterWidth * NoiseMapQuaterHeight * NoiseMapQuaterWidth;

	static constexpr int32_t NoiseMapQuaterMultiplierXZ = 4;
	static constexpr int32_t NoiseMapQuaterMultiplierY = 8;

	static constexpr int32_t ChunkBuilderCountMax = ReservedThreadCount + 64;

	static constexpr uint32_t FeatureLengthOnAxis = 32;
	static constexpr uint32_t FeatureArraySize = FeatureLengthOnAxis * FeatureLengthOnAxis * FeatureLengthOnAxis;

	static constexpr double MinTrueLight = 0.15;
	static constexpr double MaxTrueLight = 1.0;
	static constexpr double MaxNaturalLight = 1.0;
	static constexpr double BrightnessMultiplierSky = 0.65;
	static constexpr double BrightnessMultiplierGround = 0.45;
};