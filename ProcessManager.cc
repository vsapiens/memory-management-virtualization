#pragma once
#include <vector>

#include "PageSize.h"
#include "ProcessManager.h"
#include "Token.h"

namespace sisops {

void ProcessManager::Load(std::vector<Token>& instruction) {
    
}

void ProcessManager::DoProcess(std::vector<Token> instruction) {
    TokenType token_type = instruction[0].token_type;
    switch (token_type) {
        case TokenType::Load: {
            Load(instruction);
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