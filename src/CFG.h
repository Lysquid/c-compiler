#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <initializer_list>

#include "Instr.h"
#include "BasicBlock.h"

using namespace std;

class IRVisitor;

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
     The entry block is the one with the same label as the AST function name.
       (it could be the first of bbs, or it could be defined by an attribute value)
     The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG
{
public:
    CFG(string name)
    {
        this->name = name;
        next_free_symbol_index = 0;
        next_bb_number = 0;
    }

    /**
     * Ajoute un bloc à la fin du CFG
    */
    void add_bb(BasicBlock *bb);

    /**
     * Récupère un bloc par son label
    */
    BasicBlock *get_bb(string label);

    /**
     * Récupère les symboles inutilisés
    */
    vector<string> get_unused_symbols();

    /**
     * Vérifie si un bloc est dans le CFG
    */
    bool bb_in_cfg(string name);

    /**
     * Crée un nouveau nom de bloc 
    */
    string new_BB_name();

    /**
     * Récupère le label du CFG
    */
    string get_label() { return name; }

    /**
     * Récupère l'index du prochain symbole libre de la table des symboles
    */
    int get_next_free_symbol_index();

    vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/

    BasicBlock *current_bb;

    BasicBlock *end_block;

    int return_type; /**< 0 if void, 1 if int*/

    int number_of_params = 0; /**< number of parameters of the function */

    int is_return = 0; /**< 0 if not return, 1 if return */

    /**
     * Récupère la table des constantes
    */
    unordered_map<int, int>& getConstTable(){
        return const_index;
    }

    /**
     * Récupère la table des instructions
    */
    unordered_map<int, Instr*>& getInstrTable(){
        return instr_index;
    }

    void printCFG();
    
protected:

    int next_free_symbol_index = 0;  /**< to allocate new symbols in the symbol table */
    int next_bb_number = 0;           /**< just for naming */
    string name;

    unordered_map<int, int> const_index;
    unordered_map<int, Instr*> instr_index;
};
