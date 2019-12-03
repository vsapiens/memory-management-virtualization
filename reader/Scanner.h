// Scanner.h
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

namespace sisops{

class Scanner {
    public:
    Scanner();

    std::vector<Token> scan(std::string str);

    private:
    int filter(char c);
    int getEndWord(std::string s, int init);
    int transition_matrix[1000][1000] = {
        {1, 2, 3, 4, 5, 6, 115, 7, 0, 9, 8},
        {115, 115, 115, 115, 115, 115, 115, 115, 109, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 115, 110, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 115, 111, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 115, 112, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 115, 113, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 115, 114, 115, 115},
        {115, 115, 115, 115, 115, 115, 115, 7, 116, 7, 7},
        {115, 115, 115, 115, 115, 115, 115, 7, 117, 7, 7},
        {115, 115, 115, 115, 115, 115, 115, 7, 118, 7, 7},
    };
};
/*
Function: Scanner::Scanner()
    Constructor scanner
Parameters: std::string file
Return: -
*/
Scanner::Scanner(){}
/*
Function: getEndWord
    This functions gets the end of the word
Parameters: std::string s, int init
Return: int
*/
int Scanner::getEndWord(std::string s, int init) {
    for (int i = init; i < s.length(); i++) {
        if (s[i] == ' ') {
            return i;
        }
    }

    return s.length()-1;
}
/*
Function: Scanner::scan
    This function scans the file
Parameters: std::string str
Return: std::vector<Token> 
*/
std::vector<Token> Scanner::scan(std::string str) {
    str += " "; // We added this so the last token is read.
    char c;
    int state = 0, index = 0;
    std::string value = "";

    std::vector<Token> tokens;
    Token token;

    while (index < str.length()) {
        value = "";
        do {
            c = str[index];
            index++;
            state = transition_matrix[state][filter(c)];
            if (state != 0) {
                value += c;
            }
        } while (index < str.length() && state < 100);
        int end = 0;
        switch (state) {
            case 109:
                token.token_type = TokenType::Load;
                token.value = value;
                tokens.push_back(token);
                break;
            case 110:
                token.token_type = TokenType::Access;
                token.value = value;
                tokens.push_back(token);
                break;
            case 111:
                token.token_type = TokenType::Free;
                token.value = value;
                tokens.push_back(token);
                break;
            case 112:
                token.token_type = TokenType::Comment;
                token.value = value;
                tokens.push_back(token);
                break;
            case 113:
                token.token_type = TokenType::Finalize;
                token.value = value;
                tokens.push_back(token);
                break;
            case 114:
                token.token_type = TokenType::Exit;
                token.value = value;
                tokens.push_back(token);
                break;
            case 115:
                token.token_type = TokenType::String;
                end = getEndWord(str, index);
                token.value = value + str.substr(index, end-index);
                tokens.push_back(token);
                index = end+1;
                break;
            case 116:
                token.token_type = TokenType::Integer;
                token.value = value;
                tokens.push_back(token);
                break;
            case 117:
                token.token_type = TokenType::One;
                token.value = value;
                tokens.push_back(token);
                break;
            case 118:
                token.token_type = TokenType::Zero;
                token.value = value;
                tokens.push_back(token);
                break;
            case 999:
                std::cerr << "LEXICAL ERROR - " << value << std::endl;
            default:
                return tokens;
        }
        state = 0;
    }

    return tokens;
}
/*
Function: Scanner::filter
    This function filters the char and gives it to the token 
Parameters: char c
Return: int 
*/
int Scanner::filter(char c) {
    switch(c) {
        case 'P':
            return 0;
        case 'A':
            return 1;
        case 'L':
            return 2;
        case 'C':
            return 3;
        case 'F':
            return 4;
        case 'E':
            return 5;
        case '0':
            return 9;
        case '1':
            return 10;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 7;
        case ' ':
        case '\t':
            return 8;
        default:
            return 6;
    }
}
}

