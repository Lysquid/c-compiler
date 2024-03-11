#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <initializer_list>

#include "IRInstr.h"
#include "BasicBlock.h"


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

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(std::ostream &o);

    std::string IR_reg_to_asm(
            std::string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(std::ostream &o);

    void gen_asm_epilogue(std::ostream &o);

    // symbol table methods
    void add_to_symbol_table(std::string name);

    int create_new_tempvar();

    int get_var_index(std::string name);

    // basic block management
    std::string new_BB_name();

    BasicBlock *current_bb;

    std::map<std::string, int> getSymbolIndex() { return SymbolIndex; }

protected:
    std::map<std::string, int> SymbolIndex; /**< part of the symbol table  */
    int nextFreeSymbolIndex;      /**< to allocate new symbols in the symbol table */
    int nextBBnumber;              /**< just for naming */

    std::vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/
};
