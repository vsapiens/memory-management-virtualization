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

CommentInstruction::CommentInstruction(const std::string& type,const std::string& comment) {
    instruction_type = GetInstructionType(type);
    comment_ = comment;
}

std::string CommentInstruction::GetComment() {
    return comment_;
}
}