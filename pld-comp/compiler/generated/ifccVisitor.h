
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ifccParser.
 */
class  ifccVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ifccParser.
   */
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) = 0;

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitStatements(ifccParser::StatementsContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationStatement(ifccParser::DeclarationStatementContext *context) = 0;

    virtual antlrcpp::Any visitDefinitionStatement(ifccParser::DefinitionStatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignementStatement(ifccParser::AssignementStatementContext *context) = 0;

    virtual antlrcpp::Any visitPar(ifccParser::ParContext *context) = 0;

    virtual antlrcpp::Any visitVarExpr(ifccParser::VarExprContext *context) = 0;

    virtual antlrcpp::Any visitMult_div(ifccParser::Mult_divContext *context) = 0;

    virtual antlrcpp::Any visitSignVarExpr(ifccParser::SignVarExprContext *context) = 0;

    virtual antlrcpp::Any visitAdd_sub(ifccParser::Add_subContext *context) = 0;

    virtual antlrcpp::Any visitSignConstExpr(ifccParser::SignConstExprContext *context) = 0;

    virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *context) = 0;

    virtual antlrcpp::Any visitReturn_stmt(ifccParser::Return_stmtContext *context) = 0;


};

