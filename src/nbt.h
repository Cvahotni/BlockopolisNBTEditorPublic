#pragma once

#include "pch.h"

#include "vector3.h"
#include "item_stack.h"
#include "coord.h"
#include "commited_block_and_behaviour.h"
#include "feature_instance.h"
#include "log.h"

enum NBTType {
    TagEnd = 0,
    TagBool = 1,
    TagByte = 2,
    TagShort = 3,
    TagUShort = 4,
    TagInt = 5,
    TagUInt = 6,
    TagLong = 7,
    TagULong = 8,
    TagFloat = 9,
    TagDouble = 10,
    TagString = 11,
    TagVector3 = 12,
    TagItemStack = 13,
    TagByteBlob = 14,
    TagChunkCoord = 15,
    TagCommittedBlockBehaviour = 16,
    TagFeaturePlacement = 17,
    TagCompound = 100
};

class NBTTag {
public:
    NBTTag() = default;

    virtual ~NBTTag() = default;
    virtual void Write(std::vector<uint8_t>& out) = 0;
    virtual void Read(std::vector<uint8_t>& in, size_t& offset) = 0;
    virtual NBTType Type() const = 0;
    virtual void Print() const = 0;
};

class NBTBool : public NBTTag {
public:
    bool value = false;

    NBTBool(bool value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    bool Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagBool;
    }

    void Print() const override {
        Log::Info("TagBool: " + std::to_string(value));
    }
};

class NBTByte : public NBTTag {
public:
    int8_t value = 0;

    NBTByte(int8_t value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    int8_t Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagByte;
    }

    void Print() const override {
        Log::Info("TagByte: " + std::to_string(value));
    }
};

class NBTShort : public NBTTag {
public:
    int16_t value = 0;
    
    NBTShort(int32_t value) : value(value) {}
    
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;
    
    int16_t Value() {
        return value;
    }
    
    NBTType Type() const override {
        return NBTType::TagShort;
    }
    
    void Print() const override {
        Log::Info("TagShort: " + std::to_string(value));
    }
};

class NBTUShort : public NBTTag {
public:
    uint16_t value = 0;
    
    NBTUShort(int32_t value) : value(value) {}
    
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;
    
    uint16_t Value() {
        return value;
    }
    
    NBTType Type() const override {
        return NBTType::TagUShort;
    }
    
    void Print() const override {
        Log::Info("TagUShort: " + std::to_string(value));
    }
};

class NBTInt : public NBTTag {
public:
    int32_t value = 0;

    NBTInt(int32_t value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    int32_t Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagInt;
    }

    void Print() const override {
        Log::Info("TagInt: " + std::to_string(value));
    }
};

class NBTUInt : public NBTTag {
public:
    uint32_t value = 0;

    NBTUInt(uint32_t value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    uint32_t Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagUInt;
    }

    void Print() const override {
        Log::Info("TagUInt: " + std::to_string(value));
    }
};

class NBTLong : public NBTTag {
public:
    int64_t value = 0;
    
    NBTLong(int64_t value) : value(value) {}
    
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;
    
    int64_t Value() {
        return value;
    }
    
    NBTType Type() const override {
        return NBTType::TagLong;
    }
    
    void Print() const override {
        Log::Info("TagLong: " + std::to_string(value));
    }
};

class NBTULong : public NBTTag {
public:
    uint64_t value = 0;
        
    NBTULong(uint64_t value) : value(value) {}
        
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;
        
    uint64_t Value() {
        return value;
    }
        
    NBTType Type() const override {
        return NBTType::TagULong;
    }
        
    void Print() const override {
        Log::Info("TagULong: " + std::to_string(value));
    }
};

class NBTFloat : public NBTTag {
public:
    float value = 0.0f;
    
    NBTFloat(float value) : value(value) {}
    
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    float Value() {
        return value;
    }
    
    NBTType Type() const override {
        return NBTType::TagFloat;
    }
    
    void Print() const override {
        Log::Info("TagFloat: " + std::to_string(value));
    }
};

class NBTDouble : public NBTTag {
public:
    double value = 0.0;
    
    NBTDouble(double value) : value(value) {}
    
    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    double Value() {
        return value;
    }
    
    NBTType Type() const override {
        return NBTType::TagDouble;
    }
    
    void Print() const override {
        Log::Info("TagDouble: " + std::to_string(value));
    }
};

class NBTString : public NBTTag {
public:
    std::string value = "";

    NBTString(std::string value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    std::string Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagString;
    }

    void Print() const override {
        Log::Info("TagString: " + value);
    }
};

class NBTVector3 : public NBTTag {
public:
    Vector3 value{};

    NBTVector3(Vector3 value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    Vector3 Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagVector3;
    }

    void Print() const override {
        Log::Info("TagVector3: ???");
    }
};

class NBTItemStack : public NBTTag {
public:
    ItemStack value{};

    NBTItemStack(ItemStack value) : value(value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    ItemStack Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagItemStack;
    }

    void Print() const override {
        Log::Info("TagItemStack: " + std::to_string(value.ID()) + ", " + std::to_string(value.Amount()));
    }
};

class NBTByteBlob : public NBTTag {
public:
    std::vector<uint8_t> value{};

    NBTByteBlob(std::vector<uint8_t> _value) : value(_value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    std::vector<uint8_t>& Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagByteBlob;
    }

    void Print() const override {
        Log::Info("TagByteBlob: " + std::to_string(value.size()));
    }
};

class NBTChunkCoord : public NBTTag {
public:
    ChunkCoord value{};

    NBTChunkCoord(ChunkCoord _value) : value(_value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    ChunkCoord Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagChunkCoord;
    }

    void Print() const override {
        auto tempCoord = value;
        Log::Info("TagChunkCoord: " + tempCoord.ToString());
    }
};

class NBTCommittedBlockBehaviour : public NBTTag {
public:
    CommittedBlockBehaviour value{};

    NBTCommittedBlockBehaviour(CommittedBlockBehaviour _value) : value(_value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    CommittedBlockBehaviour Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagCommittedBlockBehaviour;
    }

    void Print() const override {
        Log::Info("TagCommittedBlockBehaviour: ???");
    }
};

class NBTFeaturePlacement : public NBTTag {
public:
    FeatureInstance value{};

    NBTFeaturePlacement(FeatureInstance _value) : value(_value) {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    FeatureInstance Value() {
        return value;
    }

    NBTType Type() const override {
        return NBTType::TagFeaturePlacement;
    }

    void Print() const override {
        Log::Info("TagFeaturePlacement: ???");
    }
};

class NBTCompound : public NBTTag {
public:
    std::map<std::string, std::shared_ptr<NBTTag>> tags{};

    ~NBTCompound() {}

    void Write(std::vector<uint8_t>& out) override;
    void Read(std::vector<uint8_t>& in, size_t& offset) override;

    std::shared_ptr<NBTTag> TagAt(const std::string key);

    NBTType Type() const override {
        return NBTType::TagCompound;
    }

    void Print() const override {
        Log::Info("TAG_Compound: ");

        for(const auto &tag : tags) {
            Log::Info("Name: " + tag.first);
            tag.second->Print();
        }
    }
};

class NBT {
public:
    NBTCompound root{};

    void ReadFromFileStream(std::ifstream& in);
    void WriteToFileStream(std::ofstream& out);

    void ReadFromVector(std::vector<uint8_t>& in);
    void WriteToVector(std::vector<uint8_t>& out);

    void Print() const {
        root.Print();
    }
};