#pragma once

#include <string>

namespace sisops {

enum class TokenType {
    Load,
    Access,
    Free,
    Comment,
    Finalize,
    Exit,
    Integer,
    String,
    Zero,
    One,
    Unset
};

struct Token
{
    TokenType token_type = TokenType::Unset;
    std::string value = "Unset";

    Token(TokenType tt, std::string val) {
        token_type = tt;
        value = val;
    }
};

    
}
