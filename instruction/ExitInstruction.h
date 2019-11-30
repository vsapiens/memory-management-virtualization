#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class ExitInstruction : public Instruction {
 public:
    ExitInstruction(const std::string& type);
};

ExitInstruction::ExitInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}
}