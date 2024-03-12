#include "Instr.h"

using namespace std;

void ConstInstr::gen_asm(std::ostream &o) {
    o << "    movl $" << value << ", " << dest << "(%rbp)\n";
}

void CopyInstr::gen_asm(std::ostream &o) {
    o << "    movl " << src << "(%rbp), %eax\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void AddInstr::gen_asm(std::ostream &o) {
    o << "    movl " << term1 << "(%rbp), %eax\n";
    o << "    addl " << term2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void SubInstr::gen_asm(std::ostream &o) {
    o << "    movl " << term1 << "(%rbp), %eax\n";
    o << "    subl " << term2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void MulInstr::gen_asm(std::ostream &o) {
    o << "    movl " << factor1 << "(%rbp), %eax\n";
    o << "    imull " << factor2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void DivInstr::gen_asm(std::ostream &o) {
    o << "    movl " << numerator << "(%rbp), %eax\n";
    o << "    cltd\n";
    o << "    idivl " << denominator << "(%rbp)\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void NegInstr::gen_asm(std::ostream &o) {
    o << "    movl " << src << "(%rbp), %eax\n";
    o << "    negl %eax\n";
    o << "    movl %eax, " << dest << "(%rbp)\n";
}

void LessEqCmpInstr::gen_asm(std::ostream &o) {
    o << "    movl " << term1 << "(%rbp), %eax\n";
    o << "    cmpl " << term2 << "(%rbp), %eax\n";
    o << "    setle " << "%al\n";
    o << "    movzbl " << "%al, %eax\n";
}
void GreaterEqCmpInstr::gen_asm(std::ostream &o) {

}
void LessCmpInstr::gen_asm(std::ostream &o) {

}
void GreaterCmpInstr::gen_asm(std::ostream &o) {

}

void RetInstr::gen_asm(std::ostream &o) {
    o << "    movl " << var << "(%rbp), %eax\n";
}
