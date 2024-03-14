#include "BasicBlock.h"


void BasicBlock::add_instr(Instr* instr) {
    this->instrs.push_back(instr);
}

void BasicBlock::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}
