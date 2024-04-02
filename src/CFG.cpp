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

void CFG::printCFG() {
    cout << "CFG Instructions:" << endl;
    for (BasicBlock* bb : bbs) {
        cout << "Basic Block Label: " << bb->get_label() << endl;
        cout << "Instructions:" << endl;
        for (Instr* instr : bb->instrs) {
            if (ConstInstr* constInstr = dynamic_cast<ConstInstr*>(instr)) {
                cout << "Const Instruction: value=" << constInstr->value << ", dest=" << constInstr->dest << endl;
            } else if (CopyInstr* copyInstr = dynamic_cast<CopyInstr*>(instr)) {
                cout << "Copy Instruction: src=" << copyInstr->src << ", dest=" << copyInstr->dest << endl;
            } else if (AddInstr* addInstr = dynamic_cast<AddInstr*>(instr)) {
                cout << "Add Instruction: term1=" << addInstr->term1 << ", term2=" << addInstr->term2 << ", dest=" << addInstr->dest << endl;
            } else if (SubInstr* subInstr = dynamic_cast<SubInstr*>(instr)) {
                cout << "Sub Instruction: term1=" << subInstr->term1 << ", term2=" << subInstr->term2 << ", dest=" << subInstr->dest << endl;
            } else if (MulInstr* mulInstr = dynamic_cast<MulInstr*>(instr)) {
                cout << "Mul Instruction: factor1=" << mulInstr->factor1 << ", factor2=" << mulInstr->factor2 << ", dest=" << mulInstr->dest << endl;
            } else if (DivInstr* divInstr = dynamic_cast<DivInstr*>(instr)) {
                cout << "Div Instruction: numerator=" << divInstr->numerator << ", denominator=" << divInstr->denominator << ", dest=" << divInstr->dest << endl;
            } else if (ModInstr* modInstr = dynamic_cast<ModInstr*>(instr)) {
                cout << "Mod Instruction: numerator=" << modInstr->numerator << ", denominator=" << modInstr->denominator << ", dest=" << modInstr->dest << endl;
            } else if (NegInstr* negInstr = dynamic_cast<NegInstr*>(instr)) {
                cout << "Neg Instruction: src=" << negInstr->src << ", dest=" << negInstr->dest << endl;
            } else if (CmpInstr* cmpInstr = dynamic_cast<CmpInstr*>(instr)) {
                cout << "Cmp Instruction: term1=" << cmpInstr->term1 << ", term2=" << cmpInstr->term2 << ", dest=" << cmpInstr->dest << ", cmp=" << cmpInstr->cmp << endl;
            } else if (BitInstr* bitInstr = dynamic_cast<BitInstr*>(instr)) {
                cout << "Bit Instruction: term1=" << bitInstr->term1 << ", term2=" << bitInstr->term2 << ", dest=" << bitInstr->dest << ", bitOp=" << bitInstr->bitOp << endl;
            } else if (RetInstr* retInstr = dynamic_cast<RetInstr*>(instr)) {
                cout << "Return Instruction: var=" << retInstr->var << endl;
            } else if (CopyparamInstr* copyparamInstr = dynamic_cast<CopyparamInstr*>(instr)) {
                cout << "Copyparam Instruction: src=" << copyparamInstr->src << ", dest=" << copyparamInstr->dest << endl;
            } else if (SetparamInstr* setparamInstr = dynamic_cast<SetparamInstr*>(instr)) {
                cout << "Setparam Instruction: src=" << setparamInstr->src << ", dest=" << setparamInstr->dest << endl;
            } else if (CallFunctionInstr* callfunctionInstr = dynamic_cast<CallFunctionInstr*>(instr)) {
                cout << "Callfunction Instruction: function_name=" << callfunctionInstr->function_name << ", dest=" << callfunctionInstr->dest << ", return_type=" << callfunctionInstr->return_type << endl;
            }
        }
        cout << endl;
    }
}
