#pragma once
#include <memory>
#include <vector>

#include "PageSize.h"
#include "ProcessManager.h"
#include "Token.h"
#include "instruction/Instruction.h"
#include "instruction/InstructionFactory.h"

namespace sisops {
void ProcessManager::Load(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<LoadInstruction>(current_instruction);
    if(instruction->GetBytes() > )
}
void ProcessManager::Access(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<AccessInstruction>(current_instruction);
}
void ProcessManager::Free(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FreeInstruction>(current_instruction);
}
void ProcessManager::Comment(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<CommentInstruction>(current_instruction);
}
void ProcessManager::Finalize(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FinalizeInstruction>(current_instruction);
}
void ProcessManager::Exit(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<ExitInstruction>(current_instruction);
}
void ProcessManager::DoProcess(std::vector<Token> instruction) {
    TokenType token_type = instruction[0].token_type;
    std::shared_ptr<Instruction> current_instruction = factory.MakeInstruction(instruction);
    switch (token_type) {
        case TokenType::Load: {
            Load(std::move(current_instruction));
        }
        break;
        case TokenType::Access: {
            Access(std::move(current_instruction));
        }
        break;
        case TokenType::Free: {
            Free(std::move(current_instruction));
        }
        break;
        case TokenType::Comment: {
            Comment(std::move(current_instruction));
        }
        break;
        case TokenType::Finalize: {
            Finalize(std::move(current_instruction));
        }
        break;
        case TokenType::Exit: {
            Exit(std::move(current_instruction));
        }
        break;
        default: {

        }
        break;
    }
}
}
