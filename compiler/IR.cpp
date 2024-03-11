#include "IR.h"

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
        o << "    movl " << params[0] << "(%rbp), %eax\n";
        o << "    movl %eax, " << params[1] << "(%rbp)\n";
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

BasicBlock::BasicBlock(CFG *cfg, std::string entry_label)
{
    this->cfg = cfg;
    this->exit_true = nullptr;
    this->exit_false = nullptr;
    this->label = entry_label;
    this->test_var_name = "$0";
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, std::vector<std::string> params)
{
    this->instrs.push_back(new IRInstr(this, op, params));
}

void BasicBlock::gen_asm(std::ostream &o)
{
    for (auto instr : instrs)
    {
        instr->gen_asm(o);
    }

    if(!exit_true)
    {
        cfg->gen_asm_epilogue(o);
    } else if (!exit_false)
    {
        o << "    jmp " << exit_true->get_label() << "\n";
    } else
    {
        o << "    cmpl $0, " << test_var_name << "(%rbp)\n";
        o << "    je " << exit_false->get_label() << "\n";
        o << "    jmp " << exit_true->get_label() << "\n";
    }
}


CFG::CFG()
{
    nextFreeSymbolIndex = -4;
    nextBBnumber = 0;
}

void CFG::add_bb(BasicBlock *bb)
{
    bbs.push_back(bb);
}

void CFG::add_to_symbol_table(std::string name)
{
    SymbolIndex[name] = nextFreeSymbolIndex;
    nextFreeSymbolIndex -= 4;
}

int CFG::create_new_tempvar(int value)
{
    std::string name = std::to_string(value);
    add_to_symbol_table(name);
    return SymbolIndex[name];
}

int CFG::get_var_index(std::string name)
{
    return SymbolIndex[name];
}

std::string CFG::new_BB_name()
{
    std::string name = "Block" + nextBBnumber;
    nextBBnumber++;
    return name;
}

void CFG::gen_asm_prologue(std::ostream &o)
{
    std::cout<< ".globl main\n" ;
    std::cout<< " main: \n" ;
    std::cout << "    pushq %rbp\n";
    std::cout << "    movq %rsp, %rbp\n";
}

void CFG::gen_asm_epilogue(std::ostream &o)
{
    std::cout << "    popq %rbp\n";
    std::cout << "    ret\n";
}

std::string CFG::IR_reg_to_asm(std::string reg)
{
    return std::to_string(SymbolIndex[reg]) + "(%rbp)";
}