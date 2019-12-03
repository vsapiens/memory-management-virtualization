#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class ExitInstruction : public Instruction {
 public:
    ExitInstruction(const std::string& type);
};
/*
Function: ExitInstruction::ExitInstruction
    This function exits the instruction
Parameters: const std::string& type
Return: -
*/
ExitInstruction::ExitInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}
}