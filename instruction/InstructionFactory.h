#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "AccessInstruction.h"
#include "CommentInstruction.h"
#include "ExitInstruction.h"
#include "FinalizeInstruction.h"
#include "FreeInstruction.h"
#include "LoadInstruction.h"
#include "Instruction.h"
#include "../reader/Token.h"

namespace sisops {

class InstructionFactory final {
 public:
    std::shared_ptr<Instruction> MakeInstruction(const std::vector<Token>& tokens) const;
};
/*
Function: InstructionFactory::MakeInstruction
    This functions makes the instruction
Parameters: const std::vector<Token>& tokens
Return: std::shared_ptr<Instruction> 
*/
std::shared_ptr<Instruction> InstructionFactory::MakeInstruction(const std::vector<Token>& tokens) const{
    switch(tokens[0].token_type) {
        case TokenType::Load: {
            return std::make_shared<LoadInstruction>(tokens[0].value,tokens[1].value,tokens[2].value);
        }
        case TokenType::Access: {
            return std::make_shared<AccessInstruction>(tokens[0].value,tokens[1].value,tokens[2].value,tokens[3].value);
        }
        case TokenType::Free: {
            return std::make_shared<FreeInstruction>(tokens[0].value, tokens[1].value);
        }
        case TokenType::Comment: {
            std::string comment = "";
            for (const Token& t : tokens) {
                comment += (t.value + " ");
            }
            return std::make_shared<CommentInstruction>(tokens[0].value, comment);
        }
        case TokenType::Finalize: {
            return std::make_shared<FinalizeInstruction>(tokens[0].value);
        }
        case TokenType::Exit: {
            return std::make_shared<ExitInstruction>(tokens[0].value);
        }
        default: {
            return nullptr;
        }
    }
}

}