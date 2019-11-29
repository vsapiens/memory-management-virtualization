// Parser.h
// The header handles all the input phases of the program from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

namespace sisops{

class Parser {
    public:
    Parser();
    void parseIns(std::vector<Token> tokens);

    private:
    int token_index = 0;
    void match(std::vector<Token> tokens, TokenType token);
    void parsePPart(std::vector<Token> tokens);
    void parseAPart(std::vector<Token> tokens);
    void parseLPart(std::vector<Token> tokens);
    void parseCPart(std::vector<Token> tokens);
    void parseBit(std::vector<Token> tokens);
    void parseInteger(std::vector<Token> tokens);
};

Parser::Parser(){}

void Parser::parseIns(std::vector<Token> tokens) {
    token_index = 0;
    switch(tokens[token_index].token_type) {
        case TokenType::Load:
            match(tokens, TokenType::Load);
            parsePPart(tokens);
            break;
        case TokenType::Access:
            match(tokens, TokenType::Access);
            parseAPart(tokens);
            break;
        case TokenType::Free:
            match(tokens, TokenType::Free);
            parseLPart(tokens);
            break;
        case TokenType::Comment:
            match(tokens, TokenType::Comment);
            parseCPart(tokens);
            break;
        case TokenType::Finalize:
            match(tokens, TokenType::Finalize);
            break;
        case TokenType::Exit:
            match(tokens, TokenType::Exit);
            break;
        default:
            std::cerr << "Parsing error" << std::endl;
            break;
    }

    if (token_index < tokens.size()) {
        std::cerr << "Parsing error" << std::endl;
    } else {
        std::cout << "Todo bien" << std::endl;
    }
}

void Parser::parsePPart(std::vector<Token> tokens) {
    parseInteger(tokens);
    parseInteger(tokens);
}

void Parser::parseAPart(std::vector<Token> tokens) {
    parseInteger(tokens);
    parseInteger(tokens);
    parseBit(tokens);
}

void Parser::parseLPart(std::vector<Token> tokens) {
    parseInteger(tokens);
}

void Parser::parseCPart(std::vector<Token> tokens) {
    token_index = tokens.size();
}

void Parser::parseInteger(std::vector<Token> tokens) {
    switch(tokens[token_index].token_type) {
        case TokenType::Integer:
            match(tokens, TokenType::Integer);;
            break;
        default:
            parseBit(tokens);
            break;
    }
}

void Parser::parseBit(std::vector<Token> tokens) {
    switch(tokens[token_index].token_type) {
        case TokenType::One:
            match(tokens, TokenType::One);;
            break;
        case TokenType::Zero:
            match(tokens, TokenType::Zero);
            break;
        default:
            std::cerr << "Parsing error" << std::endl;
            break;
    }
}

void Parser::match(std::vector<Token> tokens, TokenType type) {
        if (token_index >= tokens.size()) {
            std::cerr << "Parsing error" << std::endl;
        }

        if (tokens[token_index].token_type != type) {
            std::cerr << "Parsring error" << std::endl;
        } else {
            token_index++;
        }
    }
}

