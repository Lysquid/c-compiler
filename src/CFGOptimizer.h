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
    void optimization();
    bool checkInstr(Instr* instr, BasicBlock* actualbb);
    void updateCFG(int addr1, int addr2, int dest, BasicBlock* actualbb, Instr* instr);
    bool updateCFGNeutral(int addr1, int addr2, int dest, BasicBlock* actualbb, Instr* instr, int neutralElement);
    void printInstruction(Instr* instr);
    void divideOrModuloByZero();
private:
    CFG* cfg; 
    std::unordered_map<int, int> const_index;
    std::unordered_map<int, Instr*> instr_index;
    std::set<int> divide_or_modulo;
};
