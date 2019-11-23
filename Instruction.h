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
}

class LoadInstruction : public Instruction {
 public:
    LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id);
 private:
    int bytes_;
    int id_;
};

LoadInstruction::LoadInstruction(const std::string& type,const std::string& bytes, const std::string& id) {
    instruction_type = GetInstructionType(type);
    bytes_ = std::stoi(bytes);
    id_ = std::stoi(id);
}

class AccessInstruction : public Instruction {
 public:
    AccessInstruction(const std::string& type,const std::string& virtual_address, const std::string& id, const std::string& option);
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

class FreeInstruction : public Instruction {
 public:
    FreeInstruction(const std::string& type,const std::string& id);
 private:
    int id_;
};

FreeInstruction::FreeInstruction(const std::string& type,const std::string& id) {
    instruction_type = GetInstructionType(type);
    id_ = std::stoi(id);
}

class CommentInstruction : public Instruction {
 public:
    CommentInstruction(const std::string& type,const std::string& comment);
 private:
    std::string comment_;
};

CommentInstruction::CommentInstruction(const std::string& type,const std::string& comment) {
    instruction_type = GetInstructionType(type);
    comment_ = comment;
}

class FinalizeInstruction : public Instruction {
 public:
    FinalizeInstruction(const std::string& type);
};

FinalizeInstruction::FinalizeInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}

class ExitInstruction : public Instruction {
 public:
    ExitInstruction(const std::string& type);
};

ExitInstruction::ExitInstruction(const std::string& type) {
    instruction_type = GetInstructionType(type);
}
}
