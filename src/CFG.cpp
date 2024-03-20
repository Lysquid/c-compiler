#include "CFG.h"

#include <set>

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

vector<string> CFG::get_unused_symbols() {
    vector<string> unused_symbols;
    set<Scope*> scopes;
    for (auto bb: bbs) {
        scopes.insert(bb->scope);
    }
    for (auto scope: scopes) {
        vector<string> scope_unused_symbols = scope->get_unused_symbols();
        unused_symbols.insert(unused_symbols.end(), scope_unused_symbols.begin(), scope_unused_symbols.end());
    }
    return unused_symbols;
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
    string name = get_label() + "_Block" + to_string(next_bb_number);
    next_bb_number++;
    return name;
}

int CFG::get_next_free_symbol_index() {
    next_free_symbol_index -= 4;
    return this->next_free_symbol_index;
}