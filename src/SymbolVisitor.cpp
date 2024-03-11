#include "SymbolVisitor.h"

antlrcpp::Any SymbolVisitor::visitProg(ifccParser::ProgContext *ctx)
{
    this->visit(ctx->statements());
    this->visit(ctx->return_stmt());
    return 0;
}

antlrcpp::Any SymbolVisitor::visitStatements(ifccParser::StatementsContext *ctx)
{
    for (ifccParser::StatementContext *statement : ctx->statement())
        this->visit(statement);

    return 0;
}

antlrcpp::Any SymbolVisitor::visitDeclarationStatement(ifccParser::DeclarationStatementContext *ctx)
{
    std::vector<antlr4::tree::TerminalNode *> vars = ctx->VAR();
    for (antlr4::tree::TerminalNode *node : vars)
    {
        std::string var = node->getText();
        if (symbolTable.find(var) == symbolTable.end())
        {
            index -= 4;
            symbolTable[var] = index;
            numberTable[var] = -1;
        }
        else
        {
            std::cerr << "Error: variable " << var << " already declared" << std::endl;
            exit(1);
        }
    }
    return 0;
}

antlrcpp::Any SymbolVisitor::visitDefinitionStatement(ifccParser::DefinitionStatementContext *ctx)
{
    std::string var = ctx->VAR()->getText();
    if (symbolTable.find(var) == symbolTable.end())
    {
        index -= 4;
        symbolTable[var] = index;
        numberTable[var] = 0;
    }
    else
    {
        std::cerr << "Error: variable " << var << " already declared" << std::endl;
        exit(1);
    }
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolVisitor::visitAssignementStatement(ifccParser::AssignementStatementContext *ctx)
{
    std::string var = ctx->VAR()->getText();
    if (symbolTable.find(var) == symbolTable.end())
    {
        std::cerr << "Error: variable " << var << " not initialized" << std::endl;
        exit(1);
    }
    numberTable[var] = 0;
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolVisitor::visitVarExpr(ifccParser::VarExprContext *ctx)
{
    std::string var = ctx->VAR()->getText();
    if (symbolTable.find(var) == symbolTable.end())
    {
        std::cerr << "Error: variable " << var << " not found" << std::endl;
        exit(1);
    }
    else if (numberTable[var] == -1)
    {
        std::cerr << "Error: variable " << var << " not assigned" << std::endl;
        exit(1);
    }
    numberTable[var] += 1;
    return 0;
}

antlrcpp::Any SymbolVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx)
{
    return 0;
}

antlrcpp::Any SymbolVisitor::visitSignExpr(ifccParser::SignExprContext *ctx)
{
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolVisitor::visitAdd_sub(ifccParser::Add_subContext *ctx)
{
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return 0;
}

antlrcpp::Any SymbolVisitor::visitMult_div(ifccParser::Mult_divContext *ctx)
{
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return 0;
}

antlrcpp::Any SymbolVisitor::visitPar(ifccParser::ParContext *ctx)
{
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any SymbolVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
    this->visit(ctx->expr());
    for (auto &x : numberTable)
    {
        if (x.second == 0 || x.second == -1)
        {
            std::cerr << "Error: variable " << x.first << " never used" << std::endl;
            exit(1);
        }
    }
    return 0;
}
