#include "TypeCheckVisitor.h"
#include "Types.h"

antlrcpp::Any TypeCheckVisitor::visitProg(ifccParser::ProgContext *ctx) {
    for (ifccParser::FunctionContext *function: ctx->function()) {
        this->visit(function);
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitFunction(ifccParser::FunctionContext *ctx) {
    this->visit(ctx->parameters());
    Type return_type = Type(Type::VOID);
    if (ctx->return_type()->INT() != nullptr) {
        return_type = Type(Type::INT);
    }
    for (auto statement: ctx->statement()) {
        this->visit(statement);
    }
    return return_type;
}


antlrcpp::Any TypeCheckVisitor::visitParameters(ifccParser::ParametersContext *ctx) {
    for (auto var: ctx->VAR()) {
        string name = var->getText();
        this->types_table[name] = Type(Type::INT);
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitWhile(ifccParser::WhileContext *ctx) {
    if (Type(this->visit(ctx->expr())) == Type::VOID) {
        errors++;
        cerr << "Type mismatch in while condition" << endl;
    }
    this->visit(ctx->body);
    return Type(Type::VOID);

}

antlrcpp::Any TypeCheckVisitor::visitBreak(ifccParser::BreakContext *ctx) {
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitContinue(ifccParser::ContinueContext *ctx) {
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitIf(ifccParser::IfContext *ctx) {
    if (Type(this->visit(ctx->expr())) == Type::VOID) {
        errors++;
        cerr << "Type mismatch in if condition" << endl;
    }
    this->visit(ctx->if_block);
    if (ctx->else_block != nullptr) {
        this->visit(ctx->else_block);
    }
    return Type(Type::VOID);
}


antlrcpp::Any TypeCheckVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    for (ifccParser::StatementContext *statement: ctx->statement()) {
        this->visit(statement);
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    for (auto var: ctx->VAR()) {
        string name = var->getText();
        this->types_table[name] = Type(ctx->INT()->getText());
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitDeclarationAssignment(ifccParser::DeclarationAssignmentContext *ctx) {
    Type expr_type = this->visit(ctx->expr());
    Type declaration_type = Type(ctx->INT()->getText());
    if (expr_type != declaration_type) {
        errors++;
        cerr << "Type mismatch at declaration with assignment, assigning " << expr_type << " to " << declaration_type
             << endl;
    }
    this->types_table[ctx->VAR()->getText()] = declaration_type;
    return declaration_type;
}

antlrcpp::Any TypeCheckVisitor::visitExpression(ifccParser::ExpressionContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any TypeCheckVisitor::visitCallVoidFunction(ifccParser::CallVoidFunctionContext *ctx) {
    for (ifccParser::ExprContext *expr: ctx->expr()) {
        this->visit(expr);
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    Type expr_type = this->visit(ctx->expr());
    Type var_type = types_table[ctx->VAR()->getText()];
    if (expr_type != var_type) {
        errors++;
        cerr << "Type mismatch at assignment, assigning " << expr_type << " to " << var_type << " (" << ctx->VAR()->getText() << ")" << endl;
    }
    return var_type;
}

antlrcpp::Any TypeCheckVisitor::visitVar(ifccParser::VarContext *ctx) {
    return types_table[ctx->VAR()->getText()];
}

antlrcpp::Any TypeCheckVisitor::visitConst(ifccParser::ConstContext *ctx) {
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitCallIntFunction(ifccParser::CallIntFunctionContext *ctx) {
    for (ifccParser::ExprContext *expr: ctx->expr()) {
        this->visit(expr);
    }
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitChar(ifccParser::CharContext *ctx) {
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitSign(ifccParser::SignContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any TypeCheckVisitor::visitUnary(ifccParser::UnaryContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any TypeCheckVisitor::visitIncrementafter(ifccParser::IncrementafterContext *ctx) {
    return types_table[ctx->VAR()->getText()];
}

antlrcpp::Any TypeCheckVisitor::visitIncrementbefore(ifccParser::IncrementbeforeContext *ctx) {
    return types_table[ctx->VAR()->getText()];
}

antlrcpp::Any TypeCheckVisitor::visitAddSub(ifccParser::AddSubContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitMulDiv(ifccParser::MulDivContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitPar(ifccParser::ParContext *ctx) {
    return this->visit(ctx->expr());;
}

antlrcpp::Any TypeCheckVisitor::visitComparison(ifccParser::ComparisonContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitBitAnd(ifccParser::BitAndContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitBitOr(ifccParser::BitOrContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitBitXor(ifccParser::BitXorContext *ctx) {
    this->visit(ctx->expr(0));
    this->visit(ctx->expr(1));
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitRet(ifccParser::RetContext *ctx) {
    if (ctx->expr() != nullptr) {
        return this->visit(ctx->expr());
    }
    return Type(Type::VOID);
}
