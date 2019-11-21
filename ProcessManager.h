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
#include <queue>

#include "Process.h"

namespace sisops{
    struct PageIdentifier{
        const int process_id;
        const int page;
        PageIdentifier(const int process,const int page_id):process_id(process),page(page_id){};
    };

class ProcessManager {
 public:
    ~ProcessManager();
    void doProcess();

 private:
    void create();
    void access();
    void free();
    void reset();
    void exit();
    std::queue<PageIdentifier> fifo;
    std::queue<PageIdentifier> lru;
    std::vector<Process> processes;
};


}