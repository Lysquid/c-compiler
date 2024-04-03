# Compilateur C

## Hexanome

**H4221**

- Hélène Dos Santos
- Hugo Saysana
- Mathis Nguyen
- Zeyang Kong
- Romain Benoit
- Koch Florentin

## Utilisation

Dans le repertoire makefile, faites une copie du makefile pour votre platform, et appelez le `config.mk`

Compiler et exécuter les tests :
`make -j test`

## Documentation

Générer la documentation avec doxygen : `make doc`

La documentation est au format HTML. Pour la consulter, ouvrir le fichier `html/index.html`

## Fonctionnalités

- Commentaires `/* */`
- Variables (sans les scoops)
- Constantes entières et caractères
- Expressions avec les opérateurs `+` `-` `*` `/` `%` `|` `&` `^` `!`
- Comparaisons avec `==` `!=` `<` `>` `<=` `>=`
- Déclaration et affectation de variables
- `getchar` et `putchar`
- Fonctions (version bêta/incomplète/potentiellement buggée)
- Bonus (inutile) : tests parallélisés

## Architecture

Nous avons implémenté une **IR**. L'`ASTVisitor`, qui hérite du `BaseVisitor` généré par Antlr, visite l'AST et construit l'IR. Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein du *control flow graph* `CFG`. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Pour découpler l'IR de la génération d'assembleur et donc de l'architecture, nous avons mis en place un deuxième visiteur, `IRVisitor`. Son implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction du CFG et génère le code assembleur. On peut ansi rajouter un backend pour chaque architecture en écrivant le visiteur associé, sans toucher à l'IR.

## Gestion de projet

Nous sommes partis sur une base de code commune à l'hexanome au cours la 3ème séance, en utilisant la plus avancée. Nous avons en même temps fait la transition vers l'IR. La séance d'après, nous avons pu travailler efficacement en parallèle avec un workflow centré autour de GitLab : des issues pour lister les tâches à faire, développées sur des branches de features, qu'on merge sur la branche main après avoir eu une revue de code. Les refactors importants (qui ne peuvent pas se faire en parallèle) comme le visiteur d'IR, se font hors séance. Nous prévoyons de continuer avec cette méthode de gestion.
