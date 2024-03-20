#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <initializer_list>

#include "Instr.h"
#include "BasicBlock.h"

using namespace std;

class IRVisitor;

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
     The entry block is the one with the same label as the AST function name.
       (it could be the first of bbs, or it could be defined by an attribute value)
     The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG
{
public:
    CFG(string name)
    {
        this->name = name;
        next_free_symbol_index = -4;
        next_bb_number = 0;
    }

    void add_bb(BasicBlock *bb);

    BasicBlock *get_bb(string label);

    // < helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24
    string IR_reg_to_asm(string reg);

    // symbol table methods
    void add_to_symbol_table(string name);

    void use_symbol(string name);

    vector<string> get_unused_symbols();

    int create_new_tempvar();

    int get_var_index(string var);

    bool symbol_in_table(string symbol);

    bool bb_in_cfg(string name);

    // basic block management
    string new_BB_name();

    string get_label() { return name; }

    int get_next_free_symbol_index() { return next_free_symbol_index; }

    vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/

    BasicBlock *current_bb;

    int return_type; /**< 0 if void, 1 if int*/

    int number_of_params = 0; /**< number of parameters of the function */

    int is_return = 0; /**< 0 if not return, 1 if return */
protected:
    map<string, int> symbol_index;    /**< part of the symbol table  */
    int next_free_symbol_index = -4;  /**< to allocate new symbols in the symbol table */
    int next_bb_number = 0;           /**< just for naming */
    map<string, bool> is_symbol_used; /**< usage of symbols of the symbol table  */
    string name;
};
