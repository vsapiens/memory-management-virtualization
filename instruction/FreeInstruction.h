#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class FreeInstruction : public Instruction {
 public:
    FreeInstruction(const std::string& type,const std::string& id);
    int GetId();
 private:
    int id_;
};

FreeInstruction::FreeInstruction(const std::string& type,const std::string& id) {
    instruction_type = GetInstructionType(type);
    id_ = std::stoi(id);
}

inline int FreeInstruction::GetId() {
    return id_;
}
}