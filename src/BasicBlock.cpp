#include "BasicBlock.h"

BasicBlock::BasicBlock(string entry_label) {
    this->exit_true = nullptr;
    this->exit_false = nullptr;
    this->label = entry_label;
    this->test_var_index = 0;
}

void BasicBlock::add_instr(Instr* instr) {
    this->instrs.push_back(instr);
}

void BasicBlock::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}
