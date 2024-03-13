#include "x86Visitor.h"

void x86Visitor::visit(CFG &cfg) {
    gen_prologue();
    for (auto bb: cfg.bbs) {
        bb->accept(*this);
    }
    gen_epilogue();
}

void x86Visitor::gen_prologue() {
    o << ".globl main\n";
    o << " main: \n";
    o << "    pushq %rbp\n";
    o << "    movq %rsp, %rbp\n";
}

void x86Visitor::gen_epilogue() {
    o << "    popq %rbp\n";
    o << "    ret\n";
}

void x86Visitor::visit(BasicBlock &bb) {
    for (auto instr: bb.instrs) {
        instr->accept(*this);
    }
    if (!bb.exit_true) {
        return;
    } else if (!bb.exit_false) {
        o << "    jmp " << bb.exit_true->get_label() << "\n";
    } else {
        o << "    cmpl $0, " << bb.test_var_name << "(%rbp)\n";
        o << "    je " << bb.exit_false->get_label() << "\n";
        o << "    jmp " << bb.exit_true->get_label() << "\n";
    }
}

void x86Visitor::visit(ConstInstr &i) {
    o << "    movl $" << i.value << ", " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(CopyInstr &i) {
    o << "    movl " << i.src << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(AddInstr &i) {
    o << "    movl " << i.term1 << "(%rbp), %eax\n";
    o << "    addl " << i.term2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(SubInstr &i) {
    o << "    movl " << i.term1 << "(%rbp), %eax\n";
    o << "    subl " << i.term2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(MulInstr &i) {
    o << "    movl " << i.factor1 << "(%rbp), %eax\n";
    o << "    imull " << i.factor2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(DivInstr &i) {
    o << "    movl " << i.numerator << "(%rbp), %eax\n";
    o << "    cltd\n";
    o << "    idivl " << i.denominator << "(%rbp)\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(ModInstr &i) {
    o << "    movl " << i.numerator << "(%rbp), %eax\n";
    o << "    cltd\n";
    o << "    idivl " << i.denominator << "(%rbp)\n";
    o << "    movl %edx, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(NegInstr &i) {
    o << "    movl " << i.src << "(%rbp), %eax\n";
    o << "    negl %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(CmpInstr &i) {
    o << "    movl " << i.term1 << "(%rbp), %eax\n";
    o << "    cmpl " << i.term2 << "(%rbp), %eax\n";
    o << "    set";
    switch (i.cmp) {
        case CmpInstr::e:
            o << "e";
            break;
        case CmpInstr::g:
            o << "g";
            break;
        case CmpInstr::ge:
            o << "ge";
            break;
        case CmpInstr::l:
            o << "l";
            break;
        case CmpInstr::le:
            o << "le";
            break;
    }
    o << " %al\n";
    o << "    movzbl %al, %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(BitInstr &i) {
    o << "    movl " << i.term1 << "(%rbp), %eax\n";
    switch (i.bitOp) {
        case BitInstr::And:
            o << "    andl ";
            break;
        case BitInstr::Or:
            o << "    orl ";
            break;
        case BitInstr::Xor:
            o << "    xorl ";
            break;
    }
    o << i.term2 << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(RetInstr &i) {
    o << "    movl " << i.var << "(%rbp), %eax\n";
}
