// Parser.h
// The header handles all the input phases of the program from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#pragma once

namespace sisops{

class Parser {
    public:
    Parser();
    ~Parser();

    private:
    int token_index = 0;
    void match(std::vector<Token> tokens, Token token);
};

Parser::Parser(){}

void Parser::match(std::vector<Token> tokens, Token token) {
        if (tokenIndex >= tokens.size()) {
            std::cerr << "Parsing error" << std::endl;
        }

        if (tokens[tokenIndex].token_type != token.token_type) {
            std::cerr << "Parsring error" << std::endl;
        } else {
            tokenIndex++;
        }
    }
}

