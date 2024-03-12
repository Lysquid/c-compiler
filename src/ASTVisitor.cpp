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
    cfg->current_bb->add_instr(new CopyInstr(addr, cfg->get_var_index(var)));
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    string var = ctx->VAR()->getText();
    if (!cfg->symbol_in_table(var)) {
        cerr << "ERROR: variable " << var << " not initialized" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_instr(new CopyInstr(addr, cfg->get_var_index(var)));
    return 0;
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


antlrcpp::Any ASTVisitor::visitComparison(ifccParser::ComparisonContext *ctx){
  int term1 = this->visit(ctx->expr(0));
  int term2 = this->visit(ctx->expr(1));
  string op = ctx->COMP()->getText();

//  if (op == "<=") {
//      cfg->current_bb->add_instr(new LessEqCmpInstr(term1, term2));
//  } else if(op == ">=") {
//      cfg->current_bb->add_instr(new GreaterEqCmpInstr(term1, term2));
//  } else if(op == "<") {
//      cfg->current_bb->add_instr(new LessCmpInstr(term1, term2));
//  } else if(op == ">") {
//      cfg->current_bb->add_instr(new GreaterCmpInstr(term1, term2));
//  }

  return 0;
}


antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx) {
    int addr = this->visit(ctx->expr());
    cfg->current_bb->add_instr(new RetInstr(addr));
    return 0;
}
