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

//void LessEqCmpInstr::gen_asm(std::ostream &o) {
//    o << "    movl " << term1 << "(%rbp), %eax\n";
//    o << "    cmpl " << term2 << "(%rbp), %eax\n";
//    o << "    setle " << "%al\n";
//    o << "    movzbl " << "%al, %eax\n";
//}
//void GreaterEqCmpInstr::gen_asm(std::ostream &o) {
//
//}
//void LessCmpInstr::gen_asm(std::ostream &o) {
//
//}
//void GreaterCmpInstr::gen_asm(std::ostream &o) {
//
//}
