// ProcessManager.h
// The header handles all the input phases of the program from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "Process.h"
#include "../Token.h"
#include "../instruction/InstructionFactory.h"

namespace sisops{
struct PageIdentifier{
    const int process_id;
    const int page;
    PageIdentifier(const int process,const int page_id):process_id(process),page(page_id){};
};

class ProcessManager {
 private:
    std::queue<PageIdentifier> fifo;
    std::queue<PageIdentifier> lru;
    std::vector<Process> processes;
    InstructionFactory factory;
    // Loads a process into real memory.
    void Load(const std::shared_ptr<Instruction> current_instruction);
    // Tries to access a frame in memory, performs swap if needed.
    void Access(const std::shared_ptr<Instruction> current_instruction);
    // Displays a comment on screen.
    void Comment(const std::shared_ptr<Instruction> current_instruction);
    // Ends the execution of a process, freeing the memory it was using.
    void Free(const std::shared_ptr<Instruction> current_instruction);
    // Finalizes the current cicle of instructions, displays some information.
    void Finalize(const std::shared_ptr<Instruction> current_instruction);
    // Exits the program.
    void Exit(const std::shared_ptr<Instruction> current_instruction);
 public:
    ~ProcessManager();
    void DoProcess(std::vector<Token> instruction);
};


}