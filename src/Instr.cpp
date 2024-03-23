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

void ModInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void IncrementafterInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void IncrementbeforeInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void DecrementafterInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void DecrementbeforeInstr::accept(IRVisitor &visitor) {
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

void NotInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void BitInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}
void PutcharInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void GetcharInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}


void CopyparamInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void SetparamInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void CallfunctionInstr::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}
