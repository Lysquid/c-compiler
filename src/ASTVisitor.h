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
    /**
     * Visite le programme sous forme d'AST et génère l'IR associée
     */
    antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;

    /**
     * Visite une fonction et génère le CFG associé
     */
    antlrcpp::Any visitFunction(ifccParser::FunctionContext *ctx) override;

    /**
     * Visite les paramètres d'une fonction et les ajoute à la table des symboles de CFG de cette function
     */
    antlrcpp::Any visitParameters(ifccParser::ParametersContext *ctx) override;

    /**
     * Visite un bloc de code et génère les CFG associé
     */
    antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;

    /**
     * Visite un bloc While et génère les CFG associé
     */
    antlrcpp::Any visitWhile(ifccParser::WhileContext *ctx) override;

    /**
     * Visite une instruction break
     */
    antlrcpp::Any visitBreak(ifccParser::BreakContext *ctx) override;

    /**
     * Visite une instruction continue
     */
    antlrcpp::Any visitContinue(ifccParser::ContinueContext *ctx) override;

    /**
     * Visite un bloc If et génère les CFG associé
     */
    antlrcpp::Any visitIf(ifccParser::IfContext *ctx) override;

    /**
     * Visite une instruction return
     */
    antlrcpp::Any visitRet(ifccParser::RetContext *ctx) override;

    /**
     * Visite une déclaration de tableau
     */
    antlrcpp::Any visitArrayDeclaration(ifccParser::ArrayDeclarationContext *ctx) override;

    /**
     * Visite une déclaration de tableau avec affectation
     */
    antlrcpp::Any visitArrayDecl(ifccParser::ArrayDeclContext *ctx) override;

    /**
     * Visite un élement de tableau
     */
    antlrcpp::Any visitArrayAccess(ifccParser::ArrayAccessContext *ctx) override;

    /**
     * Visite une affectation d'élement de tableau 
     */
    antlrcpp::Any visitArrayAssignment(ifccParser::ArrayAssignmentContext *ctx) override;


    /**
     * Visite une déclaration de variable
     */
    antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

    /**
     * Visite une déclaration de variable avec affectation
     */
    antlrcpp::Any visitDeclareAssign(ifccParser::DeclareAssignContext *ctx) override;

    /**
     * Visite une expression
     */
    antlrcpp::Any visitExpression(ifccParser::ExpressionContext *ctx) override;

    /**
     * Visite un appel de fonction
     */
    antlrcpp::Any visitCallFunction(ifccParser::CallFunctionContext *ctx) override;

    /**
     * Visite une affectation
     */
    antlrcpp::Any visitAssignment(ifccParser::AssignmentContext *ctx) override;

    /**
     * Visite une variable
     */
    antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override;

    /**
     * Visite une constante
     */
    antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override;

    /**
     * Visite un caractère
     */
    antlrcpp::Any visitChar(ifccParser::CharContext *ctx) override;

    /**
     * Visite le signe d'une expression
     */
    antlrcpp::Any visitSign(ifccParser::SignContext *ctx) override;

    /**
     * Visite une expression avec un opérateur unaire !
     */
    antlrcpp::Any visitUnary(ifccParser::UnaryContext *ctx) override;

    /**
     * Visite une expression avec un opérateur unaire ++ ou -- après la variable
     */
    antlrcpp::Any visitIncrementAfter(ifccParser::IncrementAfterContext *ctx) override;

    /**
     * Visite une expression avec un opérateur unaire ++ ou -- avant la variable
     */
    antlrcpp::Any visitIncrementBefore(ifccParser::IncrementBeforeContext *ctx) override;

    /**
     * Visite une expression avec un opérateur binaire + ou -
     */
    antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;

    /**
     * Visite une expression avec un opérateur binaire * ou / ou %
     */
    antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;

    /**
     * Visite une expression avec un opérateur de comparaison < ou <= ou > ou >= ou == ou !=
     */
    antlrcpp::Any visitComparison(ifccParser::ComparisonContext *ctx) override;

    /**
     * Visite une expression avec un opérateur logique || ou &&
     */
    antlrcpp::Any visitLogicOp(ifccParser::LogicOpContext *ctx) override;

    /**
     * Visite une expression avec un opérateur binaire &
     */
    antlrcpp::Any visitBitAnd(ifccParser::BitAndContext *ctx) override;

    /**
     * Visite une expression avec un opérateur binaire |
     */
    antlrcpp::Any visitBitOr(ifccParser::BitOrContext *ctx) override;

    /**
     * Visite une expression avec un opérateur binaire ^
     */
    antlrcpp::Any visitBitXor(ifccParser::BitXorContext *ctx) override;

    /**
     * Visite une expression entre parenthèses
     */
    antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override;

    int getNumberOfErrors() const { return errors; }

    /**
     * Alertes sur les variables non utilisées
     */
    void IsThereUnusedVariables();

    /**
     * Récupère les CFG générés
    */
    vector<CFG *> getCFGs() { return cfgs; }

    /**
     * Vérifie si un CFG existe déjà
     */
    bool existsCFG(string name)
    {
        for (auto cfg : cfgs)
        {
            if (cfg->get_label() == name)
            {
                return true;
            }
        }
        for (auto cfg : predefinition_cfgs)
        {
            if (cfg->get_label() == name)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Récupère un CFG par son nom
     */
    CFG *getCFG(string name)
    {
        for (auto cfg : cfgs)
        {
            if (cfg->get_label() == name)
            {
                return cfg;
            }
        }
        for (auto cfg : predefinition_cfgs)
        {
            if (cfg->get_label() == name)
            {
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
