#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

namespace sisops{

namespace {

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

std::vector<std::string> readFile(std::string file){
    std::ifstream input;
    input.open(file);

    std::vector<std::string> ins;

    std::string buffer;
    while (std::getline(input, buffer)) {
        trim(buffer);
        ins.push_back(buffer);
    }

    return ins;
}
}

struct Error {
    std::string message;
    int line;

    Error(int l, std::string m) {
        line = l;
        message = m;
    }
};

std::tuple<std::vector<std::vector<Token>>, std::vector<Error>> readAndParseInputFile(std::string file) {
    std::vector<std::string> instructions = readFile(file);

    Parser parser;
    Scanner scanner;

    std::vector<std::vector<Token>> token_list;
    std::vector<Error> errors;

    for (int i = 0; i < instructions.size(); i++) {
        std::vector<Token> tokens = scanner.scan(instructions[i]);
        ParseStatus status = parser.parseIns(tokens);
        
        if (!status.correct) {
            Error e(i+1, status.message);
            errors.push_back(e);
        }
        token_list.push_back(tokens);
    }

    return std::make_tuple(token_list, errors);
}

}
