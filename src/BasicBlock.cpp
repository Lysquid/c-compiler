#include "BasicBlock.h"

BasicBlock::BasicBlock(CFG *cfg, std::string entry_label) {
    this->cfg = cfg;
    this->exit_true = nullptr;
    this->exit_false = nullptr;
    this->label = entry_label;
    this->test_var_name = "$0";
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, std::vector<std::string> params) {
    this->instrs.push_back(new IRInstr(this, op, params));
}

void BasicBlock::gen_asm(std::ostream &o) {
    for (auto instr: instrs) {
        instr->gen_asm(o);
    }

    if (!exit_true) {
        return;
    } else if (!exit_false) {
        o << "    jmp " << exit_true->get_label() << "\n";
    } else {
        o << "    cmpl $0, " << test_var_name << "(%rbp)\n";
        o << "    je " << exit_false->get_label() << "\n";
        o << "    jmp " << exit_true->get_label() << "\n";
    }
}
