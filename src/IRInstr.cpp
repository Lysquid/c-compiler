#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock *bb_, Operation op, std::vector<std::string> params)
{
    this->bb = bb_;
    this->op = op;
    this->params = params;
}

void IRInstr::gen_asm(std::ostream &o)
{
    switch (this->op)
    {
    case ldconst:
        o << "    movl $" << params[0] << ", " << params[1] << "(%rbp)\n";
        break;
    case copy:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    movl %eax, " << params[1] << "(%rbp)\n";
        break;
    case add:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    addl " << params[1] << "(%rbp), %eax\n";
        o << "    movl %eax, " << params[2] << "(%rbp)\n";
        break;
    case sub:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    subl " << params[1] << "(%rbp), %eax\n";
        o << "    movl %eax, " << params[2] << "(%rbp)\n";
        break;
    case mul:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    imull " << params[1] << "(%rbp), %eax\n";
        o << "    movl %eax, " << params[2] << "(%rbp)\n";
        break;
    case div:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    cltd\n";
        o << "    idivl " << params[1] << "(%rbp)\n";
        o << "    movl %eax, " << params[2] << "(%rbp)\n";
        break;
    case opposite:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    negl %eax\n";
        o << "    movl %eax, " << params[1] << "(%rbp)\n";
        break;
    case ret:
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        break;
    default:
        o << "Unknown operation\n";
        break;
    }
}

