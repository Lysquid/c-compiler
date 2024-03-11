#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "IRInstr.h"


class CodeGenVisitor : public ifccBaseVisitor
{
public:
        antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
        antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
        antlrcpp::Any visitStatements(ifccParser::StatementsContext *ctx) override;
        antlrcpp::Any visitDeclarationStatement(ifccParser::DeclarationStatementContext *ctx) override;
        antlrcpp::Any visitDefinitionStatement(ifccParser::DefinitionStatementContext *ctx) override;
        antlrcpp::Any visitAssignementStatement(ifccParser::AssignementStatementContext *ctx) override;
        antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *ctx) override;
        antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;
        antlrcpp::Any visitSignExpr(ifccParser::SignExprContext *ctx) override;
        antlrcpp::Any visitAdd_sub(ifccParser::Add_subContext *ctx) override;
        antlrcpp::Any visitMult_div(ifccParser::Mult_divContext *ctx) override;
        antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

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
