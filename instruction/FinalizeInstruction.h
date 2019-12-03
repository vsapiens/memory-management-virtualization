#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class FinalizeInstruction : public Instruction {
 public:
    FinalizeInstruction(const std::string& type);
};
/*
Function: FinalizeInstruction::FinalizeInstruction
    This function finalizes the instructions
Parameters: const std::string& type
Return: -
*/
FinalizeInstruction::FinalizeInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}

}