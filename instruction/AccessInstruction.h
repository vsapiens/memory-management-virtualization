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
    //Virtual address
    int virtual_address_; 
    //Id given
    int id_;
    //Option selected
    int option_;
};
/*
Function: AccessInstruction::AccessInstruction
    This function access the instruction
Parameters: (const std::string& type,const std::string& virtual_address, const std::string& id, const std::string& option)
Return: AccessInstruction
*/
AccessInstruction::AccessInstruction(const std::string& type,const std::string& virtual_address, const std::string& id, const std::string& option) {
    instruction_type = GetInstructionType(type);
    virtual_address_ = std::stoi(virtual_address);
    id_ = std::stoi(id);
    option_ = std::stoi(option);
}
/*
Function: AccessInstruction::GetVirtualAddress()
    This function gets the virtual address
Parameters: -
Return: int
*/
inline int AccessInstruction::GetVirtualAddress() {
    return virtual_address_;
}
/*
Function: AccessInstruction::GetId() 
    This function getd the id
Parameters: -
Return: int
*/
inline int AccessInstruction::GetId() {
    return id_;
}
/*
Function: AccessInstruction::GetOption() 
    This function gets the option
Parameters: -
Return: int
*/
inline int AccessInstruction::GetOption() {
    return option_;
}
}