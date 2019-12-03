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

int GetNextFinalize(std::vector<std::vector<sisops::Token>> token_list, int init) {
    int i = init;
    while ((token_list[i][0].token_type != sisops::TokenType::Finalize && token_list[i][0].token_type != sisops::TokenType::Exit) && i < token_list.size()) {
        i++;
    }

    return i;
}

// Function: Main
// It handles the input, the process of counting the archives and the output for the program.
// Parameters: -
// Return: Int, describing the correct compilation of the program
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " < -f | -l >" << std::endl;
        exit(1);
    }

    bool fifo = argv[1][1] == 'f';

    auto result = sisops::readAndParseInputFile("real_test.txt");
    std::vector<std::vector<sisops::Token>> token_list = std::get<0>(result);
    std::vector<sisops::Error> errors = std::get<1>(result);

    // If there is an error, display message of error. Else, display a message that displays
    // that there are no errors
    if (errors.size() > 0) {
        std::cout << "-----------------SYNTAX ERROR-----------------" << std:: endl;
        for (const sisops::Error& e: errors) {
            std::cout << "PARSER: Line " << e.line+1 << ": " << e.message << std::endl;
            token_list.erase(token_list.begin()+e.line);
        }
        std::cout << std::endl << "WARNING: PARSING ERRORS. CONTINUING OMITING LINES WITH ERRORS" << std::endl << std::endl;
    } else {
        std::cout << "PARSER: File free from errors" << std::endl;
    }


    sisops::ProcessManager pm(fifo);

    // Process each instruction.
    for (int i = 0; i < token_list.size(); i++) {
        sisops::OperationStatus result = pm.DoProcess(token_list[i]);
        for (const std::string& message : result.messages_) {
            std::cout << message << std::endl;
        }
        // If there's an error, display error message

        if (result.critical_error_) {
            std::cout << "-----------CRITICAL ERROR------------" << std::endl;
            std::cout << "Jumping to next block of instructions after next F instruction..." << std::endl;
            int finalize_position = GetNextFinalize(token_list, i);
            i = finalize_position;
            pm.DoProcess(token_list[i]);
        } else { 
            // Nothing.
        }
        std::cout << std::endl;
    }
}