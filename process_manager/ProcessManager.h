// ProcessManager.h
// The header handles all the input phases of the program from the name of the file to the input of the file.
// Authors:
// Erick Gonzalez A01039589
// Francisco Sánchez A01196903
// Carlos Estrada A01039919
// Moisés Fernández A01197049
// Version: 1.0 last modified 14/11/2019
#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>

#include "Process.h"
#include "../PageSize.h"
#include "../reader/Token.h"
#include "../instruction/Instruction.h"
#include "../instruction/InstructionFactory.h"

namespace sisops{

struct OperationStatus {
    bool success;
    std::vector<std::string> messages;

    OperationStatus() {
        success = true;
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
    std::unordered_map<int, Process> processes; // Consider changing this to a map for constant access.
    InstructionFactory factory;
    std::vector<Frame> real_memory;
    std::vector<Frame> swapping_memory;
    bool is_fifo;
    double time;
    int swap_operations;
    OperationStatus current_status;
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

    int FindFrameNumberSwap(PageIdentifier p);
 public:
    ProcessManager(bool is_fifo);
    OperationStatus DoProcess(std::vector<Token> instruction);
};


ProcessManager::ProcessManager(bool b) : real_memory(real_memory_page_amount),
    swapping_memory(swapping_memory_page_amount), is_fifo(b), time(0.0) {}

// Checks if the id of a process has already been loaded.
bool ProcessManager::ProcessExists(int id) {
    return processes.find(id) != processes.end();
}

// Gets the frame number of the next process in line, whether it's fifo or lru. This
// function asumes that the page returned by either fifo or lru is indeed in real memory.
// If it is not, -1 is returned. Also, this function modifies either the fifo or lru queue.
// Thus it must only be called once per swap.
int ProcessManager::GetNextVictimFrameNumber() {
    PageIdentifier victim_page;
    if (is_fifo) {
        victim_page = fifo.front();
        fifo.pop();
    } else {
        victim_page = lru.front();
        lru.pop();
    }

    for (int i = 0; i < real_memory.size(); i++) {
        if (real_memory[i].page_identifier == victim_page) {
            return i;
        }
    }

    return -1;
}

// Returns the first free frame in the swapping memory. User must first check that
// free spaces exist in the swapping memory using SwappingMemoryFull. It will return -1
// otherwise.
int ProcessManager::GetFreeSwappingFrame() {
    for (int i = 0; i < swapping_memory.size(); i++) {
        if (swapping_memory[i].free) {
            return i;
        }
    }

    return -1;
}

// Checks whether all of the real memory's pages have already been used 
bool ProcessManager::RealMemoryFull() {
    for (const Frame &f : real_memory) {
        if (f.free) {
            return false;
        }
    }

    return true;
}

// Checks whether all of the swapping memory's pages have already been used 
bool ProcessManager::SwappingMemoryFull() {
    for (const Frame &f : swapping_memory) {
        if (f.free) {
            return false;
        }
    }

    return true;
}

void ProcessManager::AddToQueue(PageIdentifier new_page) {
    if (is_fifo) {
        fifo.push(new_page);
    } else {
        lru.push(new_page);
    }
}

int ProcessManager::FindFrameNumberSwap(PageIdentifier p) {
    for (int i = 0; i < swapping_memory.size(); i++) {
        if (swapping_memory[i].page_identifier == p) {
            return i;
        }
    }

    return -1;
}

// Swaps an existing page with the current page and returns the page's new frame number 
void ProcessManager::SwapPage(PageIdentifier new_page) {
    int victim_frame_number = GetNextVictimFrameNumber();
    int swapping_frame_number = GetFreeSwappingFrame();

    swapping_memory[swapping_frame_number].page_identifier = real_memory[victim_frame_number].page_identifier;
    real_memory[victim_frame_number].page_identifier = new_page;

    int victim_pid = swapping_memory[swapping_frame_number].page_identifier.process_id;
    int victim_page = swapping_memory[swapping_frame_number].page_identifier.process_id;

    processes.find(victim_pid)->second.setValid(victim_page, false);

    processes.find(new_page.process_id)->second.setValid(new_page.page, true);
    processes.find(new_page.process_id)->second.setFrameNumber(new_page.page, victim_frame_number);

    AddToQueue(new_page);

    swap_operations++;
    time += 0.1;
}

// Insert a page into real memory. This function assumes that the real memory has at
// least one free page. This function must be called after making sure of this by calling
// RealMemoryFull.
void ProcessManager::InsertPage(PageIdentifier new_page) {
    int new_frame_number = 0;
    for (int i = 0; i < real_memory.size(); i++) {
        if (real_memory[i].free) {
            real_memory[i].page_identifier = new_page;
            real_memory[i].free = false;
            new_frame_number = i;
        }
    }

    processes.find(new_page.process_id)->second.setValid(new_page.page, true);
    processes.find(new_page.process_id)->second.setFrameNumber(new_page.page, new_frame_number);

    AddToQueue(new_page);
}

void ProcessManager::Load(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<LoadInstruction>(current_instruction);
    int id = instruction->GetId();
    int size = instruction->GetBytes();

    current_status.messages.push_back("P"); 
    current_status.messages.push_back("Assigning " + std::to_string(size) + " bytes to the process " + std::to_string(id));

    if (ProcessExists(id)) {
        current_status.success = false;
        current_status.messages.push_back("Tried to load existent process");
        return;
    }

    if (size > real_memory_size) {
        current_status.success = false;
        current_status.messages.push_back("Process bigger than real memory");
        return;
    }

    int frame_amount = (int) ceil( (double) size / (double) page_size);

    Process p(id, size, frame_amount);
    processes.insert(std::make_pair(id, p));

    // We insert a new page for each frame amount, starting the page's id at 0 until
    // frame_amount - 1.
    for (int i = 0; i < frame_amount; i++) {
        PageIdentifier new_page(id, i);
        if (RealMemoryFull()) {
            // This will cause a runtime error since both the real and swapping memory are
            // full so there is no space to swap anymore.
            if (SwappingMemoryFull()) {
                current_status.success = false;
                current_status.messages.push_back("Real memory and swapping memory full");
                return;
            }
            SwapPage(new_page);
        } else {
            InsertPage(new_page);
        }
    }

    current_status.success = true;
    current_status.messages.push_back("Process " + std::to_string(id) + " loaded correctly");
}

void ProcessManager::Access(const std::shared_ptr<Instruction> current_instruction) {

    auto instruction = std::dynamic_pointer_cast<AccessInstruction>(current_instruction);
    int id = instruction->GetId();
    int virtual_address = instruction->GetVirtualAddress();
    int option = instruction->GetOption();

    current_status.messages.push_back("A"); 
    current_status.messages.push_back("Accessing the real memory address according to the virtual address of " + std::to_string(virtual_address)+ ".");

    //If the option also writes/modifies it must declare that it does.
    if(option == 1){
        current_status.messages.push_back("Modifying the address given.");
    }
    // Throws an error message when accesing a non-existing progress
    if(!ProcessExists(id)){
        current_status.success = false;
        current_status.messages.push_back("Tried to access a non-existing process.");
        return;
    }
    // Throws an error message if the address is out of range
    if(virtual_address < 0) //TODO: Also check if the page_size * the number of frames is out of range
    {
        current_status.success = false;
        current_status.messages.push_back("The virtual address given is out of the range of the processes' addresses.");
        return;
    }
    
    //Calculates the page and displacement of the tuple v = (p,d)
    int page = std::floor(virtual_address / page_size);
    int displacement = virtual_address % page_size;

    // Check if page is not in real memory
    if (!processes.find(id)->second.getValid(page)) {
        // If it is not, then find its address in the swapping memory
        PageIdentifier p(id, page);
        int swapping_frame = FindFrameNumberSwap(p);
        // Then set it to free
        swapping_memory[swapping_frame].free = true;
        // Now call SwapPage, which will automatically choose a page from real memory
        // to swap and will insert the new page
        SwapPage(p);
    } else {
        // Page in memory, so no operation is needed
    }

    current_status.success = true;
    current_status.messages.push_back("Real Memory Address " + std::to_string(virtual_address) + " = (" + std::to_string(page)+ " , "+ std::to_string(displacement) + ")");
}

void ProcessManager::Free(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FreeInstruction>(current_instruction);
    int id = instruction->GetId();
    std::queue<PageIdentifier> temp;

    if(!ProcessExists(id)){
        current_status.success = false;
        current_status.messages.push_back("Tried to free a non-existing process.");
        return;
    }

    // Set the frames of the swapping and real memory as free if they belong to the process.
    for (int i = 0; i < swapping_memory.size(); i++) {
        if(!swapping_memory[i].free && swapping_memory[i].page_identifier.process_id == id) {
            swapping_memory[i].free = true;
        }
    }

    for (int i = 0; i < real_memory.size(); i++) {
        if(!real_memory[i].free && real_memory[i].page_identifier.process_id == id) {
            real_memory[i].free = true;
        }
    }

    // If they are different processes, push them into another queue.
    if (is_fifo) {
        while (!fifo.empty()) {
            if (fifo.front().process_id != id) {
                temp.push(fifo.front());
            }
            
            fifo.pop();
        }

        fifo = temp;
    }
    else {
        while (!lru.empty()) {
            if (lru.front().process_id != id) {
                temp.push(lru.front());
            }
            
            lru.pop();
        }

        lru = temp;
    }

    current_status.success = true;
    current_status.messages.push_back("The pages of the process are available for other operations.");
}

void ProcessManager::Comment(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<CommentInstruction>(current_instruction);
    std::string comment = instruction->GetComment();

    current_status.messages.push_back("C"); 
    current_status.success = true;
    current_status.messages.push_back(comment); 
    /* TODO: The reader only reads the first word of the comment given
            test2.txt:
                Expected Output: archivo de prueba para FIFO, LRU
                Given Output:    archivo 
    */
}

void ProcessManager::Finalize(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FinalizeInstruction>(current_instruction);

    current_status.messages.push_back("F");
    current_status.messages.push_back("Swap In/Out Operations: " + std::to_string(swap_operations));

}

void ProcessManager::Exit(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<ExitInstruction>(current_instruction);

    current_status.messages.push_back("E");
    current_status.success = true;
    current_status.messages.push_back("End of instuctions.");
}

OperationStatus ProcessManager::DoProcess(std::vector<Token> instruction) {
    TokenType token_type = instruction[0].token_type;
    std::shared_ptr<Instruction> current_instruction = factory.MakeInstruction(instruction);
    
    // Reset current status for new operation
    current_status.success = true;
    current_status.messages.clear();

    switch (token_type) {
        case TokenType::Load: {
            Load(std::move(current_instruction));
        }
        break;
        case TokenType::Access: {
            Access(std::move(current_instruction));
        }
        break;
        case TokenType::Free: {
            Free(std::move(current_instruction));
        }
        break;
        case TokenType::Comment: {
            Comment(std::move(current_instruction));
        }
        break;
        case TokenType::Finalize: {
            Finalize(std::move(current_instruction));
        }
        break;
        case TokenType::Exit: {
            Exit(std::move(current_instruction));
        }
        break;
        default: {

        }
        break;
    }

    return current_status;
}

}