#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "CFG.h"
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class ASTVisitor : public ifccBaseVisitor
{
public:
    antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

    antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;

    antlrcpp::Any visitParameters(ifccParser::ParametersContext *ctx) override;

    antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

    antlrcpp::Any visitWhile(ifccParser::WhileContext *ctx) override;

    antlrcpp::Any visitBreak(ifccParser::BreakContext *ctx) override;

    antlrcpp::Any visitContinue(ifccParser::ContinueContext *ctx) override;
    
    antlrcpp::Any visitIf(ifccParser::IfContext *ctx) override;

    antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override;

    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

    antlrcpp::Any visitDeclareAssign(ifccParser::DeclareAssignContext *ctx) override;

    antlrcpp::Any visitExpression(ifccParser::ExpressionContext *ctx) override;

    antlrcpp::Any visitCallIntFunction(ifccParser::CallIntFunctionContext *ctx) override;

    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;

    antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;

    antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

    antlrcpp::Any visitChar(ifccParser::CharContext *ctx) override;

    antlrcpp::Any visitSign(ifccParser::SignContext *ctx) override;

    antlrcpp::Any visitUnary(ifccParser::UnaryContext *ctx) override;

    antlrcpp::Any visitIncrementafter(ifccParser::IncrementafterContext *ctx) override;

    antlrcpp::Any visitIncrementbefore(ifccParser::IncrementbeforeContext *ctx) override;

    antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;

    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;

    antlrcpp::Any visitComparison(ifccParser::ComparisonContext *ctx) override;

    antlrcpp::Any visitLogicop(ifccParser::LogicopContext *ctx) override;

    antlrcpp::Any visitBitAnd(ifccParser::BitAndContext *ctx) override;

    antlrcpp::Any visitBitOr(ifccParser::BitOrContext *ctx) override;

    antlrcpp::Any visitBitXor(ifccParser::BitXorContext *ctx) override;

    antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

    int getNumberOfErrors() const { return errors; }

    void IsThereUnusedVariables();

    vector<CFG *> getCFGs() { return cfgs; }

    bool existsCFG(string name){
        for (auto cfg : cfgs){
            if (cfg->get_label() == name){
                return true;
            }
        }
        for (auto cfg : predefinition_cfgs){
            if (cfg->get_label() == name){
                return true;
            }
        }
        return false;
    }

    CFG *getCFG(string name){
        for (auto cfg : cfgs){
            if (cfg->get_label() == name){
                return cfg;
            }
        }
        for (auto cfg : predefinition_cfgs){
            if (cfg->get_label() == name){
                return cfg;
            }
        }
        return nullptr;
    }


private:
    int errors = 0;
    vector<CFG *> cfgs;
    vector<CFG *> predefinition_cfgs;
    CFG *current_cfg;
};
