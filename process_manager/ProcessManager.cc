#pragma once
#include <memory>
#include <vector>
#include <cmath>

#include "PageSize.h"
#include "ProcessManager.h"
#include "../Reader/Token.h"
#include "instruction/Instruction.h"
#include "instruction/InstructionFactory.h"

namespace sisops {

ProcessManager::ProcessManager(bool b) : real_memory(real_memory_page_amount),
    swapping_memory(swapping_memory_page_amount) {
    is_fifo = b;
    }

// Checks if the id of a process has already been loaded.
bool ProcessManager::ProcessExists(int id) {
    for (const Process& p : processes) {
        if (p.getId() == id) {
            return true;
        } 
    }

    return false;
}

// Gets the frame number of the next process in line, whether it's fifo or lru. This
// function asumes that the page returned by either fifo or lru is indeed in real memory.
// If it is not, -1 is returned. Also, this function modifies either the fifo or lru queue.
// Thus it must only be called once per swap.
int ProcessManager::GetNextVictimFrameNumber() {
    if (is_fifo) {
        PageIdentifier victim_page = fifo.front();
        fifo.pop();
    } else {
        PageIdentifier victim_page = lru.front();
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

// Swaps an existing page with the current page and returns the page's new frame number 
void ProcessManager::SwapPage(PageIdentifier new_page) {
    int victim_frame_number = GetNextVictimFrameNumber();
    int swapping_frame_number = GetFreeSwappingFrame();

    swapping_memory[swapping_frame_number].page_identifier = real_memory[victim_frame_number].page_identifier;
    real_memory[victim_frame_number].page_identifier = new_page;

    int victim_pid = swapping_memory[swapping_frame_number].page_identifier.process_id;
    int victim_page = swapping_memory[swapping_frame_number].page_identifier.process_id;

    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].getId() == victim_pid) {
            processes[i].setValid(victim_page, false);
        }

        // Maybe we can make this its own function since it is repeated in the
        // InsertPage function
        if (processes[i].getId() == new_page.process_id) {
            processes[i].setValid(new_page.page, true);
            processes[i].setFrameNumber(new_page.page, victim_frame_number);
        }
    }

    AddToQueue(new_page);
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

    for (int i = 0; i < processes.size(); i++) {
        if (processes[i].getId() == new_page.process_id) {
            processes[i].setValid(new_page.page, true);
            processes[i].setFrameNumber(new_page.page, new_frame_number);
        }
    }

    AddToQueue(new_page);
}

OperationStatus ProcessManager::Load(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<LoadInstruction>(current_instruction);
    int id = instruction->GetId();
    int size = instruction->GetBytes();

    OperationStatus status;

    if (ProcessExists(id)) {
        status.success = false;
        status.message = "Tried to load existent process";
        return status;
    }

    if (size > real_memory_size) {
        status.success = false;
        status.message = "Process bigger than real memory";
        return status;
    }

    int frame_amount = (int) ceil( (double) size / (double) page_size);

    Process p(id, size, frame_amount);
    processes.push_back(p);


    // We insert a new page for each frame amount, starting the page's id at 0 until
    // frame_amount - 1.
    for (int i = 0; i < frame_amount; i++) {
        PageIdentifier new_page(id, i);
        if (RealMemoryFull()) {
            // This will cause a runtime error since both the real and swapping memory are
            // full so there is no space to swap anymore.
            if (SwappingMemoryFull()) {
                status.success = false;
                status.message = "Real memory and swapping memory full";
                return status;
            }
            SwapPage(new_page);
        } else {
            InsertPage(new_page);
        }
    }

    status.success = true;
    status.message = "Process " + std::to_string(id) + " loaded correctly";

    return status;
}
OperationStatus ProcessManager::Access(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<AccessInstruction>(current_instruction);
}
OperationStatus ProcessManager::Free(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FreeInstruction>(current_instruction);
}
OperationStatus ProcessManager::Comment(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<CommentInstruction>(current_instruction);
}
OperationStatus ProcessManager::Finalize(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<FinalizeInstruction>(current_instruction);
}
OperationStatus ProcessManager::Exit(const std::shared_ptr<Instruction> current_instruction) {
    auto instruction = std::dynamic_pointer_cast<ExitInstruction>(current_instruction);
}
OperationStatus ProcessManager::DoProcess(std::vector<Token> instruction) {
    TokenType token_type = instruction[0].token_type;
    std::shared_ptr<Instruction> current_instruction = factory.MakeInstruction(instruction);
    OperationStatus status;
    switch (token_type) {
        case TokenType::Load: {
            return Load(std::move(current_instruction));
        }
        break;
        case TokenType::Access: {
            return Access(std::move(current_instruction));
        }
        break;
        case TokenType::Free: {
            return Free(std::move(current_instruction));
        }
        break;
        case TokenType::Comment: {
            return Comment(std::move(current_instruction));
        }
        break;
        case TokenType::Finalize: {
            return Finalize(std::move(current_instruction));
        }
        break;
        case TokenType::Exit: {
            return Exit(std::move(current_instruction));
        }
        break;
        default: {

        }
        break;
    }
}
}
