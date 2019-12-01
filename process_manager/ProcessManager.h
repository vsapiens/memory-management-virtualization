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
#include "../PageSize.h"
#include "../reader/Token.h"
#include "../instruction/Instruction.h"
#include "../instruction/InstructionFactory.h"

namespace sisops{

struct OperationStatus {
    bool success;
    std::string message;

    OperationStatus() {
        success = true;
        message = "";
    }
};

struct PageIdentifier{
    int process_id;
    int page;
    PageIdentifier(const int process,const int page_id):process_id(process),page(page_id){};
    PageIdentifier():process_id(-1),page(-1){};

    void operator = (const PageIdentifier &p) { 
        this->process_id = p.process_id;
        this->page = p.page;
    }

    bool operator == (const PageIdentifier& p) {
        return this->process_id == p.process_id && this->page == p.page;
    }
};

struct Frame {
    bool free;
    PageIdentifier page_identifier;

    Frame() {
        free = true;
    }
};

class ProcessManager {
 private:
    std::queue<PageIdentifier> fifo;
    std::queue<PageIdentifier> lru;
    std::vector<Process> processes; // Consider changing this to a map for constant access.
    InstructionFactory factory;
    std::vector<Frame> real_memory;
    std::vector<Frame> swapping_memory;
    bool is_fifo;
    // Loads a process into real memory.
    OperationStatus Load(const std::shared_ptr<Instruction> current_instruction);
    // Tries to access a frame in memory, performs swap if needed.
    OperationStatus Access(const std::shared_ptr<Instruction> current_instruction);
    // Displays a comment on screen.
    OperationStatus Comment(const std::shared_ptr<Instruction> current_instruction);
    // Ends the execution of a process, freeing the memory it was using.
    OperationStatus Free(const std::shared_ptr<Instruction> current_instruction);
    // Finalizes the current cicle of instructions, displays some information.
    OperationStatus Finalize(const std::shared_ptr<Instruction> current_instruction);
    // Exits the program.
    OperationStatus Exit(const std::shared_ptr<Instruction> current_instruction);
    // Checks if the id of a process has already been loaded.
    bool ProcessExists(int id);
    // Gets the frame number of the next process in line, whether it's fifo or lru. This
    // function asumes that the page returned by either fifo or lru is indeed in real memory.
    // If it is not, -1 is returned.
    int GetNextVictimFrameNumber();
    // Returns the first free frame in the swapping memory. User must first check that
    // free spaces exist in the swapping memory using SwappingMemoryFull. It will return -1
    // otherwise.
    int GetFreeSwappingFrame();
    // Checks whether all of the real memory's pages have already been used 
    bool RealMemoryFull();
    // Checks whether all of the swapping memory's pages have already been used 
    bool SwappingMemoryFull();
    // Swaps an existing page with the current page and returns the page's new frame number 
    void SwapPage(PageIdentifier new_page); 

    void InsertPage(PageIdentifier new_page);

    void AddToQueue(PageIdentifier new_page);
 public:
    ProcessManager(bool is_fifo);
    OperationStatus DoProcess(std::vector<Token> instruction);
};


}