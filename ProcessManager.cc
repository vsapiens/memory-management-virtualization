#pragma once
#include <memory>
#include <vector>

#include "PageSize.h"
#include "ProcessManager.h"
#include "Token.h"
#include "util/Instruction.h"
#include "util/InstructionFactory.h"

namespace sisops {

void ProcessManager::Load(std::unique_ptr<Instruction> current_instruction) {
    const LoadInstruction
}

void ProcessManager::DoProcess(std::vector<Token> instruction) {
    TokenType token_type = instruction[0].token_type;
    std::unique_ptr<Instruction> current_instruction = factory.MakeInstruction(instruction);
    switch (token_type) {
        case TokenType::Load: {
            Load(std::move(current_instruction));
        }
        break;
        case TokenType::Access: {

        }
        break;
        case TokenType::Free: {

        }
        break;
        case TokenType::Comment: {

        }
        break;
        case TokenType::Finalize: {

        }
        break;
        case TokenType::Exit: {

        }
        break;
        default: {

        }
        break;
    }
}

}