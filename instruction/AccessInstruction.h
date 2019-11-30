#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class AccessInstruction : public Instruction {
 public:
    AccessInstruction(const std::string& type,const std::string& virtual_address, const std::string& id, const std::string& option);
    int GetVirtualAddress();
    int GetId();
    int GetOption();
 private:
    int virtual_address_;
    int id_;
    int option_;
};

AccessInstruction::AccessInstruction(const std::string& type,const std::string& virtual_address, const std::string& id, const std::string& option) {
    instruction_type = GetInstructionType(type);
    virtual_address_ = std::stoi(virtual_address);
    id_ = std::stoi(id);
    option_ = std::stoi(option);
}

inline int AccessInstruction::GetVirtualAddress() {
    return virtual_address_;
}

inline int AccessInstruction::GetId() {
    return id_;
}

inline int AccessInstruction::GetOption() {
    return option_;
}
}