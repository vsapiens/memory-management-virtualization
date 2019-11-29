#pragma once
#include <memory>
#include <vector>

#include "Instruction.h"
#include "InstructionFactory.h"
#include "Token.h"


namespace sisops {

std::unique_ptr<Instruction> InstructionFactory::MakeInstruction(const std::vector<Token>& tokens) const{
    switch(tokens[0].token_type) {
        case TokenType::Load: {
            return std::make_unique<LoadInstruction>(tokens[0].value,tokens[1].value,tokens[2].value);
        }
        case TokenType::Access: {
            return std::make_unique<AccessInstruction>(tokens[0].value,tokens[1].value,tokens[2].value,tokens[3].value);
        }
        case TokenType::Free: {
            return std::make_unique<FreeInstruction>(tokens[0].value, tokens[1].value);
        }
        case TokenType::Comment: {
            return std::make_unique<CommentInstruction>(tokens[0].value, tokens[1].value);
        }
        case TokenType::Finalize: {
            return std::make_unique<FinalizeInstruction>(tokens[0].value);
        }
        case TokenType::Exit: {
            return std::make_unique<ExitInstruction>(tokens[0].value);
        }
        default: {
            return nullptr;
        }
    }
}
}