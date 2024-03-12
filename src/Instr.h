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
    };

    CmpInstr(int term1, int term2, int dest, cmp_type cmp) : term1(term1), term2(term2), dest(dest), cmp(cmp) {}

    void accept(IRVisitor &visitor) override;

    int term1;
    int term2;
    int dest;
    cmp_type cmp;
};

class RetInstr : public Instr {
public:
    explicit RetInstr(int var) : var(var) {}

    void accept(IRVisitor &visitor) override;

    int var;
};
