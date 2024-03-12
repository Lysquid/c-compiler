#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <initializer_list>

using namespace std;

class BasicBlock;

class CFG;

class Instr {

public:
    // x86 assembly code generation for this IR instruction
    virtual void gen_asm(std::ostream &o) = 0;

};

class ConstInstr : public Instr {
public:
    ConstInstr(int value, int dest) : value(value), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int value;
    int dest;
};

class CopyInstr : public Instr {
public:
    CopyInstr(int src, int dest) : src(src), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int src;
    int dest;
};

class AddInstr : public Instr {
public:
    AddInstr(int term1, int term2, int dest) : term1(term1), term2(term2), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
    int dest;
};

class SubInstr : public Instr {
public:
    SubInstr(int term1, int term2, int dest) : term1(term1), term2(term2), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
    int dest;
};

class MulInstr : public Instr {
public:
    MulInstr(int factor1, int factor2, int dest) : factor1(factor1), factor2(factor2), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int factor1;
    int factor2;
    int dest;
};

class DivInstr : public Instr {
public:
    DivInstr(int numerator, int denominator, int dest) : numerator(numerator), denominator(denominator), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int numerator;
    int denominator;
    int dest;
};

class NegInstr : public Instr {
public:
    NegInstr(int src, int dest) : src(src), dest(dest) {}

    void gen_asm(std::ostream &o) override;

private:
    int src;
    int dest;
};

class LessEqCmpInstr : public Instr {
public:
    LessEqCmpInstr(int term1, int term2) : term1(term1), term2(term2) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
};

class GreaterEqCmpInstr : public Instr {
public:
    GreaterEqCmpInstr(int term1, int term2) : term1(term1), term2(term2) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
};

class LessCmpInstr : public Instr {
public:
    LessCmpInstr(int term1, int term2) : term1(term1), term2(term2) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
};

class GreaterCmpInstr : public Instr {
public:
    GreaterCmpInstr(int term1, int term2) : term1(term1), term2(term2) {}

    void gen_asm(std::ostream &o) override;

private:
    int term1;
    int term2;
};

class RetInstr : public Instr {
public:
    explicit RetInstr(int var) : var(var) {}

    void gen_asm(std::ostream &o) override;

private:
    int var;
};
