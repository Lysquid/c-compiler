#include "Scope.h"

bool Scope::is_symbol_declared(string symbol) {
    if (is_declared_locally(symbol)) {
        return true;
    } else if (this->parent != nullptr) {
        return this->parent->is_symbol_declared(symbol);
    } else {
        return false;
    }
}

bool Scope::is_declared_locally(std::string symbol) {
    return this->symbol_index.find(symbol) != symbol_index.end();
}

void Scope::use_symbol(string symbol) {
    if (is_declared_locally(symbol)) {
        this->is_symbol_used[symbol] = true;
    } else if (this->parent != nullptr) {
        this->parent->use_symbol(symbol);
    }
}

int Scope::get_var_index(string symbol) {
    if (is_declared_locally(symbol)) {
        return this->symbol_index[symbol];
    } else if (this->parent != nullptr) {
        return this->parent->get_var_index(symbol);
    }
    return 0;
}

void Scope::add_to_symbol_table(string name, int index) {
    this->symbol_index[name] = index;
    this->is_symbol_used[name] = false;
}

vector<string> Scope::get_unused_symbols() {
    vector<string> unused_symbol;
    for(auto &entry: this->is_symbol_used){
        if(!entry.second){
            unused_symbol.push_back(entry.first);
        }
    }
    return unused_symbol;
}