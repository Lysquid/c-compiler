#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <initializer_list>

#include "Instr.h"
#include "IRVisitor.h"

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

    BasicBlock(string entry_label);

    void accept(IRVisitor &visitor);

    void add_instr(Instr *instr);

    string get_label() { return label; }

    void set_exit_true(BasicBlock *bb) { exit_true = bb; }

    void set_exit_false(BasicBlock *bb) { exit_false = bb; }


    // No encapsulation whatsoever here. Feel free to do better.

    vector<Instr *> instrs; /** < the instructions themselves. */
    BasicBlock *exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
    BasicBlock *exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
    string label;              /**< label of the BB, also will be the label in the generated code */
    string test_var_name;      /** < when generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
};

