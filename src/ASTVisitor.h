#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "CFG.h"

using namespace std;

class ASTVisitor : public ifccBaseVisitor {
public:
    antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

    antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override;

    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

    antlrcpp::Any visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx) override;

    antlrcpp::Any visitExpression(ifccParser::ExpressionContext *ctx) override;

    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;

    antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;

    antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

    antlrcpp::Any visitSign(ifccParser::SignContext *ctx) override;

    antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;

    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;

    antlrcpp::Any visitComparison(ifccParser::ComparisonContext *ctx) override;

    antlrcpp::Any visitBitAnd(ifccParser::BitAndContext *ctx) override;

    antlrcpp::Any visitBitOr(ifccParser::BitOrContext *ctx) override;

    antlrcpp::Any visitBitXor(ifccParser::BitXorContext *ctx) override;

    antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

    int getNumberOfErrors() const { return errors; }

    CFG *getCFG() { return cfg; }

private:
    int errors = 0;
    CFG *cfg = new CFG();
    BasicBlock *current_bb;

};
