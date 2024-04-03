#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

class Scope {
public:

    explicit Scope(Scope* parent): parent(parent) {}

    /**
     * Vérifie si un symbole est déclaré
    */
    bool is_symbol_declared(string name);

    /**
     * Vérifie si un symbole est déclaré localement
    */
    bool is_declared_locally(string symbol);

    /**
     * Ajoute un symbole à la table des symboles
    */
    void add_to_symbol_table(string name, int index);

    /**
     * Retourne l'index d'un symbole
    */
    int get_var_index(string name);

    /**
     * Marque un symbole comme utilisé
    */
    void use_symbol(string name);

    /**
     * Retourne les symboles inutilisés
    */
    vector<string> get_unused_symbols();

private:
    map<string, int> symbol_index;    /**< part of the symbol table  */
    map<string, bool> is_symbol_used; /**< usage of symbols of the symbol table  */
    Scope* parent;
};