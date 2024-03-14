# Compilateur C

## Usage

Dans le repertoire makefile, faites une copie du makefile pour votre platform, et appelez le `config.mk`

Compiler et exécuter les tests :
`make -j test`

## Fonctionnalités

- Commentaires `/* */`
- Variables (sans les scoops)
- Constantes entières et caractères
- Expressions avec les opérateurs `+` `-` `*` `/` `%` `|` `&` `^` `!`
- Comparaisons avec `==` `!=` `<` `>` `<=` `>=`
- Déclaration et affectation de variables
- `getchar` et `putchar`
- Fonctions (version bêta/incomplète/potentiellement buggée)

## Architecture

Nous avons implémenté une **IR**. L'`ASTVisitor`, qui hérite du `BaseVisitor` généré par Antlr, visite l'AST et construit l'IR. Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein du *control flow graph* `CFG`. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Pour découpler l'IR de la génération d'assembleur et donc de l'architecture, nous avons mis en place un deuxième visiteur, `IRVisitor`. Son implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction du CFG et génère le code assembleur. On peut ansi rajouter un backend pour chaque architecture en écrivant le visiteur associé, sans toucher à l'IR.