#include "CFG.h"
#include "IRVisitor.h"

CFG::CFG() {
    next_free_symbol_index = -4;
    next_bb_number = 0;
}

void CFG::add_bb(BasicBlock *bb) {
    bbs.push_back(bb);
}

void CFG::add_to_symbol_table(string name) {
    symbol_index[name] = next_free_symbol_index;
    next_free_symbol_index -= 4;
}

int CFG::create_new_tempvar() {
    string name = to_string(next_free_symbol_index - 4);
    add_to_symbol_table(name);
    return symbol_index[name];
}

int CFG::get_var_index(string var) {
    return symbol_index[var];
}

bool CFG::symbol_in_table(std::string symbol) {
    return symbol_index.find(symbol) != symbol_index.end();
}

string CFG::new_BB_name() {
    string name = "Block" + next_bb_number;
    next_bb_number++;
    return name;
}

string CFG::IR_reg_to_asm(string reg) {
    return to_string(symbol_index[reg]) + "(%rbp)";
}
