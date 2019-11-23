#include <vector>
#include <string>
#include <fstream>
#include "Token.h"
#include "Scanner.h"

namespace sisops{

namespace {

std::vector<std::string> readFile(std::string file){
    std::ifstream input;
    input.open("file");

    std::vector<std::string> ins;

    std::string buffer;
    while (getline(input, buffer)) {
        ins.push_back(buffer);
    }

    return ins;
}
}

std::vector<std::vector<Token>> readInputFile(std::string file) {
    std::vector<std::string> instructions = readFile(file);

}

}
