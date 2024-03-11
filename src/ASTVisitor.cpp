#include "ASTVisitor.h"

antlrcpp::Any ASTVisitor::visitProg(ifccParser::ProgContext *ctx)
{
    auto *main = new BasicBlock(this->cfg, "main");
    this->cfg->add_bb(main);
    this->cfg->current_bb = main;
    for (ifccParser::StatementContext* statement: ctx->statement()) {
        this->visit(statement);
    }
    this->visit(ctx->ret());
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
    std::vector<antlr4::tree::TerminalNode *> vars = ctx->VAR();
    std::map<std::string, int> SymbolIndex = cfg->getSymbolIndex();
    for (antlr4::tree::TerminalNode *node : vars)
    {
        std::string var = node->getText();
        if (SymbolIndex.find(var) == SymbolIndex.end())
        {
            cfg->add_to_symbol_table(var);
        }
        else
        {
            std::cerr << "Error: variable " << var << " already declared" << std::endl;
            exit(1);
        }
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx)
{
    std::string var = ctx->VAR()->getText();

    if (!cfg->getSymbolIndex().count(var))
    {
        cfg->add_to_symbol_table(var);
    }
    else
    {
        std::cerr << cfg->getSymbolIndex().size() << std::endl;
        std::cout << cfg->getSymbolIndex()[var] << std::endl;
        std::cerr << "Error: variable " << var << " already declared" << std::endl;
        exit(1);
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, {std::to_string(addr), std::to_string(cfg->getSymbolIndex()[var])});
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx)
{
    std::string var = ctx->VAR()->getText();
    if (!cfg->getSymbolIndex().count(var))
    {
        std::cerr << "Error: variable " << var << " not initialized" << std::endl;
        exit(1);
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, {std::to_string(addr), std::to_string(cfg->getSymbolIndex()[var])});
    return 0;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx)
{
    std::string var = ctx->VAR()->getText();

    if (!cfg->getSymbolIndex().count(var))
    {
        std::cerr << "Error: variable " << var << " not found" << std::endl;
        exit(1);
    }
    return cfg->getSymbolIndex()[var];
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx)
{
    int value = stoi(ctx->CONST()->getText());
    int addr = cfg->create_new_tempvar();
    cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, {std::to_string(value), std::to_string(addr)});
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx)
{
    int addr = this->visit(ctx->expr());
    std::string op = ctx->ADD_SUB()->getText();
    if (op == "-")
    {
        int addr2 = cfg->create_new_tempvar();
        cfg->current_bb->add_IRInstr(IRInstr::Operation::opposite, {std::to_string(addr), std::to_string(addr2)});
        return addr2;
    }
    return addr;
}

antlrcpp::Any ASTVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    std::string op = ctx->ADD_SUB()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "+")
    {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::add, {std::to_string(addr1), std::to_string(addr2), std::to_string(addr3)});
    }
    else
    {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::sub, {std::to_string(addr1), std::to_string(addr2), std::to_string(addr3)});
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    std::string op = ctx->MUL_DIV()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "*")
    {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::mul, {std::to_string(addr1), std::to_string(addr2), std::to_string(addr3)});
    }
    else
    {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::div, {std::to_string(addr1), std::to_string(addr2), std::to_string(addr3)});
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitPar(ifccParser::ParContext *ctx)
{
    return this->visit(ctx->expr());
}

antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx)
{
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::ret, {std::to_string(addr)});
    return 0;
}
