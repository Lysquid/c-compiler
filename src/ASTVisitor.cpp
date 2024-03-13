#include "ASTVisitor.h"

antlrcpp::Any ASTVisitor::visitProg(ifccParser::ProgContext *ctx) {
    auto *main = new BasicBlock("main");
    cfg->add_bb(main);
    current_bb = main;
    for (ifccParser::StatementContext *statement: ctx->statement()) {
        this->visit(statement);
    }
    this->visit(ctx->ret());
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    for (antlr4::tree::TerminalNode *node: ctx->VAR()) {
        string var = node->getText();
        if (!cfg->symbol_in_table(var)) {
            cfg->add_to_symbol_table(var);
        } else {
            cerr << "ERROR: variable " << var << " already declared" << endl;
            errors++;
        }
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx) {
    string var = ctx->VAR()->getText();

    if (!cfg->symbol_in_table(var)) {
        cfg->add_to_symbol_table(var);
    } else {
        cerr << "ERROR: variable " << var << " already declared" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new CopyInstr(addr, cfg->get_var_index(var)));
    return 0;
}

antlrcpp::Any ASTVisitor::visitExpression(ifccParser::ExpressionContext *ctx) {
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    string var = ctx->VAR()->getText();
    if (!cfg->symbol_in_table(var)) {
        cerr << "ERROR: variable " << var << " not initialized" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new CopyInstr(addr, cfg->get_var_index(var)));
    return addr;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx) {
    string var = ctx->VAR()->getText();

    if (!cfg->symbol_in_table(var)) {
        cerr << "ERROR: variable " << var << " not found" << endl;
        errors++;
    }
    return cfg->get_var_index(var);
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx) {
    int value = stoi(ctx->CONST()->getText());
    int addr = cfg->create_new_tempvar();
    current_bb->add_instr(new ConstInstr(value, addr));
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx) {
    int addr = this->visit(ctx->expr());
    string op = ctx->ADD_SUB()->getText();
    if (op == "-") {
        int addr2 = cfg->create_new_tempvar();
        current_bb->add_instr(new NegInstr(addr, addr2));
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
        current_bb->add_instr(new AddInstr(addr1, addr2, addr3));
    } else {
        current_bb->add_instr(new SubInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->MUL_DIV()->getText();
    int addr3 = cfg->create_new_tempvar();

    if (op == "*") {
        current_bb->add_instr(new MulInstr(addr1, addr2, addr3));
    } else if (op == "/"){
        current_bb->add_instr(new DivInstr(addr1, addr2, addr3));
    } else if (op == "%"){
        current_bb->add_instr(new ModInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitPar(ifccParser::ParContext *ctx) {
    return this->visit(ctx->expr());
}


antlrcpp::Any ASTVisitor::visitComparison(ifccParser::ComparisonContext *ctx){
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->COMP()->getText();
    int res = cfg->create_new_tempvar();

    if (op == "<=") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::le));
    } else if(op == ">=") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ge));
    } else if(op == "<") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::l));
    } else if(op == ">") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::g));
    } else if (op == "==") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::e));
    } else if (op == "!=") {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ne));
    }
    return res;
}

antlrcpp::Any ASTVisitor::visitBitAnd(ifccParser::BitAndContext *ctx) {
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_AND()->getText();
    int res = cfg->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::And));

    return res;
}

antlrcpp::Any ASTVisitor::visitBitOr(ifccParser::BitOrContext *ctx) {
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_OR()->getText();
    int res = cfg->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Or));

    return res;
}


antlrcpp::Any ASTVisitor::visitBitXor(ifccParser::BitXorContext *ctx) {
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_XOR()->getText();
    int res = cfg->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Xor));

    return res;
}


antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx) {
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new RetInstr(addr));
    return 0;
}
