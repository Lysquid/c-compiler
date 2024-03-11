#include "ASTVisitor.h"

using namespace std;

antlrcpp::Any ASTVisitor::visitProg(ifccParser::ProgContext *ctx) {
    auto *main = new BasicBlock(this->cfg, "main");
    this->cfg->add_bb(main);
    this->cfg->current_bb = main;
    for (ifccParser::StatementContext *statement: ctx->statement()) {
        this->visit(statement);
    }
    this->visit(ctx->ret());
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    vector<antlr4::tree::TerminalNode *> vars = ctx->VAR();
    map<string, int> SymbolIndex = cfg->getSymbolIndex();
    for (antlr4::tree::TerminalNode *node: vars) {
        string var = node->getText();
        if (SymbolIndex.find(var) == SymbolIndex.end()) {
            cfg->add_to_symbol_table(var);
        } else {
            cerr << "Error: variable " << var << " already declared" << endl;
            exit(1);
        }
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx) {
    string var = ctx->VAR()->getText();

    if (!cfg->getSymbolIndex().count(var)) {
        cfg->add_to_symbol_table(var);
    } else {
        cerr << cfg->getSymbolIndex().size() << endl;
        cout << cfg->getSymbolIndex()[var] << endl;
        cerr << "Error: variable " << var << " already declared" << endl;
        exit(1);
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::copy,
                                 {to_string(addr), to_string(cfg->getSymbolIndex()[var])});
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    string var = ctx->VAR()->getText();
    if (!cfg->getSymbolIndex().count(var)) {
        cerr << "Error: variable " << var << " not initialized" << endl;
        exit(1);
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::copy,
                                 {to_string(addr), to_string(cfg->getSymbolIndex()[var])});
    return 0;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx) {
    string var = ctx->VAR()->getText();

    if (!cfg->getSymbolIndex().count(var)) {
        cerr << "Error: variable " << var << " not found" << endl;
        exit(1);
    }
    return cfg->getSymbolIndex()[var];
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx) {
    int value = stoi(ctx->CONST()->getText());
    int addr = cfg->create_new_tempvar();
    cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, {to_string(value), to_string(addr)});
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx) {
    int addr = this->visit(ctx->expr());
    string op = ctx->ADD_SUB()->getText();
    if (op == "-") {
        int addr2 = cfg->create_new_tempvar();
        cfg->current_bb->add_IRInstr(IRInstr::Operation::opposite, {to_string(addr), to_string(addr2)});
        return addr2;
    }
    return addr;
}

antlrcpp::Any ASTVisitor::visitAddSub(ifccParser::AddSubContext *ctx) {
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->ADD_SUB()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "+") {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::add,
                                     {to_string(addr1), to_string(addr2), to_string(addr3)});
    } else {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::sub,
                                     {to_string(addr1), to_string(addr2), to_string(addr3)});
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->MUL_DIV()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "*") {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::mul,
                                     {to_string(addr1), to_string(addr2), to_string(addr3)});
    } else {
        cfg->current_bb->add_IRInstr(IRInstr::Operation::div,
                                     {to_string(addr1), to_string(addr2), to_string(addr3)});
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitPar(ifccParser::ParContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx) {
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_IRInstr(IRInstr::Operation::ret, {to_string(addr)});
    return 0;
}
