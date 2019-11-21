#include <vector>
#include <string>
#include <fstream>

namespace sisops{

namespace {

}

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
