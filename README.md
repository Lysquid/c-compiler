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

### Antler4

Assurer 

Dans le repertoire makefile, faites une copie du makefile pour votre platform, et appelez la `config.mk`.

Pour compiler et exécuter les tests :
`make -j test`
permettra de compiler et exécuter les tests avec plusieurs threads pour plus de rapidité. Un test qui passe sera représenté dans la console par `.`, et un test qui ne passe pas sera clairement indiqué sur la console.

Un test passe si l'une des conditions suivantes est réunie:
- Le programme donné en entrée est bien compilé par GCC et IFCC, et les valeurs de retour d'exécution sont les mêmes.
- Le programme donné en entrée n'a pas pu être compilé par GCC et IFCC, et les deux compilateurs on retourné au moins une erreur.
Dans tous les autres cas, le test ne passera pas.

## Documentation

Générer la documentation avec doxygen : `make doc`

La documentation est au format HTML. Pour la consulter, ouvrir le fichier `html/index.html`

## Fonctionnalités

- Commentaires `/* */`
- Variables (sans les scopes)
- Constantes entières et caractères
- Tableaux 1D
- Expressions avec les opérateurs `+` `-` `*` `/` `%` `|` `&` `^` `!`
- Comparaisons avec `==` `!=` `<` `>` `<=` `>=`
- Déclaration et affectation de variables
- Conditions `if`, `else`
- Boucles `while`
- Opérateurs logiques NON pareseux `&&` `||`
- `getchar` et `putchar`
- Fonctions (version bêta/incomplète/potentiellement buggée)
- Bonus (inutile, sauf pour nous, ça nous a fait gagner beaucoup de temps) : tests parallélisés

## Architecture

Nous avons implémenté une **IR**. L'`ASTVisitor`, qui hérite du `BaseVisitor` généré par Antlr, visite l'AST et construit l'IR. Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein du *control flow graph* `CFG`. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Pour découpler l'IR de la génération d'assembleur et donc de l'architecture, nous avons mis en place un deuxième visiteur, `IRVisitor`. Son implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction du CFG et génère le code assembleur. On peut ansi rajouter un backend pour chaque architecture en écrivant le visiteur associé, sans toucher à l'IR.

## Gestion de projet

Nous sommes partis sur une base de code commune à l'hexanome au cours la 3ème séance, en utilisant la plus avancée. Nous avons en même temps fait la transition vers l'IR. La séance d'après, nous avons pu travailler efficacement en parallèle avec un workflow centré autour de GitLab : des issues pour lister les tâches à faire, développées sur des branches de features, qu'on merge sur la branche main après avoir eu une revue de code. Les refactors importants (qui ne peuvent pas se faire en parallèle) comme le visiteur d'IR, se font hors séance. Nous prévoyons de continuer avec cette méthode de gestion.
