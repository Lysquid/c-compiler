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
class CFG {
public:
    CFG();

    void add_bb(BasicBlock *bb);

    // < helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24
    string IR_reg_to_asm(string reg);

    // symbol table methods
    void add_to_symbol_table(string name);

    int create_new_tempvar();

    int get_var_index(string var);

    bool symbol_in_table(string symbol);

    // basic block management
    string new_BB_name();

    BasicBlock *current_bb;

    vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/

protected:
    map<string, int> symbol_index; /**< part of the symbol table  */
    int next_free_symbol_index;      /**< to allocate new symbols in the symbol table */
    int next_bb_number;              /**< just for naming */

};
