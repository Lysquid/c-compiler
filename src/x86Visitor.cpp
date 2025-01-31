#include "x86Visitor.h"
#include "Instr.h"

void x86Visitor::visit(CFG &cfg) {
    // Prologue
    int size = -cfg.get_next_free_symbol_index();
    o << ".globl " << cfg.get_label() << "\n";
    o << cfg.get_label() << ":\n";
    o << "    pushq %rbp\n";
    o << "    movq %rsp, %rbp\n";
    o << "    subq $" << to_string(size%16? size-size%16+16:size) << ", %rsp\n";

    // Blocks
    for (auto bb: cfg.bbs) {
        bb->accept(*this);
    }

    // Epilogue
    o << "    movq %rbp, %rsp\n";
    o << "    pop %rbp \n";
    o << "    ret\n";
}

void x86Visitor::visit(BasicBlock &bb) {
    o << bb.get_label() << ":\n";
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

void x86Visitor::visit(IncrementafterInstr &i) {
    o << "    movl " << i.term << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n"; // on sauvegarde le contenu de la variable dans dest
    o << "    addl " << "$1, %eax\n";
    o << "    movl %eax, " << i.term << "(%rbp)\n";
}

void x86Visitor::visit(DecrementafterInstr &i) {
    o << "    movl " << i.term << "(%rbp), %eax\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n"; // on sauvegarde le contenu de la variable dans dest
    o << "    subl " << "$1, %eax\n";
    o << "    movl %eax, " << i.term << "(%rbp)\n";
}

void x86Visitor::visit(IncrementbeforeInstr &i) {
    o << "    movl " << i.term << "(%rbp), %eax\n";
    o << "    addl " << "$1, %eax\n";
    o << "    movl %eax, " << i.term << "(%rbp)\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(DecrementbeforeInstr &i) {
    o << "    movl " << i.term << "(%rbp), %eax\n";
    o << "    subl " << "$1, %eax\n";
    o << "    movl %eax, " << i.term << "(%rbp)\n";
    o << "    movl %eax, " << i.dest << "(%rbp)\n";
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

void x86Visitor::visit(NotInstr &i) {
    o << "    movl " << i.term << "(%rbp), %eax\n";
    o << "    cmpl " << "$0, %eax\n";
    o << "    sete %al\n";
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
    o << "    jmp " << i.exit_label << "\n";
}

void x86Visitor::visit(CopyParamInstr &i) {
    if(i.src < 6){
        o << "    movl %" << registers[i.src] << ", " << i.dest << "(%rbp)\n";
    }
}

void x86Visitor::visit(SetParamInstr &i) {
    if(i.dest < 6){
        o << "    movl " << i.src << "(%rbp), %" << registers[i.dest] << "\n";
    } else {
        o << "    movl " << i.src << "(%rbp), %eax\n";
        o << "    pushq %rax\n";
    }
}

void x86Visitor::visit(CallFunctionInstr &i) {
    o << "    call " << i.function_name << "\n";
    if(i.return_type) o << "    movl %eax, " << i.dest << "(%rbp)\n";
}

void x86Visitor::visit(BreakInstr &i) {
    o << "    jmp " << i.exit_label << "\n";
}

void x86Visitor::visit(ContinueInstr &i) {
    o << "    jmp " << i.exit_label << "\n";
}

void x86Visitor::visit(RetVoidInstr &i) {
    o << "    jmp " << i.exit_label << "\n";
}