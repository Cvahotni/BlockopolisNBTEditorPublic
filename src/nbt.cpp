#include "pch.h"
#include "nbt.h"
#include "buffer_io.h"

void NBTBool::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteBoolToBuffer(out, value);
}

void NBTBool::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadBoolFromBuffer(in, offset, value);
}

void NBTByte::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}

void NBTByte::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTShort::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
    
void NBTShort::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTUShort::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
    
void NBTUShort::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTInt::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}

void NBTInt::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTUInt::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}

void NBTUInt::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTLong::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
    
void NBTLong::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTULong::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
        
void NBTULong::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTFloat::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
    
void NBTFloat::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTDouble::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}
    
void NBTDouble::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTString::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteStringToBuffer(out, value);
}

void NBTString::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadStringFromBuffer(in, offset, value);
}

void NBTVector3::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteVector3ToBuffer(out, value);
}

void NBTVector3::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadVector3romBuffer(in, offset, value);
}

void NBTItemStack::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value);
}

void NBTItemStack::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value);
}

void NBTByteBlob::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteByteListToBuffer(out, value);
}

void NBTByteBlob::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadByteListFromBuffer(in, offset, value);
}

void NBTChunkCoord::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteChunkCoordToBuffer(out, value);
}

void NBTChunkCoord::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadChunkCoordFromBuffer(in, offset, value);
}

void NBTCommittedBlockBehaviour::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value.x);
    BufferIO::WriteToBuffer(out, value.y);
    BufferIO::WriteToBuffer(out, value.z);
    BufferIO::WriteToBuffer(out, value.b);
}

void NBTCommittedBlockBehaviour::Read(std::vector<uint8_t>& in, size_t& offset) {
    BufferIO::ReadFromBuffer(in, offset, value.x);
    BufferIO::ReadFromBuffer(in, offset, value.y);
    BufferIO::ReadFromBuffer(in, offset, value.z);
    BufferIO::ReadFromBuffer(in, offset, value.b);
}

void NBTFeaturePlacement::Write(std::vector<uint8_t>& out) {
    BufferIO::WriteToBuffer(out, value.X());
    BufferIO::WriteToBuffer(out, value.Y());
    BufferIO::WriteToBuffer(out, value.Z());
    BufferIO::WriteToBuffer(out, value.F());
}

void NBTFeaturePlacement::Read(std::vector<uint8_t>& in, size_t& offset) {
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    int32_t f = 0;

    BufferIO::ReadFromBuffer(in, offset, x);
    BufferIO::ReadFromBuffer(in, offset, y);
    BufferIO::ReadFromBuffer(in, offset, z);
    BufferIO::ReadFromBuffer(in, offset, f);

    value.SetX(x);
    value.SetY(y);
    value.SetZ(z);
    value.SetF(f);
}

void NBTCompound::Write(std::vector<uint8_t>& out) {
    for(const auto &tag : tags) {
        auto name = tag.first;
        auto pointer = tag.second;

        if(!pointer) {
            Log::Warning("Tried to write an NBT tag with an invalid pointer: " + name);
            continue;
        }

        BufferIO::WriteToBuffer(out, pointer->Type());
        BufferIO::WriteStringToBuffer(out, name.c_str());

        pointer->Write(out);
    }

    BufferIO::WriteToBuffer(out, NBTType::TagEnd);
}

void NBTCompound::Read(std::vector<uint8_t>& in, size_t& offset) {
    while(true) {
        NBTType tagType = NBTType::TagByte;
        BufferIO::ReadFromBuffer(in, offset, tagType);
            
        if(tagType == TagEnd) {
            break;
        }

        std::string name = "";
        BufferIO::ReadStringFromBuffer(in, offset, name);

        std::shared_ptr<NBTTag> tag;

        switch(tagType) {
            case NBTType::TagCompound: {
                tag = std::make_shared<NBTCompound>(NBTCompound{});
                break;
            }

            case NBTType::TagBool: {
                tag = std::make_shared<NBTBool>(NBTBool(false));
                break;
            }

            case NBTType::TagByte: {
                tag = std::make_shared<NBTByte>(NBTByte(0));
                break;
            }

            case NBTType::TagShort: {
                tag = std::make_shared<NBTShort>(NBTShort(0));
                break;
            }

            case NBTType::TagUShort: {
                tag = std::make_shared<NBTUShort>(NBTUShort(0));
                break;
            }

            case NBTType::TagInt: {
                tag = std::make_shared<NBTInt>(NBTInt(0));
                break;
            }

            case NBTType::TagUInt: {
                tag = std::make_shared<NBTUInt>(NBTUInt(0));
                break;
            }

            case NBTType::TagLong: {
                tag = std::make_shared<NBTLong>(NBTLong(0));
                break;
            }

            case NBTType::TagULong: {
                tag = std::make_shared<NBTULong>(NBTULong(0));
                break;
            }

            case NBTType::TagFloat: {
                tag = std::make_shared<NBTFloat>(NBTFloat(0));
                break;
            }

            case NBTType::TagDouble: {
                tag = std::make_shared<NBTDouble>(NBTDouble(0));
                break;
            }

            case NBTType::TagString: {
                tag = std::make_shared<NBTString>(NBTString(""));
                break;
            }

            case NBTType::TagVector3: {
                tag = std::make_shared<NBTVector3>(NBTVector3({}));
                break;
            }

            case NBTType::TagItemStack: {
                tag = std::make_shared<NBTItemStack>(NBTItemStack({}));
                break;
            }

            case NBTType::TagByteBlob: {
                tag = std::make_shared<NBTByteBlob>(NBTByteBlob({}));
                break;
            }

            case NBTType::TagChunkCoord: {
                tag = std::make_shared<NBTChunkCoord>(NBTChunkCoord({}));
                break;
            }

            case NBTType::TagCommittedBlockBehaviour: {
                tag = std::make_shared<NBTCommittedBlockBehaviour>(NBTCommittedBlockBehaviour({}));
                break;
            }

            case NBTType::TagFeaturePlacement: {
                tag = std::make_shared<NBTFeaturePlacement>(NBTFeaturePlacement({}));
                break;
            }
                
            default: {
                Log::Error("Unsupported NBT type");
                return;
            }
        }

        tag->Read(in, offset);
        tags[name] = tag;
    }
}

std::shared_ptr<NBTTag> NBTCompound::TagAt(const std::string key) {
    if(tags.count(key) < 1) {
        Log::Error("Failed to find NBT tag key: " + key);
        tags[key] = std::make_shared<NBTCompound>();
    }

    return tags[key];
}

void NBT::ReadFromFileStream(std::ifstream& in) {
    in.seekg(0, std::ios::end);
    auto fileSize = in.tellg();
    in.seekg(0, std::ios::beg);

    size_t offset = 0;

    std::vector<uint8_t> buffer(fileSize);
    in.read(reinterpret_cast<char*>(buffer.data()), fileSize);   

    root.Read(buffer, offset);
    in.close();
}

void NBT::WriteToFileStream(std::ofstream& out) {
    std::vector<uint8_t> buffer{};
    root.Write(buffer);

    out.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
    out.close();
}

void NBT::ReadFromVector(std::vector<uint8_t>& in) {
    size_t offset = 0;
    root.Read(in, offset);
}

void NBT::WriteToVector(std::vector<uint8_t>& out) {
    root.Write(out);
}