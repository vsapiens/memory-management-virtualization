#pragma once
#include <string>

#include "Instruction.h"

namespace sisops {
class LoadInstruction : public Instruction {
 public:
    LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id);
    ~LoadInstruction(){};
    int GetBytes();
    int GetId();
 private:
    //Number of bytes
    int bytes_;
    //The id of the process
    int id_;
};
/*
Function: LoadInstruction::LoadInstruction
    This function loads the instruction
Parameters: const std::string& type,const std::string& bytes, const std::string& id
Return: -
*/
LoadInstruction::LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id) {
    instruction_type = GetInstructionType(type);
    bytes_ = std::stoi(bytes);
    id_ = std::stoi(id);
}
/*
Function: LoadInstruction::GetBytes()
    This function gets the bytes
Parameters: -
Return: bytes_
*/
inline int LoadInstruction::GetBytes() {
    return bytes_;
}
/*
Function: LoadInstruction::GetId()
    This function gets the id
Parameters: -
Return: id_
*/
inline int LoadInstruction::GetId() {
    return id_;
}
}