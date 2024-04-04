#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

class BasicBlock;

class CFG;

class IRVisitor;

class Instr {
public:
    virtual void accept(IRVisitor &visitor) = 0;

};

class ConstInstr : public Instr {
public:
    ConstInstr(int value, int dest) : value(value), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int value;
    int dest;
};

class CopyInstr : public Instr {
public:
    CopyInstr(int src, int dest) : src(src), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int src;
    int dest;
};

class AddInstr : public Instr {
public:
    AddInstr(int term1, int term2, int dest) : term1(term1), term2(term2), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term1;
    int term2;
    int dest;
};

class SubInstr : public Instr {
public:
    SubInstr(int term1, int term2, int dest) : term1(term1), term2(term2), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term1;
    int term2;
    int dest;
};

class MulInstr : public Instr {
public:
    MulInstr(int factor1, int factor2, int dest) : factor1(factor1), factor2(factor2), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int factor1;
    int factor2;
    int dest;
};

class DivInstr : public Instr {
public:
    DivInstr(int numerator, int denominator, int dest) : numerator(numerator), denominator(denominator), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int numerator;
    int denominator;
    int dest;
};

class ModInstr : public Instr {
public:
    ModInstr(int numerator, int denominator, int dest) : numerator(numerator), denominator(denominator), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int numerator;
    int denominator;
    int dest;
};

class IncrementafterInstr : public Instr {
public:
    IncrementafterInstr(int term, int dest) : term(term), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term;
    int dest;
};

class IncrementbeforeInstr : public Instr {
public:
    IncrementbeforeInstr(int term, int dest) : term(term), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term;
    int dest;
};

class DecrementafterInstr : public Instr {
public:
    DecrementafterInstr(int term, int dest) : term(term), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term;
    int dest;
};

class DecrementbeforeInstr : public Instr {
public:
    DecrementbeforeInstr(int term, int dest) : term(term), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term;
    int dest;
};

class NegInstr : public Instr {
public:
    NegInstr(int src, int dest) : src(src), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int src;
    int dest;
};

class CmpInstr : public Instr {
public:

    enum cmp_type {
        e,
        g,
        ge,
        l,
        le,
        ne
    };

    CmpInstr(int term1, int term2, int dest, cmp_type cmp) : term1(term1), term2(term2), dest(dest), cmp(cmp) {}

    void accept(IRVisitor &visitor) override;

    int term1;
    int term2;
    int dest;
    cmp_type cmp;
};

class NotInstr : public Instr {
public:

    NotInstr(int term, int dest) : term(term), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int term;
    int dest;
};

class BitInstr : public Instr {
public:

    enum bit_type {
        And,
        Or,
        Xor,
    };

    BitInstr(int term1, int term2, int dest, bit_type bitOp) : term1(term1), term2(term2), dest(dest), bitOp(bitOp) {}

    void accept(IRVisitor &visitor) override;

    int term1;
    int term2;
    int dest;
    bit_type bitOp;
};

class RetInstr : public Instr {
public:
    explicit RetInstr(int var, string exit_label) : var(var), exit_label(exit_label) {}

    void accept(IRVisitor &visitor) override;

    int var;
    string exit_label;
};


class CopyParamInstr : public Instr {
public:

    CopyParamInstr(int src, int dest) : src(src), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int src;
    int dest;
};

class SetParamInstr : public Instr {
public:

    SetParamInstr(int src, int dest) : src(src), dest(dest) {}

    void accept(IRVisitor &visitor) override;

    int src;
    int dest;
};

class CallFunctionInstr : public Instr {
public:
    CallFunctionInstr(string function_name, int dest, int return_type) : function_name(function_name), dest(dest), return_type(return_type) {}

    void accept(IRVisitor &visitor) override;

    string function_name;
    int dest;
    int return_type;
};

class BreakInstr : public Instr {
public:
    BreakInstr(string exit_label) : exit_label(exit_label) {}

    void accept(IRVisitor &visitor) override;

    string exit_label;
};

class ContinueInstr : public Instr {
public:
    ContinueInstr(string exit_label) : exit_label(exit_label) {}

    void accept(IRVisitor &visitor) override;

    string exit_label;
};

class RetVoidInstr : public Instr {
public:
    RetVoidInstr(string exit_label) : exit_label(exit_label) {}

    void accept(IRVisitor &visitor) override;

    string exit_label;
};