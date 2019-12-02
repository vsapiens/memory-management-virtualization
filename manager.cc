// manager.cc
// This program is the main that handles the process manager of memory and the output handler.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#include <iostream>
#include <memory>
#include <tuple>
#include "process_manager/ProcessManager.h"
#include "reader/Reader.h"

// Function: Main
// It handles the input, the process of counting the archives and the output for the program.
// Parameters: -
// Return: Int, describing the correct compilation of the program
int main()
{
    auto result = sisops::readAndParseInputFile("test2.txt");
    std::vector<std::vector<sisops::Token>> token_list = std::get<0>(result);
    std::vector<sisops::Error> errors = std::get<1>(result);

    if (errors.size() > 0) {
        std::cout << "-----------------SYNTAX ERROR-----------------" << std:: endl;
        for (const sisops::Error& e: errors) {
            std::cout << "PARSER: Line " << e.line << ": " << e.message << std::endl;
        }
        exit(1);
    } else {
        std::cout << "PARSER: File free from errors" << std::endl;
    }

    sisops::ProcessManager pm(true);

    for (const std::vector<sisops::Token>& tokens : token_list) {
        sisops::OperationStatus result = pm.DoProcess(tokens);
        for (const std::string& message : result.messages) {
            std::cout << message << std::endl;
        }
    }
}