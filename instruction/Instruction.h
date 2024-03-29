#pragma once
#include <string>

namespace sisops {

enum class InstructionType {
    Load,
    Access,
    Free,
    Comment,
    Finalize,
    Exit,
    Unset
};

class Instruction {
 public:
    virtual ~Instruction(){}
 protected:
    InstructionType instruction_type;
    InstructionType GetInstructionType(const std::string& type);
};
/*
Function: Instruction::GetInstructionType
    This functions gets the instruction type
Parameters: const std::string& type
Return: InstructionType
*/
InstructionType Instruction::GetInstructionType(const std::string& type) {
    if(type == "P") {
        return InstructionType::Load;
    }
    if(type == "A") {
        return InstructionType::Access;
    }
    if(type == "L") {
        return InstructionType::Free;
    }
    if(type == "C") {
        return InstructionType::Comment;
    }
    if(type == "F") {
        return InstructionType::Finalize;
    }
    if(type == "E") {
        return InstructionType::Exit;
    }
    return InstructionType::Unset;
}

}
