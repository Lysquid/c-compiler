#include "TypeCheckVisitor.h"
#include "Types.h"

antlrcpp::Any TypeCheckVisitor::visitProg(ifccParser::ProgContext *ctx) {
    for (ifccParser::FunctionContext *function: ctx->function()) {
        this->visit(function);
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitFunction(ifccParser::FunctionContext *ctx) {
    auto scope_var_types = this->var_types;
    this->var_types.clear();
    string name = ctx->VAR()->getText();
    this->visit(ctx->parameters());
    Type return_type = Type(Type::VOID);
    if (ctx->return_type()->TYPE() != nullptr) {
        return_type = Type(Type::INT);
    }
    this->func_types[name] = return_type;
    this->current_func_type = return_type;
    for (auto statement: ctx->statement()) {
        this->visit(statement);
    }
    this->var_types = scope_var_types;
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitParameters(ifccParser::ParametersContext *ctx) {
    for (int i = 0; i < ctx->VAR().size(); i++) {
        string name = ctx->VAR(i)->getText();
        Type type = ctx->TYPE(i)->getText();
        this->var_types[name] = type;
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitWhile(ifccParser::WhileContext *ctx) {
    if (Type(this->visit(ctx->expr())) == Type::VOID) {
        errors++;
        cerr << "ERROR: Type mismatch in while condition" << endl;
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
        cerr << "ERROR: Type mismatch in if condition" << endl;
    }
    this->visit(ctx->if_block);
    if (ctx->else_block != nullptr) {
        this->visit(ctx->else_block);
    }
    return Type(Type::VOID);
}


antlrcpp::Any TypeCheckVisitor::visitBlock(ifccParser::BlockContext *ctx) {
    auto scope_var_types = this->var_types;
    for (ifccParser::StatementContext *statement: ctx->statement()) {
        this->visit(statement);
    }
    this->var_types = scope_var_types;
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
    Type declaration_type = Type(ctx->TYPE()->getText());
    for (auto declaration: ctx->declareAssign()) {
        Type expr_type = this->visit(declaration);
        string var = declaration->VAR()->getText();
        if (declaration->expr() && expr_type != declaration_type) {
            errors++;
            cerr << "ERROR: Type mismatch at declaration, assigning " << expr_type << " to " << declaration_type << " (" << var << ")" << endl;
        }
        this->var_types[var] = declaration_type;
    }
    return Type(Type::VOID);
}

antlrcpp::Any TypeCheckVisitor::visitDeclareAssign(ifccParser::DeclareAssignContext *ctx) {
    if (ctx->expr()) {
        return this->visit(ctx->expr());
    } else {
        return Type(Type::VOID);
    }
}

antlrcpp::Any TypeCheckVisitor::visitExpression(ifccParser::ExpressionContext *ctx) {
    return this->visit(ctx->expr());
}

antlrcpp::Any TypeCheckVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
    Type expr_type = this->visit(ctx->expr());
    Type var_type = var_types[ctx->VAR()->getText()];
    if (expr_type != var_type) {
        errors++;
        cerr << "ERROR: Type mismatch at assignment, assigning " << expr_type << " to " << var_type << " (" << ctx->VAR()->getText() << ")" << endl;
    }
    return var_type;
}

antlrcpp::Any TypeCheckVisitor::visitVar(ifccParser::VarContext *ctx) {
    return var_types[ctx->VAR()->getText()];
}

antlrcpp::Any TypeCheckVisitor::visitConst(ifccParser::ConstContext *ctx) {
    return Type(Type::INT);
}

antlrcpp::Any TypeCheckVisitor::visitCallFunction(ifccParser::CallFunctionContext *ctx) {
    string name = ctx->VAR()->getText();
    for (ifccParser::ExprContext *expr: ctx->expr()) {
        this->visit(expr);
    }
    return this->func_types[name];
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
    return var_types[ctx->VAR()->getText()];
}

antlrcpp::Any TypeCheckVisitor::visitIncrementbefore(ifccParser::IncrementbeforeContext *ctx) {
    return var_types[ctx->VAR()->getText()];
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
        if (this->current_func_type == Type::VOID) {
            cerr << "WARNING: Returning value in void function" << endl;
        } else {
            Type return_type = this->visit(ctx->expr());
            if (this->current_func_type != return_type) {
                errors++;
                cerr << "ERROR: Type mismatch for return value in non void function" << endl;
            }
        }
    } else {
        if (this->current_func_type != Type::VOID) {
            errors++;
            cerr << "ERROR: Returning nothing in non void function" << endl;
        }
    }
    return Type(Type::VOID);
}
