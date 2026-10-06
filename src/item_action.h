#pragma once

#include "pch.h"

#include "item_stack.h"
#include "item_slot_type.h"

enum ItemActionType {
    CreativeItemAction = 0,
    ReplaceItemAction = 1,
    DepositOneItemAction = 2,
    DepositAllItemAction = 3,
    SplitInHalfItemAction = 4,

    ItemActionTypesSize = 5
};

struct ItemAction {
public:
    ItemActionType type = ItemActionType::ReplaceItemAction;

    uint32_t fromSlot = 0;
    uint32_t toSlot = 0;

    ItemSlotType fromSlotType = ItemSlotType::DefaultSlot;
    ItemSlotType toSlotType = ItemSlotType::DefaultSlot;

    ItemStack stack{};
};