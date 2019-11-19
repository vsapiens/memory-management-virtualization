// ProcessManager.h
// The header handles all the input phases of the program
// from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada
// Moisés Fernández
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <fstream>
#include <string>
#include <vector>

namespace sisops{

class ProcessManager {
public:
ProcessManager(std::string& file);
ProcessManager(std::string&& file);
~ProcessManager();

void initialize();

private:
const std::string file_;
std::vector<std::string> instructions_;
};

ProcessManager::ProcessManager(std::string& file):file_(file){}
ProcessManager::ProcessManager(std::string&& file):file_(file){}

void ProcessManager::initialize() {
    std::ifstream input;
    input.open(file_);

    std::string buffer;
    while (std::getline(input, buffer)) {
        instructions_.push_back(buffer);
    }

    input.close();
}

}