#include "ASTVisitor.h"

antlrcpp::Any ASTVisitor::visitProg(ifccParser::ProgContext *ctx)
{

    for (ifccParser::FunctionContext *function : ctx->function())
    {
        this->visit(function);
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
    string name = ctx->VAR()->getText();
    BasicBlock *bb = new BasicBlock(name);
    cfg->add_bb(bb);
    current_bb = bb;
    string return_type = ctx->return_type()->getText();
    if (return_type == "int")
    {
        current_bb->return_type = 1;
    }
    else if (return_type == "void")
    {
        current_bb->return_type = 0;
    }
    else
    {
        cerr << "ERROR: unknown return type" << endl;
        errors++;
    }

    this->visit(ctx->parameters());

    this->visit(ctx->block());
    return 0;
}

antlrcpp::Any ASTVisitor::visitParameters(ifccParser::ParametersContext *ctx)
{
    current_bb->number_of_params = ctx->VAR().size();
    int i = 0;
    for (antlr4::tree::TerminalNode *node : ctx->VAR())
    {
                string var = node->getText();
        if (!current_bb->symbol_in_table(var))
        {
            current_bb->add_to_symbol_table(var);
            current_bb->add_instr(new CopyparamInstr(i, current_bb->get_var_index(var)));
            i++;
        }
        else
        {
            cerr << "ERROR: variable " << var << " already declared" << endl;
            errors++;
        }
    }
    return 0;
}


antlrcpp::Any ASTVisitor::visitCondstatement(ifccParser::CondstatementContext *ctx) {
    this->visit(ctx->condblock());
    return 0;
}

antlrcpp::Any ASTVisitor::visitCondblock(ifccParser::CondblockContext *ctx) {
    auto *ifblock = new BasicBlock(cfg->new_BB_name());
    auto *endifblock = new BasicBlock(cfg->new_BB_name());
    auto *elseblock = new BasicBlock(cfg->new_BB_name());

    BasicBlock * blockBeforeJump = current_bb;

    blockBeforeJump->set_exit_true(ifblock);
    ifblock->set_exit_true(endifblock);

    elseblock->set_exit_true(endifblock);
    cfg->add_bb(ifblock); // then

    blockBeforeJump->set_exit_false(endifblock); // s'il n'y a pas de else, on saute à endifblock

    blockBeforeJump->test_var_index = this->visit(ctx->expr()); // le test, on stocke le resultat de la visite dans test_var_index

    current_bb = ifblock;
    this->visit(ctx->block()); // le bloc if

    if(ctx->elseblock() != nullptr){
        cfg->add_bb(elseblock);
        blockBeforeJump->set_exit_false(elseblock);
        current_bb = elseblock; // le bloc else
        this->visit(ctx->elseblock());
    }

    cfg->add_bb(endifblock); // endif
    current_bb = endifblock;

    return 0;
}

antlrcpp::Any ASTVisitor::visitElseifblock(ifccParser::ElseifblockContext *ctx){
    this->visit(ctx->condblock());

    return 0;
}

antlrcpp::Any ASTVisitor::visitSimpleelse(ifccParser::SimpleelseContext *ctx){
    this->visit(ctx->block());
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    for (antlr4::tree::TerminalNode *node: ctx->VAR()) {
        string var = node->getText();
        if (!current_bb->symbol_in_table(var))
        {
            current_bb->add_to_symbol_table(var);
        }
        else
        {
            cerr << "ERROR: variable " << var << " already declared" << endl;
            errors++;
        }
    }
    return 0;
}


antlrcpp::Any ASTVisitor::visitBlock(ifccParser::BlockContext *ctx)
{
    for (ifccParser::StatementContext *statement : ctx->statement())
    {
        this->visit(statement);
    }

    if (current_bb->return_type && !current_bb->is_return)
    {
        cerr << "ERROR: function " << current_bb->get_label() << " should return a value" << endl;
    }

    if (!current_bb->return_type && current_bb->is_return)
    {
        cerr << "ERROR: void function " << current_bb->get_label() << " should not return a value" << endl;
    }

    return 0;
}

antlrcpp::Any ASTVisitor::visitGetchar(ifccParser::GetcharContext *ctx) {
    int addr = current_bb->create_new_tempvar();
    current_bb->add_instr(new GetcharInstr(addr));
    return addr;
}



antlrcpp::Any ASTVisitor::visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx)
{
    string var = ctx->VAR()->getText();

    if (!current_bb->symbol_in_table(var))
    {
        current_bb->add_to_symbol_table(var);
    }
    else
    {
        cerr << "ERROR: variable " << var << " already declared" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new CopyInstr(addr, current_bb->get_var_index(var)));
    return 0;
}

antlrcpp::Any ASTVisitor::visitExpression(ifccParser::ExpressionContext *ctx)
{
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any ASTVisitor::visitCallVoidFunction(ifccParser::CallVoidFunctionContext *ctx)
{
    string name = ctx->VAR()->getText();
    if (cfg->bb_in_cfg(name))
    {
        if (cfg->get_bb(name)->number_of_params != ctx->expr().size())
        {
            cerr << "ERROR: wrong number of parameters for function " << name << endl;
            errors++;
        }
        int i = 0;
        int return_type = cfg->get_bb(name)->return_type;
        int dest = 0;
        if (return_type)
        {
            dest = current_bb->create_new_tempvar();
        }
        for (ifccParser::ExprContext *expr : ctx->expr())
        {
            int addr = this->visit(expr);
            current_bb->add_instr(new SetparamInstr(addr, i));
            i++;
        }
        current_bb->add_instr(new CallfunctionInstr(name, dest, return_type));
    }
    else
    {
        cerr << "ERROR: unknown function " << name << endl;
        errors++;
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx)
{
    string var = ctx->VAR()->getText();
    if (!current_bb->symbol_in_table(var))
    {
        cerr << "ERROR: variable " << var << " not initialized" << endl;
        errors++;
    }
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new CopyInstr(addr, current_bb->get_var_index(var)));
    return addr;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx)
{
    string var = ctx->VAR()->getText();

    if (!current_bb->symbol_in_table(var))
    {
        cerr << "ERROR: variable " << var << " not found" << endl;
        errors++;
    }
    return current_bb->get_var_index(var);
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx)
{
    int value = stoi(ctx->CONST()->getText());
    int addr = current_bb->create_new_tempvar();
    current_bb->add_instr(new ConstInstr(value, addr));
    return addr;
}

antlrcpp::Any ASTVisitor::visitPutchar(ifccParser::PutcharContext *ctx) {
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new PutcharInstr(addr));
    return 0;
}


antlrcpp::Any ASTVisitor::visitCallIntFunction(ifccParser::CallIntFunctionContext *ctx)
{
    string name = ctx->VAR()->getText();
    int dest = 0;
    if (cfg->bb_in_cfg(name))
    {
        if (cfg->get_bb(name)->number_of_params != ctx->expr().size())
        {
            cerr << "ERROR: wrong number of parameters for function " << name << endl;
            errors++;
        }

        int i = 0;
        int return_type = cfg->get_bb(name)->return_type;
        
        if (!return_type)
        {
            cerr << "ERROR: void function " << name << " couldn't return a value" << endl;
            errors++;
        }
        else
        {
            dest = current_bb->create_new_tempvar();

        }

        for (ifccParser::ExprContext *expr : ctx->expr())
        {
            int addr = this->visit(expr);
            current_bb->add_instr(new SetparamInstr(addr, i));
            i++;
        }
        current_bb->add_instr(new CallfunctionInstr(name, dest, return_type));
    }
    else
    {
        cerr << "ERROR: unknown function " << name << endl;
        errors++;
    }
    return dest;
    
}

antlrcpp::Any ASTVisitor::visitCarac(ifccParser::CaracContext *ctx) {
    string carac = ctx->CARAC()->getText();
    const char* charConv = carac.c_str();
    int value = charConv[1];
    int addr = current_bb->create_new_tempvar();
    current_bb->add_instr(new ConstInstr(value, addr));
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx) {
    int addr = this->visit(ctx->expr());
    string op = ctx->ADD_SUB()->getText();
    if (op == "-")
    {
        int addr2 = current_bb->create_new_tempvar();
        current_bb->add_instr(new NegInstr(addr, addr2));
        return addr2;
    }
    return addr;
}

antlrcpp::Any ASTVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->ADD_SUB()->getText();
    int addr3 = current_bb->create_new_tempvar();

    if (op == "+")
    {
        current_bb->add_instr(new AddInstr(addr1, addr2, addr3));
    }
    else
    {
        current_bb->add_instr(new SubInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->MUL_DIV()->getText();
    int addr3 = current_bb->create_new_tempvar();

    if (op == "*")
    {
        current_bb->add_instr(new MulInstr(addr1, addr2, addr3));
    }
    else if (op == "/")
    {
        current_bb->add_instr(new DivInstr(addr1, addr2, addr3));
    }
    else if (op == "%")
    {
        current_bb->add_instr(new ModInstr(addr1, addr2, addr3));
    }
    return addr3;
}

antlrcpp::Any ASTVisitor::visitPar(ifccParser::ParContext *ctx)
{
    return this->visit(ctx->expr());
}

antlrcpp::Any ASTVisitor::visitComparison(ifccParser::ComparisonContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->COMP()->getText();
    int res = current_bb->create_new_tempvar();

    if (op == "<=")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::le));
    }
    else if (op == ">=")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ge));
    }
    else if (op == "<")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::l));
    }
    else if (op == ">")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::g));
    }
    else if (op == "==")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::e));
    }
    else if (op == "!=")
    {
        current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ne));
    }
    return res;
}

antlrcpp::Any ASTVisitor::visitBitAnd(ifccParser::BitAndContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_AND()->getText();
    int res = current_bb->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::And));

    return res;
}

antlrcpp::Any ASTVisitor::visitBitOr(ifccParser::BitOrContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_OR()->getText();
    int res = current_bb->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Or));

    return res;
}

antlrcpp::Any ASTVisitor::visitBitXor(ifccParser::BitXorContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_XOR()->getText();
    int res = current_bb->create_new_tempvar();

    current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Xor));

    return res;
}

antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx)
{
    int addr = this->visit(ctx->expr());
    current_bb->add_instr(new RetInstr(addr));
    current_bb->is_return = 1;
    return 0;
}

void ASTVisitor::IsThereUnusedVariables() {
    vector<string> UnusedVariables= cfg->get_unused_symbols();
    for(string& var : UnusedVariables){
        cerr << "WARN : unused variable "<< var << endl;
    }
}
