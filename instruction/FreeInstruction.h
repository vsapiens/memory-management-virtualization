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
/*
Function: FreeInstruction::FreeInstruction
    Frees the instruction
Parameters: const std::string& type,const std::string& id
Return: -
*/
FreeInstruction::FreeInstruction(const std::string& type,const std::string& id) {
    instruction_type = GetInstructionType(type);
    id_ = std::stoi(id);
}
/*
Function: FreeInstruction::GetId()
    This functions gets the ID
Parameters: const std::string& type,const std::string& id
Return: int
*/
inline int FreeInstruction::GetId() {
    return id_;
}
}