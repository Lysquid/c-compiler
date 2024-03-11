#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "CFG.h"


class ASTVisitor : public ifccBaseVisitor
{
public:
    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
    virtual antlrcpp::Any visitStatements(ifccParser::StatementsContext *ctx) override;
    virtual antlrcpp::Any visitDeclarationStatement(ifccParser::DeclarationStatementContext *ctx) override;
    virtual antlrcpp::Any visitDefinitionStatement(ifccParser::DefinitionStatementContext *ctx) override;
    virtual antlrcpp::Any visitAssignementStatement(ifccParser::AssignementStatementContext *ctx) override;
    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
    virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;
    virtual antlrcpp::Any visitSignExpr(ifccParser::SignExprContext *ctx) override;
    virtual antlrcpp::Any visitAdd_sub(ifccParser::Add_subContext *ctx) override;
    virtual antlrcpp::Any visitMult_div(ifccParser::Mult_divContext *ctx) override;
    virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

    CFG* getCFG() { return cfg; }

private:
    CFG* cfg = new CFG();

};

