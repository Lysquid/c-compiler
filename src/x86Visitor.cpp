#include "x86Visitor.h"

void x86Visitor::visit(CFG &cfg) {
    gen_prologue(cfg);
    int size = cfg.bbs.size();
    for (int i = 0; i < size; i++) {
        BasicBlock* bb = cfg.bbs[i];
        bb->accept(*this);
        if(i != size-1) gen_prologue_BB(*cfg.bbs[i+1]);
    }
    gen_epilogue();
}

void x86Visitor::gen_prologue(CFG &cfg) {
    int size = -cfg.get_next_free_symbol_index();
    o << ".globl " << cfg.get_label() << "\n";
    o << cfg.get_label() << ":\n";
    o << "    pushq %rbp\n";
    o << "    movq %rsp, %rbp\n";
    o << "    subq $" << to_string(size%16? size-size%16+16:size) << ", %rsp\n";
    
}

void x86Visitor::gen_prologue_BB(BasicBlock &bb) {
    o << bb.get_label() << ":\n";
}

void x86Visitor::gen_epilogue() {
    o << "    movq %rbp, %rsp\n";
    o << "    pop %rbp \n";
    o << "    ret\n";
}

void x86Visitor::visit(BasicBlock &bb) {
    for (auto instr: bb.instrs) {
        instr->accept(*this);
    }
    if (bb.exit_true == nullptr) {
        return;
    } else if (bb.exit_false == nullptr) {
        o << "    jmp " << bb.exit_true->get_label() << "\n";
    } else {
        o << "    cmpl $0, " << bb.test_var_index << "(%rbp)\n";
        o << "    jne " << bb.exit_true->get_label() << "\n";
        o << "    jmp " << bb.exit_false->get_label() << "\n";
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
    //function calculated the modulo
    o << "    movl " << i.numerator << "(%rbp), %eax\n";
    o << "    cdq\n";
    o << "    movl " << i.denominator << "(%rbp), %ecx\n";
    o << "    idivl   %ecx\n";
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
        case CmpInstr::ne:
            o << "ne";
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

void x86Visitor::visit(PutcharInstr &i) {
    o << "    movl " << i.var << "(%rbp), %edi\n";
    o << "    call putchar@PLT\n";
}

void x86Visitor::visit(GetcharInstr &i) {
    o << "    call getchar@PLT\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}


void x86Visitor::visit(CopyparamInstr &i) {
    o << "    movl %" << i.memory_type[i.src] << ", " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(SetparamInstr &i) {
    o << "    movl " << i.src << "(%rbp), %" << i.memory_type[i.dest] << "\n";
}

void x86Visitor::visit(CallfunctionInstr &i) {
    o << "    call " << i.function_name << "\n";
    if(i.return_type) o << "    movl %eax, " << i.dest << "(%rbp)\n";
}