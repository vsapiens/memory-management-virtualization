#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Instruction.h"
#include "Token.h"

namespace sisops {

class InstructionFactory final {
 public:
    std::unique_ptr<Instruction> MakeInstruction(const std::vector<Token>& tokens) const;
};

}