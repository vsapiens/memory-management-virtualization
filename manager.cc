// manager.cc
// This program is the main that handles the process manager of memory and the output handler.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#include <iostream>
#include "ProcessManager.h"
#include "Reader.h"
#include "Token.h"

// Function: Main
// It handles the input, the process of counting the archives and the output for the program.
// Parameters: -
// Return: Int, describing the correct compilation of the program
int main()
{
    //std::vector<std::vector<sisops::Token>> tokenized_instructions = sisops::readInputFile("file.txt");
    std::string input;
    std::getline(std::cin, input);
    sisops::Scanner scanner;
    std::vector<sisops::Token> tokens = scanner.scan(input);
    for (const sisops::Token& token : tokens) {
        std::cout << token.value << "\t" <<  sisops::token_type_to_string(token.token_type) << std::endl;
    }
    return 0;
}