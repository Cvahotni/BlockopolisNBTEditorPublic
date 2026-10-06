#pragma once

#include "pch.h"

struct ItemStack {
public:
    ItemStack() {}
    ItemStack(uint16_t _id, uint16_t _amount) : id(_id), amount(_amount) {}

    uint16_t ID() const {
        return id;
    }

    uint16_t Amount() const {
        return amount;
    }

    void SetID(const uint16_t _id) {
        id = _id;
    }

    void SetAmount(const uint16_t _amount) {
        amount = _amount;
    }

    bool IsEmpty();
    bool IsAir();

    bool Matches(ItemStack other);
    void SetEmpty();

    void CopyFrom(ItemStack other);
    ItemStack Copy();

    std::string ToString() {
        return std::to_string(id) + ", " + std::to_string(amount);
    }

private:
    uint16_t id = 0;
    uint16_t amount = 0;
};