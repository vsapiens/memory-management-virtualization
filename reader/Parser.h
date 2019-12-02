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

struct ParseStatus {
    bool correct;
    std::string message;

    ParseStatus() {
        correct = true;
        message = "";
    }
};

class Parser {
    public:
    Parser();
    ParseStatus parseIns(std::vector<Token> tokens);

    private:
    int token_index = 0;
    void match(std::vector<Token> tokens, TokenType token);
    void parsePPart(std::vector<Token> tokens);
    void parseAPart(std::vector<Token> tokens);
    void parseLPart(std::vector<Token> tokens);
    void parseCPart(std::vector<Token> tokens);
    void parseBit(std::vector<Token> tokens);
    void parseInteger(std::vector<Token> tokens);

    ParseStatus parse_status;
};

Parser::Parser() : parse_status(){}

ParseStatus Parser::parseIns(std::vector<Token> tokens) {
    token_index = 0;

    parse_status.correct = true;
    parse_status.message = "";

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
            parse_status.correct = false;
            parse_status.message = "Instruction must begin with an operation <P, A, L, E, F, C>";
            break;
    }

    if (token_index < tokens.size() && parse_status.correct) {
        parse_status.correct = false;
        parse_status.message = "Instruction contains " + std::to_string(tokens.size()) 
            + " element(s). Expected " + std::to_string(token_index);
    }

    return parse_status;
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
    if (token_index >= tokens.size()) {
        if (parse_status.correct) {
            parse_status.correct = false;
            parse_status.message = "Fewer elements than expected"; 
        }

        return;
    }

    switch(tokens[token_index].token_type) {
        case TokenType::Integer:
            match(tokens, TokenType::Integer);
            break;
        case TokenType::One:
        case TokenType::Zero:
            parseBit(tokens);
            break;
        default:
             if (parse_status.correct) {
                parse_status.correct = false;
                parse_status.message = "Expected Integer or Bit. Got " 
                    + token_type_to_string(tokens[token_index].token_type);
             }
    }
}

void Parser::parseBit(std::vector<Token> tokens) {
    if (token_index >= tokens.size()) {
        if (parse_status.correct) {
            parse_status.correct = false;
            parse_status.message = "Fewer elements than expected"; 
        }

        return;
    }

    switch(tokens[token_index].token_type) {
        case TokenType::One:
            match(tokens, TokenType::One);;
            break;
        case TokenType::Zero:
            match(tokens, TokenType::Zero);
            break;
        default:
            if (parse_status.correct) {
                parse_status.correct = false;
                parse_status.message = "Expected bit on last position. Got " 
                    + token_type_to_string(tokens[token_index].token_type);
            }
            break;
    }
}

void Parser::match(std::vector<Token> tokens, TokenType type) {
        if (token_index >= tokens.size()) {
            parse_status.correct = false;
            parse_status.message = "Instruction contains " + std::to_string(token_index) 
            + " elements. Expected " + std::to_string(tokens.size());
        }

        if (tokens[token_index].token_type != type) {
            parse_status.correct = false;
            parse_status.message = "Expected" + token_type_to_string(type) + ". Got " 
                + token_type_to_string(tokens[token_index].token_type);
        } else {
            token_index++;
        }
    }
}

