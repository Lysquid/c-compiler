#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "IR.h"


class CodeGenVisitor : public ifccBaseVisitor
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

        std::map<std::string, int> getSymbolTable() { return symbolTable; }
        void setSymbolTable(std::map<std::string, int> symbolTable)
        {
                this->symbolTable = symbolTable;
                this->index = -4 * symbolTable.size();
        }

private:
        std::map<std::string, int> symbolTable;
        int index = 0;
};

class SymbolVisitor : public ifccBaseVisitor
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

        std::map<std::string, int> getSymbolTable() { return symbolTable; }

private:
        int index = 0;
        std::map<std::string, int> symbolTable;
        std::map<std::string, int> numberTable;
};

class IRVisitor : public ifccBaseVisitor
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

private:
        CFG* CFG = new CFG();

};