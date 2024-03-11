#include "CFG.h"

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

int CFG::create_new_tempvar()
{
    std::string name = std::to_string(nextFreeSymbolIndex-4);
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
    o << ".globl main\n" ;
    o << " main: \n" ;
    o << "    pushq %rbp\n";
    o << "    movq %rsp, %rbp\n";
}

void CFG::gen_asm_epilogue(std::ostream &o)
{
    o << "    popq %rbp\n";
    o << "    ret\n";
}

std::string CFG::IR_reg_to_asm(std::string reg)
{
    return std::to_string(SymbolIndex[reg]) + "(%rbp)";
}

void CFG::gen_asm(std::ostream &o)
{
    this->gen_asm_prologue(o);
    for (auto bb : bbs)
    {
        bb->gen_asm(o);
    }
    this->gen_asm_epilogue(o);
}