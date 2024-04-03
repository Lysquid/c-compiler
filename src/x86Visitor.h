#pragma once

#include "IRVisitor.h"

class x86Visitor : public IRVisitor {
public:

    explicit x86Visitor(ostream &o) : IRVisitor(o) {}

    void visit(CFG &cfg) override;

    void visit(BasicBlock &bb) override;

    void visit(ConstInstr &i) override;

    void visit(CopyInstr &i) override;

    void visit(AddInstr &i) override;

    void visit(SubInstr &i) override;

    void visit(MulInstr &i) override;

    void visit(DivInstr &i) override;

    void visit(ModInstr &i) override;

    void visit(IncrementafterInstr &i) override;

    void visit(DecrementafterInstr &i) override;

    void visit(IncrementbeforeInstr &i) override;

    void visit(DecrementbeforeInstr &i) override;

    void visit(NegInstr &i) override;

    void visit(CmpInstr &i) override;

    void visit(NotInstr &i) override;

    void visit(LogicInstr &i) override;

    void visit(BitInstr &i) override;

    void visit(RetInstr &i) override;

    void visit(CopyParamInstr &i) override;

    void visit(SetParamInstr &i) override;

    void visit(CallFunctionInstr &i) override;

    void visit(BreakInstr &i) override;

    void visit(ContinueInstr &i) override;

    void visit(RetVoidInstr &i) override;

private:

    const vector<string> registers = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};

};
