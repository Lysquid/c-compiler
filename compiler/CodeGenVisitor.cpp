#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
    std::cout<< ".globl main\n" ;
    std::cout<< " main: \n" ;

    std::cout << "    pushq %rbp\n";
    std::cout << "    movq %rsp, %rbp\n";

    this->visit( ctx->statements() );

    this->visit( ctx->return_stmt() );
    
    std::cout << "    popq %rbp\n";
    std::cout << "    ret\n";

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitStatements(ifccParser::StatementsContext *ctx) 
{
    for(ifccParser::StatementContext * statement : ctx->statement() ) this->visit( statement );

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclarationStatement(ifccParser::DeclarationStatementContext *ctx) 
{
    std::vector<antlr4::tree::TerminalNode *> vars = ctx->VAR();
    for(antlr4::tree::TerminalNode * node : vars)
    {
        std::string var = node->getText();
        index -= 4;
        symbolTable[var] = index;
    }
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitDefinitionStatement(ifccParser::DefinitionStatementContext *ctx) 
{
    std::string var = ctx->VAR()->getText();
    int addr = this->visit( ctx->expr() );

    std::cout << "    movl " << addr << "(%rbp), %eax\n";
    std::cout << "    movl %eax, " << symbolTable[var] << "(%rbp)\n";

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignementStatement(ifccParser::AssignementStatementContext *ctx) 
{
    
    std::string var = ctx->VAR()->getText();
    int addr =  this->visit( ctx->expr() );

    std::cout << "    movl " << addr << "(%rbp), %eax\n";
    std::cout << "    movl %eax, " << symbolTable[var] << "(%rbp)\n";
    
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) 
{
    std::string var = ctx->VAR()->getText();

    if( symbolTable.find(var) == symbolTable.end() ) {
        std::cerr << "Error: variable " << var << " not found" << std::endl;
        exit(1);
    }

    return symbolTable[var];
}


antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
    int value = stoi(ctx->CONST()->getText());
    index -= 4;
    std::cout << "    movl $" << value << ", " << index << "(%rbp)\n";
    return index;
}

antlrcpp::Any CodeGenVisitor::visitSignExpr(ifccParser::SignExprContext *ctx) 
{
    int addr = this->visit( ctx->expr() );
    std::string op = ctx->ADD_SUB()->getText();
    if(op == "-") {
        index -= 4;
        std::cout << "    movl " << addr << "(%rbp), %eax\n";
        std::cout << "    negl %eax\n";
        std::cout << "    movl %eax, " << index << "(%rbp)\n";
        return index;
    }

    return addr;
}

antlrcpp::Any CodeGenVisitor::visitAdd_sub(ifccParser::Add_subContext *ctx) 
{
    int addr1 = this->visit( ctx->expr(0) );
    int addr2 = this->visit( ctx->expr(1) );
    std::string op = ctx->ADD_SUB()->getText();
    index -= 4;
    if(op == "+") {
        std::cout << "    movl " << addr1 << "(%rbp), %eax\n";
        std::cout << "    addl " << addr2 << "(%rbp), %eax\n";
        std::cout << "    movl %eax, " << index << "(%rbp)\n";
    } else {
        std::cout << "    movl " << addr1 << "(%rbp), %eax\n";
        std::cout << "    subl " << addr2 << "(%rbp), %eax\n";
        std::cout << "    movl %eax, " << index << "(%rbp)\n";
    }

    return index;
}

antlrcpp::Any CodeGenVisitor::visitMult_div(ifccParser::Mult_divContext *ctx) 
{
    int addr1 = this->visit( ctx->expr(0) );
    int addr2 = this->visit( ctx->expr(1) );
    std::string op = ctx->MULT_DIV()->getText();
    index -= 4;
    if(op == "*") {
        std::cout << "    movl " << addr1 << "(%rbp), %eax\n";
        std::cout << "    imull " << addr2 << "(%rbp), %eax\n";
        std::cout << "    movl %eax, " << index << "(%rbp)\n";
    } else {
        std::cout << "    movl " << addr1 << "(%rbp), %eax\n";
        std::cout << "    cltd\n";
        std::cout << "    idivl " << addr2 << "(%rbp)\n";
        std::cout << "    movl %eax, " << index << "(%rbp)\n";
    }

    return index;
}


antlrcpp::Any CodeGenVisitor::visitPar(ifccParser::ParContext *ctx) 
{
    return this->visit( ctx->expr() );
}

antlrcpp::Any CodeGenVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{

    int addr = this->visit( ctx->expr() );
    std::cout << "    movl " << addr << "(%rbp), %eax\n";

    return 0;
}

antlrcpp::Any SymbolVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
    this->visit( ctx->statements() );
    this->visit( ctx->return_stmt() );
    return 0;
}

antlrcpp::Any SymbolVisitor::visitStatements(ifccParser::StatementsContext *ctx) 
{
    for(ifccParser::StatementContext * statement : ctx->statement() ) this->visit( statement );

    return 0;
}

antlrcpp::Any SymbolVisitor::visitDeclarationStatement(ifccParser::DeclarationStatementContext *ctx) 
{
    std::vector<antlr4::tree::TerminalNode *> vars = ctx->VAR();
    for(antlr4::tree::TerminalNode * node : vars)
    {
        std::string var = node->getText();
        if( symbolTable.find(var) == symbolTable.end() ) {
            index -= 4;
            symbolTable[var] = index;
            numberTable[var] = -1;
        } else {
            std::cerr << "Error: variable " << var << " already declared" << std::endl;
            exit(1);
        }
    }
    return 0;
}

antlrcpp::Any SymbolVisitor::visitDefinitionStatement(ifccParser::DefinitionStatementContext *ctx) 
{
    std::string var = ctx->VAR()->getText();
    if( symbolTable.find(var) == symbolTable.end() ) {
        index -= 4;
        symbolTable[var] = index;
        numberTable[var] = 0;
    } else {
        std::cerr << "Error: variable " << var << " already declared" << std::endl;
        exit(1);
    }
    this->visit( ctx->expr() );
    return 0;
}

antlrcpp::Any SymbolVisitor::visitAssignementStatement(ifccParser::AssignementStatementContext *ctx) 
{
    std::string var = ctx->VAR()->getText();
    if( symbolTable.find(var) == symbolTable.end() ) {
        std::cerr << "Error: variable " << var << " not initialized" << std::endl;
        exit(1);
    }
    numberTable[var] = 0;
    this->visit( ctx->expr() );
    return 0;
}

antlrcpp::Any SymbolVisitor::visitVarExpr(ifccParser::VarExprContext *ctx) 
{
    std::string var = ctx->VAR()->getText();
    if( symbolTable.find(var) == symbolTable.end() ) {
        std::cerr << "Error: variable " << var << " not found" << std::endl;
        exit(1);
    } else if (numberTable[var] == -1) {
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
    this->visit( ctx->expr() );
    return 0;
}


antlrcpp::Any SymbolVisitor::visitAdd_sub(ifccParser::Add_subContext *ctx) 
{
    this->visit( ctx->expr(0) );
    this->visit( ctx->expr(1) );
    return 0;
}

antlrcpp::Any SymbolVisitor::visitMult_div(ifccParser::Mult_divContext *ctx)
{
    this->visit( ctx->expr(0) );
    this->visit( ctx->expr(1) );
    return 0;
}


antlrcpp::Any SymbolVisitor::visitPar(ifccParser::ParContext *ctx) 
{
    this->visit( ctx->expr() );
    return 0;
}

antlrcpp::Any SymbolVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx)
{
    this->visit( ctx->expr() );
    for(auto& x : numberTable) {
        if( x.second == 0 || x.second == -1) {
            std::cerr << "Error: variable " << x.first << " never used" << std::endl;
            exit(1);
        }
    }
    return 0;
}

antlrcpp::Any IRVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
    this->CFG->add_bb(new BasicBlock(this->CFG, "entry"));

    this->visit( ctx->statements() );
    this->visit( ctx->return_stmt() );
    return 0;
}