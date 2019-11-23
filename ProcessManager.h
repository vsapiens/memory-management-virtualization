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
#include "Token.h"

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

    void Load(std::vector<Token>& instruction);
    void Create(std::vector<Token>& instruction);
    void Access(std::vector<Token>& instruction);
    void Free(std::vector<Token>& instruction);
    void Finalize();
    void Exit();
 public:
    ~ProcessManager();
    void DoProcess(std::vector<Token> instruction);
};


}