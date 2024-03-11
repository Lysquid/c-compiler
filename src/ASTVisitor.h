#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "CFG.h"


class ASTVisitor : public ifccBaseVisitor {
public:
    antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

    antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override;

    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

    antlrcpp::Any visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx) override;

    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;

    antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;

    antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

    antlrcpp::Any visitSign(ifccParser::SignContext *ctx) override;

    antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;

    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;

    antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

    CFG *getCFG() { return cfg; }

private:
    CFG *cfg = new CFG();

};

