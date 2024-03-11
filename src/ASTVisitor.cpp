#include "ASTVisitor.h"

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
    vector < antlr4::tree::TerminalNode * > vars = ctx->VAR();
    map<string, int> SymbolIndex = cfg->getSymbolIndex();
    for (antlr4::tree::TerminalNode *node: vars) {
        string var = node->getText();
        if (SymbolIndex.find(var) == SymbolIndex.end()) {
            cfg->add_to_symbol_table(var);
        } else {
            cerr << "Error: variable " << var << " already declared" << endl;
            errors++;
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
        errors++;
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_instr(new CopyInstr(addr, cfg->getSymbolIndex()[var]));
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    string var = ctx->VAR()->getText();
    if (!cfg->getSymbolIndex().count(var)) {
        cerr << "Error: variable " << var << " not initialized" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_instr(new CopyInstr(addr, cfg->getSymbolIndex()[var]));
    return 0;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx) {
    string var = ctx->VAR()->getText();

    if (!cfg->getSymbolIndex().count(var)) {
        cerr << "Error: variable " << var << " not found" << endl;
        errors++;
    }
    return cfg->getSymbolIndex()[var];
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx) {
    int value = stoi(ctx->CONST()->getText());
    int addr = cfg->create_new_tempvar();
    cfg->current_bb->add_instr(new ConstInstr(value, addr));
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx) {
    int addr = this->visit(ctx->expr());
    string op = ctx->ADD_SUB()->getText();
    if (op == "-") {
        int addr2 = cfg->create_new_tempvar();
        cfg->current_bb->add_instr(new NegInstr(addr, addr2));
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
        cfg->current_bb->add_instr(new AddInstr(addr1, addr2, addr3));
    } else {
        cfg->current_bb->add_instr(new SubInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->MUL_DIV()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "*") {
        cfg->current_bb->add_instr(new MulInstr(addr1, addr2, addr3));
    } else {
        cfg->current_bb->add_instr(new DivInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitPar(ifccParser::ParContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx) {
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_instr(new RetInstr(addr));
    return 0;
}
