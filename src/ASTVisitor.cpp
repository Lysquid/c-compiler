#include "ASTVisitor.h"
#include "Instr.h"

antlrcpp::Any ASTVisitor::visitProg(ifccParser::ProgContext *ctx)
{
    CFG *putchar = new CFG("putchar");
    putchar->number_of_params = 1;
    putchar->return_type = 0;
    this->predefinition_cfgs.push_back(putchar);

    CFG *getchar = new CFG("getchar");
    getchar->number_of_params = 0;
    getchar->return_type = 1;
    this->predefinition_cfgs.push_back(getchar);

    for (ifccParser::FunctionContext *function : ctx->function())
    {
        this->visit(function);
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitFunction(ifccParser::FunctionContext *ctx)
{
    string name = ctx->VAR()->getText();
    if (existsCFG(name))
    {
        cerr << "ERROR: function " << name << " already declared" << endl;
        errors++;
    }

    CFG *cfg = new CFG(name);
    this->current_cfg = cfg;
    this->cfgs.push_back(cfg);
    auto *scope = new Scope(nullptr);
    auto *block = new BasicBlock(current_cfg->new_BB_name(), scope);
    cfg->add_bb(block);
    auto *end_block = new BasicBlock(current_cfg->new_BB_name(), scope);
    block->set_exit_true(end_block);
    cfg->end_block = end_block;

    current_cfg->current_bb = block;
    string return_type = ctx->return_type()->getText();
    if (return_type == "int")
    {
        current_cfg->return_type = 1;
    }
    else if (return_type == "void")
    {
        current_cfg->return_type = 0;
    }
    else
    {
        cerr << "ERROR: unknown return type" << endl;
        errors++;
    }

    this->visit(ctx->parameters());

    for (auto statement : ctx->statement())
    {
        this->visit(statement);
    }

    cfg->add_bb(end_block);
    return 0;
}

antlrcpp::Any ASTVisitor::visitParameters(ifccParser::ParametersContext *ctx)
{
    int size = ctx->VAR().size();
    current_cfg->number_of_params = size;
    for (int i = size - 1; i >= 0; i--)
    {
        string var = ctx->VAR(i)->getText();
        if (!current_cfg->current_bb->is_symbol_declared(var))
        {
            if (i >= 6)
            {
                current_cfg->current_bb->add_to_symbol_table(var, 16+(i-6)*8);
            }
            else
            {
                current_cfg->current_bb->add_to_symbol_table(var, current_cfg->get_next_free_symbol_index());
                current_cfg->current_bb->add_instr(new CopyParamInstr(i, current_cfg->current_bb->get_var_index(var)));
            }
        }
        else
        {
            cerr << "ERROR: variable " << var << " already declared" << endl;
            errors++;
        }
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitWhile(ifccParser::WhileContext *ctx)
{
    auto scope = current_cfg->current_bb->scope;

    BasicBlock *previous_block = current_cfg->current_bb;                 // bloc courant
    auto *test_block = new BasicBlock(current_cfg->new_BB_name(), scope); // bloc de test
    auto *body_block = new BasicBlock(current_cfg->new_BB_name(), scope); // corps du while
    auto *next_block = new BasicBlock(current_cfg->new_BB_name(), scope); // bloc suivant

    body_block->test_block = test_block; // notify it is a loop

    next_block->set_exit_true(previous_block->exit_true);

    // si le test est vrai on execute le corps, sinon on passe à la suite
    test_block->set_exit_true(body_block);
    test_block->set_exit_false(next_block);

    // dans le bloc courant on passe au test
    previous_block->set_exit_true(test_block);

    // à la fin du corps on ré-execute le test
    body_block->set_exit_true(test_block);

    // le bloc de test
    current_cfg->add_bb(test_block);
    current_cfg->current_bb = test_block;
    test_block->test_var_index = this->visit(ctx->expr()); // récupère le test, et la variable qui le stocke

    // le bloc de corps
    current_cfg->add_bb(body_block);
    current_cfg->current_bb = body_block;
    this->visit(ctx->body); // statements of the body

    // le bloc suivant
    current_cfg->add_bb(next_block);
    current_cfg->current_bb = next_block;

    return 0;
}

antlrcpp::Any ASTVisitor::visitBreak(ifccParser::BreakContext *ctx)
{
    BasicBlock *currentBlock = current_cfg->current_bb; // bloc courant

    if (currentBlock->test_block != nullptr)
    {
        current_cfg->current_bb->add_instr(new BreakInstr(currentBlock->test_block->exit_false->get_label()));
    }
    else
    {
        cerr << "ERROR: break statement not within a loop" << endl;
        errors++;
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitContinue(ifccParser::ContinueContext *ctx)
{
    BasicBlock *currentBlock = current_cfg->current_bb; // bloc courrant

    if (currentBlock->test_block != nullptr)
    {
        current_cfg->current_bb->add_instr(new ContinueInstr(currentBlock->test_block->get_label()));
    }
    else
    {
        cerr << "ERROR: continue statement not within a loop" << endl;
        errors++;
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitIf(ifccParser::IfContext *ctx)
{
    auto scope = current_cfg->current_bb->scope;
    auto *if_block = new BasicBlock(current_cfg->new_BB_name(), scope);
    auto *next_block = new BasicBlock(current_cfg->new_BB_name(), scope);

    BasicBlock *previous_block = current_cfg->current_bb;

    // notify if we are currently in a loop
    if (previous_block->test_block != nullptr)
    {
        if_block->test_block = previous_block->test_block;
        next_block->test_block = previous_block->test_block;
    }

    next_block->set_exit_true(current_cfg->current_bb->exit_true);
    previous_block->set_exit_true(if_block);

    if_block->set_exit_true(next_block);

    current_cfg->add_bb(if_block); // then

    previous_block->set_exit_false(next_block); // s'il n'y a pas de else, on saute à endifblock

    previous_block->test_var_index = this->visit(ctx->expr()); // le test, on stocke le resultat de la visite dans test_var_index

    current_cfg->current_bb = if_block;
    this->visit(ctx->if_block); // le bloc if

    if (ctx->else_block != nullptr)
    {
        auto *else_block = new BasicBlock(current_cfg->new_BB_name(), scope);

        // notify if we are currently in a loop
        if (previous_block->test_block != nullptr)
        {
            else_block->test_block = previous_block->test_block;
        }

        else_block->set_exit_true(next_block);
        previous_block->set_exit_false(else_block);

        current_cfg->add_bb(else_block);
        current_cfg->current_bb = else_block; // le bloc else
        this->visit(ctx->else_block);
    }

    current_cfg->add_bb(next_block); // endif
    current_cfg->current_bb = next_block;

    return 0;
}

antlrcpp::Any ASTVisitor::visitBlock(ifccParser::BlockContext *ctx)
{
    BasicBlock *previous_block = current_cfg->current_bb;

    auto block = new BasicBlock(current_cfg->new_BB_name(), new Scope(current_cfg->current_bb->scope));
    auto next_block = new BasicBlock(current_cfg->new_BB_name(), previous_block->scope);

    if (previous_block->test_block != nullptr)
    {
        block->test_block = previous_block->test_block;
        next_block->test_block = previous_block->test_block;
    }

    next_block->set_exit_true(previous_block->exit_true);
    block->set_exit_true(next_block);
    previous_block->set_exit_true(block);

    current_cfg->add_bb(block);
    current_cfg->current_bb = block;

    for (ifccParser::StatementContext *statement : ctx->statement())
    {
        this->visit(statement);
    }

    current_cfg->add_bb(next_block);
    current_cfg->current_bb = next_block;

    if (current_cfg->return_type && !current_cfg->is_return)
    {
        cerr << "ERROR: function " << current_cfg->get_label() << " should return a value" << endl;
    }

    if (!current_cfg->return_type && current_cfg->is_return)
    {
        cerr << "ERROR: void function " << current_cfg->get_label() << " should not return a value" << endl;
    }

    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx)
{
    for (auto declaration : ctx->declareAssign())
    {
        this->visit(declaration);
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitDeclareAssign(ifccParser::DeclareAssignContext *ctx)
{
    string var = ctx->VAR()->getText();
    if (current_cfg->current_bb->scope->is_declared_locally(var))
    {
        cerr << "ERROR: variable " << var << " already declared" << endl;
        errors++;
    }
    else
    {
        current_cfg->current_bb->add_to_symbol_table(var, current_cfg->get_next_free_symbol_index());
        if (ctx->expr())
        {
            int addr = this->visit(ctx->expr());
            current_cfg->current_bb->add_instr(new CopyInstr(addr, current_cfg->current_bb->get_var_index(var)));
        }
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitExpression(ifccParser::ExpressionContext *ctx)
{
    this->visit(ctx->expr());
    return 0;
}

antlrcpp::Any ASTVisitor::visitAssignment(ifccParser::AssignmentContext *ctx)
{
    string dest_var = ctx->VAR()->getText();
    string op = ctx->assignmentop->getText();

    if (!current_cfg->current_bb->is_symbol_declared(dest_var))
    {
        cerr << "ERROR: variable " << dest_var << " not initialized" << endl;
        errors++;
    }
    int dest_addr = current_cfg->current_bb->get_var_index(dest_var);
    int expr_addr = this->visit(ctx->expr());

    if (op == "=")
    {
        current_cfg->current_bb->add_instr(new CopyInstr(expr_addr, dest_addr));
    }
    if (op == "+=")
    {
        current_cfg->current_bb->add_instr(new AddInstr(dest_addr, expr_addr, dest_addr));
    }
    if (op == "-=")
    {
        current_cfg->current_bb->add_instr(new SubInstr(dest_addr, expr_addr, dest_addr));
    }
    if (op == "*=")
    {
        current_cfg->current_bb->add_instr(new MulInstr(dest_addr, expr_addr, dest_addr));
    }
    if (op == "/=")
    {
        current_cfg->current_bb->add_instr(new DivInstr(dest_addr, expr_addr, dest_addr));
    }
    return dest_addr;
}

antlrcpp::Any ASTVisitor::visitVar(ifccParser::VarContext *ctx)
{
    string var = ctx->VAR()->getText();

    if (!current_cfg->current_bb->is_symbol_declared(var))
    {
        cerr << "ERROR: variable " << var << " not found" << endl;
        errors++;
    }

    return current_cfg->current_bb->get_var_index(var);
}

antlrcpp::Any ASTVisitor::visitConst(ifccParser::ConstContext *ctx)
{
    int value = stoi(ctx->CONST()->getText());
    int addr = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    ConstInstr *constInstruction = new ConstInstr(value, addr);
    current_cfg->current_bb->add_instr(constInstruction);

    current_cfg->getConstTable()[addr] = value;
    current_cfg->getInstrTable()[addr] = constInstruction;

    return addr;
}

antlrcpp::Any ASTVisitor::visitCallIntFunction(ifccParser::CallIntFunctionContext *ctx)
{
    string name = ctx->VAR()->getText();
    if (existsCFG(name))
    {
        if (getCFG(name)->number_of_params != ctx->expr().size())
        {
            cerr << "ERROR: wrong number of parameters for function " << name << endl;
            errors++;
        }

        int dest = 0;
        int return_type = getCFG(name)->return_type;
        if (return_type)
        {
            dest = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
        }

        vector<int> args_addrs;
        for (auto argument : ctx->expr())
        {
            int addr = this->visit(argument);
            args_addrs.push_back(addr);
        }

        for (int i = args_addrs.size() - 1; i >= 0; i--)
        {
            current_cfg->current_bb->add_instr(new SetParamInstr(args_addrs[i], i));
        }
        current_cfg->current_bb->add_instr(new CallFunctionInstr(name, dest, return_type));

        if (return_type)
        {
            return dest;
        }
    }
    else
    {
        cerr << "ERROR: unknown function " << name << endl;
        errors++;
    }
    return 0;
}

antlrcpp::Any ASTVisitor::visitChar(ifccParser::CharContext *ctx)
{
    string char_str = ctx->CHAR()->getText();
    int value = static_cast<unsigned char>(char_str.c_str()[1]);
    int addr = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
    current_cfg->current_bb->add_instr(new ConstInstr(value, addr));
    return addr;
}

antlrcpp::Any ASTVisitor::visitSign(ifccParser::SignContext *ctx)
{
    int addr = this->visit(ctx->expr());
    string op = ctx->ADD_SUB()->getText();
    if (op == "-")
    {
        int addr2 = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
        current_cfg->current_bb->add_instr(new NegInstr(addr, addr2));
        return addr2;
    }
    return addr;
}

antlrcpp::Any ASTVisitor::visitUnary(ifccParser::UnaryContext *ctx)
{
    int term = this->visit(ctx->expr());
    string op = ctx->UNARY_OP()->getText();
    int dest = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
    if (op == "!")
    {
        current_cfg->current_bb->add_instr(new NotInstr(term, dest));
    }
    return dest;
}

antlrcpp::Any ASTVisitor::visitIncrementafter(ifccParser::IncrementafterContext *ctx)
{
    int term = current_cfg->current_bb->get_var_index(ctx->VAR()->getText());
    int dest = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
    string op = ctx->INCREMENT()->getText();
    if (op == "++")
    {
        current_cfg->current_bb->add_instr(new IncrementafterInstr(term, dest));
    }
    else if (op == "--")
    {
        current_cfg->current_bb->add_instr(new DecrementafterInstr(term, dest));
    }
    return dest;
}

antlrcpp::Any ASTVisitor::visitIncrementbefore(ifccParser::IncrementbeforeContext *ctx)
{
    int term = current_cfg->current_bb->get_var_index(ctx->VAR()->getText());
    int dest = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());
    string op = ctx->INCREMENT()->getText();
    if (op == "++")
    {
        current_cfg->current_bb->add_instr(new IncrementbeforeInstr(term, dest));
    }
    else if (op == "--")
    {
        current_cfg->current_bb->add_instr(new DecrementbeforeInstr(term, dest));
    }
    return dest;
}

antlrcpp::Any ASTVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->ADD_SUB()->getText();
    int dest = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    if (op == "+")
    {
        current_cfg->current_bb->add_instr(new AddInstr(term1, term2, dest));
    }
    else
    {
        current_cfg->current_bb->add_instr(new SubInstr(term1, term2, dest));
    }
    return dest;
}

antlrcpp::Any ASTVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    int addr1 = this->visit(ctx->expr(0));
    int addr2 = this->visit(ctx->expr(1));
    string op = ctx->MUL_DIV()->getText();
    int addr3 = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    if (op == "*")
    {
        current_cfg->current_bb->add_instr(new MulInstr(addr1, addr2, addr3));
    }
    else if (op == "/")
    {
        current_cfg->current_bb->add_instr(new DivInstr(addr1, addr2, addr3));
    }
    else if (op == "%")
    {
        current_cfg->current_bb->add_instr(new ModInstr(addr1, addr2, addr3));
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
    int res = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    if (op == "<=")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::le));
    }
    else if (op == ">=")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ge));
    }
    else if (op == "<")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::l));
    }
    else if (op == ">")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::g));
    }
    else if (op == "==")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::e));
    }
    else if (op == "!=")
    {
        current_cfg->current_bb->add_instr(new CmpInstr(term1, term2, res, CmpInstr::ne));
    }
    return res;
}


antlrcpp::Any ASTVisitor::visitLogicop(ifccParser::LogicopContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->LOGIC()->getText();
    int res = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    if (op == "||")
    {
        current_cfg->current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Or));
    }
    if (op == "&&")
    {
        current_cfg->current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::And));
    }

    return res;
}


antlrcpp::Any ASTVisitor::visitBitAnd(ifccParser::BitAndContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_AND()->getText();
    int res = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    current_cfg->current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::And));

    return res;
}


antlrcpp::Any ASTVisitor::visitBitOr(ifccParser::BitOrContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_OR()->getText();
    int res = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    current_cfg->current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Or));

    return res;
}


antlrcpp::Any ASTVisitor::visitBitXor(ifccParser::BitXorContext *ctx)
{
    int term1 = this->visit(ctx->expr(0));
    int term2 = this->visit(ctx->expr(1));
    string op = ctx->BIT_XOR()->getText();
    int res = current_cfg->current_bb->create_new_tempvar(current_cfg->get_next_free_symbol_index());

    current_cfg->current_bb->add_instr(new BitInstr(term1, term2, res, BitInstr::Xor));

    return res;
}


antlrcpp::Any ASTVisitor::visitRet(ifccParser::RetContext *ctx)
{
    int return_type = current_cfg->return_type;
    if (!ctx->expr())
    {
        if (return_type == 1)
        {
            cerr << "ERROR: function " << current_cfg->get_label() << " should return a value" << endl;
            errors++;
        }
        else
        {
            current_cfg->current_bb->add_instr(new RetVoidInstr(current_cfg->end_block->get_label()));
            current_cfg->is_return = 1;
        }
    }
    else
    {
        int addr = this->visit(ctx->expr());
        if (return_type == 1)
        {
            current_cfg->current_bb->add_instr(new RetInstr(addr, current_cfg->end_block->get_label()));
            current_cfg->is_return = 1;
        }
        else
        {
            current_cfg->current_bb->add_instr(new RetVoidInstr(current_cfg->end_block->get_label()));
            current_cfg->is_return = 1;
        }
    }

    return 0;
}

void ASTVisitor::IsThereUnusedVariables()
{
    vector<string> UnusedVariables = current_cfg->get_unused_symbols();
    for (string &var : UnusedVariables)
    {
        cerr << "WARN : unused variable " << var << endl;
    }
}
