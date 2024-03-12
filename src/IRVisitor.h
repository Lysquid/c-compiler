#pragma once

#include "CFG.h"
#include "BasicBlock.h"
#include "Instr.h"

using namespace std;

class IRVisitor {
public:

    explicit IRVisitor(ostream &o) : o(o) {}

    virtual void visit(CFG &cfg) = 0;

    virtual void visit(BasicBlock &bb) = 0;

    virtual void visit(ConstInstr &i) = 0;

    virtual void visit(CopyInstr &i) = 0;

    virtual void visit(AddInstr &i) = 0;

    virtual void visit(SubInstr &i) = 0;

    virtual void visit(MulInstr &i) = 0;

    virtual void visit(DivInstr &i) = 0;

    virtual void visit(NegInstr &i) = 0;

    virtual void visit(RetInstr &i) = 0;

protected:
    ostream &o;

};
