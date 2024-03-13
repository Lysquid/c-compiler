#include "Instr.h"
#include "IRVisitor.h"

using namespace std;

void ConstInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void CopyInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void AddInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void SubInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void MulInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void DivInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void NegInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void RetInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void CmpInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void BitInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}
