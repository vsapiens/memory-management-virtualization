#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class FinalizeInstruction : public Instruction {
 public:
    FinalizeInstruction(const std::string& type);
};

FinalizeInstruction::FinalizeInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}

}