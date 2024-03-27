#include "BasicBlock.h"
#include "IRVisitor.h"


void BasicBlock::add_instr(Instr* instr) {
    this->instrs.push_back(instr);
}

void BasicBlock::accept(IRVisitor &visitor) {
    visitor.visit(*this);
}

void BasicBlock::add_to_symbol_table(string name, int index) const {
    this->scope->add_to_symbol_table(name, index);
}

bool BasicBlock::is_symbol_declared(string name) const {
    return scope->is_symbol_declared(name);
}

int BasicBlock::create_new_tempvar(int index) const {
    string name = "!tmp" + to_string(index);
    this->add_to_symbol_table(name, index);
    this->use_symbol(name);
    return index;
}


void BasicBlock::use_symbol(string name) const {
    this->scope->use_symbol(name);
}

vector<string> BasicBlock::get_unused_symbols() {
    return this->scope->get_unused_symbols();
}

int BasicBlock::get_var_index(string var) {
    this->use_symbol(var);
    return this->scope->get_var_index(var);
}
