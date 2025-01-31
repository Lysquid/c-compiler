#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Instr.h"
#include "Scope.h"

using namespace std;

class CFG;

/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then
			if  exit_true  is a  nullptr,
			the epilogue is generated
		else if exit_false is a nullptr,
		  an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
		  an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting
  the if, while, etc of the AST  to IR.

Possible optimization:
	 a cmp_* comparison instructions, if it is the last instruction of its block,
	   generates an actual assembly comparison
	   followed by a conditional jump to the exit_false branch
*/

class BasicBlock {
public:

    BasicBlock(string entry_label, Scope* scope) : exit_true(nullptr), exit_false(nullptr), label(entry_label), test_block(nullptr), next_free_symbol_index(-4), scope(scope) {};

	/**
	 * Accepte un visiteur de la classe IRVisitor
	*/
    void accept(IRVisitor &visitor);

	/**
	 * Ajoute une instruction à la fin du bloc
	*/
    void add_instr(Instr *instr);

	/**
	 * Supprime une instruction du bloc
	*/
	void delete_instr(Instr *instr);

	/**
	 * Remplace une instruction par une autre
	*/
	void replace_instr(Instr *old_instr, Instr *new_instr);

	/**
	 * Retourne le label du bloc 
	*/
    string get_label() { return label; }

	/**
	 * Définit le bloc suivant de la condition vraie
	*/
    void set_exit_true(BasicBlock *bb) { exit_true = bb; }

	/**
	 * Définit le bloc suivant de la condition fausse
	*/
    void set_exit_false(BasicBlock *bb) { exit_false = bb; }

	/**
	 * Ajoute une variable dans la table des symboles
	*/
	void add_to_symbol_table(string name, int index) const;

	/**
	 * Vérifie si une variable est déclarée
	*/
    bool is_symbol_declared(string name) const;

	/**
	 * Retourne l'index d'une variable
	*/
	int get_var_index(string var);

	/**
	 * Crée une nouvelle variable temporaire
	*/
    int create_new_tempvar(int index) const;

	/**
	 * Marque la variable comme utilisée dans la scope
	*/
    void use_symbol(string name) const;

	/**
	 * Retourne les variables non utilisées
	*/
	vector<string> get_unused_symbols();


    // No encapsulation whatsoever here. Feel free to do better.

    vector<Instr *> instrs; /** < the instructions themselves. */
    BasicBlock *exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
    BasicBlock *exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
    string label;              /**< label of the BB, also will be the label in the generated code */
	BasicBlock *test_block;  /**< pointer to the test block if we are in a loop */
    int test_var_index;      /** < when generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
	map<string, int> symbol_index; /**< local variables */
	int next_free_symbol_index; /**< next available index for a new local variable */
	Scope *scope; /** < scope of the block */

};

