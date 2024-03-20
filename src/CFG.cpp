#include "CFG.h"
#include "IRVisitor.h"


void CFG::add_bb(BasicBlock *bb) {
    bbs.push_back(bb);
    next_bb_number++;
}

BasicBlock *CFG::get_bb(string label) {
    for (auto bb: bbs) {
        if (bb->get_label() == label) {
            return bb;
        }
    }
    return nullptr;
}

void CFG::add_to_symbol_table(string name) {
    symbol_index[name] = next_free_symbol_index;
    is_symbol_used[name] = false;
    next_free_symbol_index -= 4;
}

void CFG::use_symbol(string name) {
    is_symbol_used[name] = true;
}

vector<string> CFG::get_unused_symbols() {
    vector<string> unused_symbol;
    for(auto &entry: is_symbol_used){
        if(!entry.second){
            unused_symbol.push_back(entry.first);
        }
    }
    return unused_symbol;
}

int CFG::create_new_tempvar() {
    string name = to_string(next_free_symbol_index);
    add_to_symbol_table(name);
    return symbol_index[name];
}

int CFG::get_var_index(string var) {
    return symbol_index[var];
}

bool CFG::symbol_in_table(std::string symbol) {
    return symbol_index.find(symbol) != symbol_index.end();
}

bool CFG::bb_in_cfg(string name) {
    for (auto bb: bbs) {
        if (bb->get_label() == name) {
            return true;
        }
    }
    return false;
}

string CFG::new_BB_name() {
    string name = "Block" + next_bb_number;
    next_bb_number++;
    return name;
}

string CFG::IR_reg_to_asm(string reg) {
    return to_string(symbol_index[reg]) + "(%rbp)";
}
