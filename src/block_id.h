#pragma once

#include "pch.h"

class BlockID {
public:
    static uint16_t Pack(const uint8_t id, const uint8_t rotation, const uint8_t variant) {
        return (rotation << 14) | (variant << 11) | (id << 0);
    }
    
    static uint16_t PackEmpty() { 
        return Pack(0, 0, 0); 
    }

    static uint8_t ID(const uint16_t packed) { 
        return (packed >> 0) & 0x7FF;
    }

    static uint8_t Rotation(const uint16_t packed) { 
        return (packed >> 14) & 0x3;
    }

    static uint8_t Variant(const uint16_t packed) {
        return (packed >> 11) & 0x7;
    }

    static uint16_t Convert(const uint16_t packed) {
        return Pack(ID(packed), 0, 0);
    }

    static bool FlipHorizontal(const uint8_t variant) {
        return (variant & (1 << 0)) != 0;
    }

    static bool FlipVertical(const uint8_t variant) {
        return (variant & (1 << 1)) != 0;
    }

    static bool Waterlogged(const uint8_t variant) {
        return (variant & (1 << 2)) != 0;
    }

    static uint16_t PackFlags(const uint16_t packed, const bool flipHorizontal, const bool flipVertical, const bool waterlogged) {
        return Pack(ID(packed), Rotation(packed), PackFlagsVariant(Variant(packed), flipHorizontal, flipVertical, waterlogged));
    }

    static uint8_t PackFlagsVariant(const uint8_t variant, const bool flipHorizontal, const bool flipVertical, const bool waterlogged) {
        uint8_t variantMod = variant;

        variantMod |= flipHorizontal ? (1 << 0) : variantMod &= ~(1 << 0);
        variantMod |= flipVertical ? (1 << 1) : variantMod &= ~(1 << 1);
        variantMod |= waterlogged ? (1 << 2) : variantMod &= ~(1 << 2);

        return variantMod;
    }
};