#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"

#include "ASTVisitor.h"
#include "x86Visitor.h"
#include "CFGOptimizer.h"
#include "TypeCheckVisitor.h"

using namespace std;

int main(int argn, const char **argv) {
    stringstream in;
    if (argn == 2) {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    } else {
        cerr << "usage: ifcc path/to/file.c" << endl;
        exit(1);
    }

    antlr4::ANTLRInputStream input(in.str());

    ifccLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    tokens.fill();

    ifccParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.axiom();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }

    TypeCheckVisitor tcv;
    tcv.visit(tree);

    if (tcv.errors > 0) {
        exit(1);
    }

    ASTVisitor av;
    av.visit(tree);

    //checking for unused variables
    av.IsThereUnusedVariables();

    if (av.getNumberOfErrors() > 0) {
        cerr << "Stopping due to errors" << endl;
        exit(1);
    }

    vector <CFG*> cfgs = av.getCFGs();
    for(auto* cfg: cfgs){
        CFGOptimizer co(*cfg, cfg->getConstTable(), cfg->getInstrTable());
        co.optimization();
        co.divideOrModuloByZero();
    }


    x86Visitor xv(cout);
    vector <CFG*> optimizedCfgs = av.getCFGs();
    for(auto* cfg: optimizedCfgs){
        xv.visit(*cfg);
    }

    return 0;
}
