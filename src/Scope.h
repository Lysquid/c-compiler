#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class Scope {
public:

    explicit Scope(Scope* parent): parent(parent) {}

    bool is_symbol_declared(string name);

    void add_to_symbol_table(string name, int index);

    int get_var_index(string name);

    void use_symbol(string name);

    vector<string> get_unused_symbols();

    map<string, int> symbol_index;    /**< part of the symbol table  */
    map<string, bool> is_symbol_used; /**< usage of symbols of the symbol table  */
    Scope* parent;
};