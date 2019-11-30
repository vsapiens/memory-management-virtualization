#pragma once
#include <string>

#include "Instruction.h"

namespace sisops {
class LoadInstruction : public Instruction {
 public:
    LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id);
    ~LoadInstruction(){};
    int GetBytes();
    int GetId();
 private:
    int bytes_;
    int id_;
};

LoadInstruction::LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id) {
    instruction_type = GetInstructionType(type);
    bytes_ = std::stoi(bytes);
    id_ = std::stoi(id);
}

inline int LoadInstruction::GetBytes() {
    return bytes_;
}

inline int LoadInstruction::GetId() {
    return id_;
}
}