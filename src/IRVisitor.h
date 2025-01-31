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

    virtual void visit(ModInstr &i) = 0;

    virtual void visit(IncrementafterInstr &i) = 0;

    virtual void visit(DecrementafterInstr &i) = 0;

    virtual void visit(IncrementbeforeInstr &i) = 0;

    virtual void visit(DecrementbeforeInstr &i) = 0;

    virtual void visit(NegInstr &i) = 0;

    virtual void visit(CmpInstr &i) = 0;

    virtual void visit(NotInstr &i) = 0;

    virtual void visit(BitInstr &i) = 0;

    virtual void visit(RetInstr &i) = 0;

    virtual void visit(CopyParamInstr &i) = 0;

    virtual void visit(SetParamInstr &i) = 0;

    virtual void visit(CallFunctionInstr &i) = 0;

    virtual void visit(BreakInstr &i) = 0;

    virtual void visit(ContinueInstr &i) = 0;

    virtual void visit(RetVoidInstr &i) = 0;

protected:
    ostream &o;

};
