#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

namespace sisops{

namespace {

std::vector<std::string> readFile(std::string file){
    std::ifstream input;
    input.open(file);

    std::vector<std::string> ins;

    std::string buffer;
    while (std::getline(input, buffer)) {
        ins.push_back(buffer);
    }

    return ins;
}
}

std::vector<std::vector<Token>> readInputFile(std::string file) {
    std::vector<std::string> instructions = readFile(file);

    Parser parser;
    Scanner scanner;

    std::vector<std::vector<Token>> token_list;

    for (const std::string &instruction : instructions) {
        std::vector<Token> tokens = scanner.scan(instruction);
        parser.parseIns(tokens);
        token_list.push_back(tokens);
    }

    std::cout << "Listou" << std::endl;

    return token_list;
}

}
