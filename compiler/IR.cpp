#include "IR.h"

IRInstr::IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params)
{
    this->bb = bb_;
    this->op = op;
    this->t = t;
    this->params = params;
}

void IRInstr::gen_asm(ostream &o)
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
    default:
        o << "Unknown operation\n";
        break;
    }
}

BasicBlock::BasicBlock(CFG *cfg, string entry_label)
{
    this->cfg = cfg;
    this->exit_true = nullptr;
    this->exit_false = nullptr;
    this->label = entry_label;
    this->test_var_name = "$0";
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params)
{
    this->instrs.push_back(new IRInstr(this, op, t, params));
}

void BasicBlock::gen_asm(ostream &o)
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

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, string d, string x, string y)
{
    vector<string> params;
    params.push_back(d);
    params.push_back(x);
    params.push_back(y);
    this->add_IRInstr(op, t, params);
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

void CFG::add_to_symbol_table(string name, Type t)
{
    SymbolType[name] = t;
    SymbolIndex[name] = nextFreeSymbolIndex;
    nextFreeSymbolIndex -= 4;
}

string CFG::create_new_tempvar(Type t)
{
    string name = "t" + to_string(nextFreeSymbolIndex);
    add_to_symbol_table(name, t);
    nextFreeSymbolIndex -= 4;
    return name;
}

int CFG::get_var_index(string name)
{
    return SymbolIndex[name];
}

Type CFG::get_var_type(string name)
{
    return SymbolType[name];
}

string CFG::new_BB_name()
{
    string name = "Block" + nextBBnumber;
    nextBBnumber++;
    return name;
}

void CFG::gen_asm_prologue(ostream &o)
{
    std::cout<< ".globl main\n" ;
    std::cout<< " main: \n" ;
    std::cout << "    pushq %rbp\n";
    std::cout << "    movq %rsp, %rbp\n";
}

void CFG::gen_asm_epilogue(ostream &o)
{
    std::cout << "    popq %rbp\n";
    std::cout << "    ret\n";
}

string CFG::IR_reg_to_asm(string reg)
{
    return to_string(SymbolIndex[reg]) + "(%rbp)";
}