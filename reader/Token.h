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
/*
Function: token_type_to_string
    The function identifies the token type and matches it to the string
Parameters: TokenType tt
Return: std::string
*/
std::string token_type_to_string(TokenType tt) {
    switch(tt) {
        case TokenType::Load:
            return "Load";
        case TokenType::Access:
            return "Access";
        case TokenType::Free:
            return "Free";
        case TokenType::Comment:
            return "Comment";
        case TokenType::Finalize:
            return "Finalize";
        case TokenType::Exit:
            return "Exit";
        case TokenType::Integer:
            return "Integer";
        case TokenType::String:
            return "String";
        case TokenType::Zero:
            return "Zero";
        case TokenType::One:
            return "One";
        case TokenType::Unset:
            return "Unset";
    }
}

struct Token
{
    TokenType token_type = TokenType::Unset;
    std::string value = "Unset";

    Token() {}
/*
Function: Token
    Constructor of the token type and its correspondent value
Parameters: TokenType tt, std::string val
Return: -
*/
    Token(TokenType tt, std::string val) {
        token_type = tt;
        value = val;
    }
};

    
}
