#pragma once
#include <string>

namespace sisops {

enum class InstructionType {
    Load,
    Access,
    Free,
    Comment,
    Finalize,
    Exit
};

class Instruction {
 public:
    virtual ~Instruction(){}
 protected:
    InstructionType instruction_type;
    InstructionType GetInstructionType(const std::string& type);
};

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
    //TODO: Verify warning
    // ./process_manager/../instruction/Instruction.h:42:1: warning: control may reach end of non-void function [-Wreturn-type]
    // }
}

}
