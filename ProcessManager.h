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
#include <string>
#include <vector>
#include <fstream>

class ProcessManager {
    public:
    ProcessManager(std::string);
    ~ProcessManager();

    void initialize();

    private:
    std::string file;
    std::vector<std::string> instructions;
};

ProcessManager::ProcessManager(std::string file) {
    this->file = file;
}

void ProcessManager::initialize() {
    std::ifstream input;
    input.open(file);

    std::string buffer;
    while (std::getline(input, buffer)) {
        instructions.push_back(buffer);
    }

    input.close();
}