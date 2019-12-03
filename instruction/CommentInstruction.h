#pragma once

#include <string>

#include "Instruction.h"

namespace sisops {
class CommentInstruction : public Instruction {
 public:
    CommentInstruction(const std::string& type,const std::string& comment);
    std::string GetComment();
 private:
    std::string comment_;
};
/*
Function: CommentInstruction::CommentInstruction
    This function access the instruction
Parameters: const std::string& type,const std::string& comment
Return: -
*/
CommentInstruction::CommentInstruction(const std::string& type,const std::string& comment) {
    instruction_type = GetInstructionType(type);
    comment_ = comment;
}
/*
Function: CommentInstruction::GetComment()
    This function gets the comment
Parameters: const std::string& type,const std::string& comment
Return: string
*/
std::string CommentInstruction::GetComment() {
    return comment_;
}
}