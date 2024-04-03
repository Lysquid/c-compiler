#pragma once

#include "CFG.h"
#include "ASTVisitor.h"
#include <vector>
#include <string>

using namespace std;

class CFGOptimizer
{
public:
    explicit CFGOptimizer(CFG& cfg, std::unordered_map<int, int> const_index, std::unordered_map<int, Instr*> instr_index) : cfg(&cfg), const_index(const_index), instr_index(instr_index) {}

    /**
     * Optimize le CFG
    */
    void optimization();

    /**
     * Vérifie si une instruction est optimisable
    */
    bool checkInstr(Instr* instr, BasicBlock* actualbb);

    /**
     * Optimise une instruction
    */
    void updateCFG(int addr1, int addr2, int dest, BasicBlock* actualbb, Instr* instr);

    /**
     * Optimise une instruction avec une valeur neutre
    */
    bool updateCFGNeutral(int addr1, int addr2, int dest, BasicBlock* actualbb, Instr* instr, int neutralElement);
    void printInstruction(Instr* instr);

    /**
     * Vérifie si une division ou un modulo par zéro est effectué
    */
    void divideOrModuloByZero();
private:
    CFG* cfg; 
    std::unordered_map<int, int> const_index;
    std::unordered_map<int, Instr*> instr_index;
    std::set<int> divide_or_modulo;
};
