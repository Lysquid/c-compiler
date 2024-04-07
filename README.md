# Compilateur C IFCC

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

Installez Antler4, avec le gestionaire de système, ou en exécutant le script `./install-antlr.sh`

Dans le repertoire `makefile`, faites une copie du makefile pour votre platform, et appelez le `config.mk`. Si vous avec utilisez le script d'installation, cette étape n'est pas nécessaire.

### Utilisation

Compilez le projet : `make -j` (le flag permet de compiler en parallèle)

Vous pouvez maintenant compiler un programme de notre sous ensemble du C vers x86 avec `./ifcc program.c`

### Tests

Compilez et exécuter les tests :
`make -j test`

Pour tester un seul programme : `./ifcc-test.py program.c`

Un test qui passe sera représenté dans la console par `.`, et un test qui ne passe pas sera clairement indiqué sur la console.

Un test passe si l'une des conditions suivantes est réunie :

- Le programme donné en entrée est bien compilé par GCC et IFCC, et les valeurs de retour d'exécution sont les mêmes.
- Le programme donné en entrée n'a pas pu être compilé par GCC et IFCC, et les deux compilateurs on retourné au moins une erreur.
Dans tous les autres cas, le test ne passera pas.

### Documentation

Générez la documentation avec doxygen : `make doc`

La documentation est au format HTML. Pour la consulter, ouvrez le fichier `html/index.html`

## Manuel utilisateur

Ce projet permet de compiler un sous ensemble du C, qui est délimité dans cette partie.

### Commentaires

Les commentaires du type `/* */` et `//` sont supportés :

```c
// salut
a = 1;
/*
Je suis un commentaire
multiline
*/
```

### Variables

Les déclarations de variable sont les même qu'en C. Seuls le type `int` est supporté. Le type `char` fonctionne, et est traité comme un `int`.

Il est également possible d'affecter une valeur **constante** (un entier) à une variable avec `variable = constante`. 

```c
int a;
int b = 2;
int x=1, y, z=3;
a = 5;
```

Comme pour avec GCC, redéclarer une variable, utiliser une variable non déclarée ou avant sa déclaration lève une erreur.

### Caractères

Un unique caractère entre peut être utilisé pour assigner une variable (la valeur ASCII corespondante est stockée).

```c
int c1 = 'a';   // 97
char c2 = 'b';  // 98
```

Les caractère spéciaux tels que `\n` ne fonctionnent pas.

### Tableaux

### Expressions arithmétiques

Les opérateurs suivants sont supportés : `+` `-` `*` `/` `%` `|` `&` `^` `!`, ainsi que le moins unaire. La priorité des opérateurs arithmétiques est respectée : les opérateurs multiplicatifs avant les opérateurs additifs, et ceux ayant la même priorité sont évalués dans l'ordre. Les parenthèses permettent de préciser la priorité des opérations.

```c
int a = (2 + (13 % 10)) * -6 / 2 + (1+(+1(1+1)))
int b = 8 & 1  //
```

### Opérateurs d'incrémentation

Comme avec GCC, le compilateur IFCC est capable de reconnaitre les opérateurs d'incrémentation `++` et `--`. S'ils sont placés devant une variable, alors la variable sera respectivement incrémentée ou décrémentée de 1 **avant** d'avoir sa valeur retournée. Dans le cas où ils sont placés après la variable, alors sa valeur sera incrémentée ou décrémentée de 1 **après** avoir sa valeur retournée.

```c
int a = 0;
int b = a++;  // ici, b = 0, c'est-à-dire la valeur de a AVANT incrémentation, puis a = 1
int c = ++a;  // ici, c = 2, c'est-à-dire la valeur de a APRES incrémentation, puis a = 2
```

### Opérateurs de comparaison

Il est possible de réaliser des comparaisons entre deux entiers (constantes ou variables) grâce aux opérateurs de comparaison `==` `!=` `<` `>` `<=` `>=`. Similairement à GCC, la valeur retournée sera 1 si la comparaison est vraie, et 0 sinon.

```c
int a = 0;
int b = a < 4;  // ici, b = 1, comme 0 est bien inférieur à 4
int c = a == 1; // ici, c = 0, comme 0 n'est pas égal à 1
```

### Structures conditionnelles

Le compilateur IFCC supporte les structures conditionnelles de C `if`, `while` et `switch?`.

#### if

La structure `if(condition){ }` permet d'exécuter des instructions entre acolades si la valeur donnée en entrée est différente de 0.

```c
int a = 0;
if(42){
    a = 6;
}

// a = 6 à la fin
```

Il est aussi possible de d'indiquer des instructions à exécuter dans le cas où la condition est égale à 0 avec
`else`.

```c
int a = 0;
if (a > 5){
    a = 3;
} else {
    a = 42;
}

// ici a = 42
```

#### while

La boucle `while(condition){ }` fonctionne de manière similaire à un `if`. Les instructions à l'intérieur des acolades sont exécutées tant que la condition est différente de 0.

```c
int a = 0;
while (a < 5){
    a++;
}

// ici a = 5
```

#### switch

### Opérateurs logiques non paresseux

Il est possible de combiner deux valeurs ensembles pour pouvoir réaliser des conditions plus complexes avec les opérateurs `&&` et `||`.

Contrairement à GCC, les opérateurs `&&` et `||` ne sont pas paresseux avec IFCC. Cela signifie que les deux expressions seront exécutées dans tous les cas.

#### ET &&
`a && b` retournera 1 si et seulement si `a` et `b` sont différents de 0. Dans tous les autres cas, 0 sera retourné.

```c
int a = 0;
if (a > 5 && a < 5){
    a = 3;
} 

int b = 0;
if (b == 0 && b < 8) {
    b = 5;
}

// ici a = 0 et b = 5
```


#### OU ||
`a || b` retournera 1 si au moins `a` ou `b` est différent de 0. Dans le cas où a et b sont égaux à 0, 0 sera retourné.

```c
int a = 0;
if (a > 5 || a < 5){
    a = 3;
} 

int b = 0;
if (b == 0 || b < 8) {
    b = 5;
}

// ici a = 3 et b = 5
```

- Commentaires `/* */`
- Variables (sans les scopes)
- Constantes entières et caractères
- Tableaux 1D
- Expressions avec les opérateurs `+` `-` `*` `/` `%` `|` `&` `^` `!`
- Opérateurs d'incrémentation `i++` `i--` `++i` `--i`
- Comparaisons avec `==` `!=` `<` `>` `<=` `>=`
- Déclaration et affectation de variables
- Vérification de la déclaration d'une variable avant son utilisation
- Vérification de l'utilisation d'une variable déclarée
- Structures conditionnelles `if`, `else`
- Boucles `while`, avec `continue` et `break`
- Opérateurs logiques NON pareseux `&&` `||`
- `getchar` et `putchar`
- Fonctions (version bêta/incomplète/potentiellement buggée)
- Bonus (inutile, sauf pour nous, ça nous a fait gagner beaucoup de temps) : tests parallélisés

## Architecture

Nous avons implémenté une **IR**. L'`ASTVisitor`, qui hérite du `BaseVisitor` généré par Antlr, visite l'AST et construit l'IR. Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein du *control flow graph* `CFG`. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Pour découpler l'IR de la génération d'assembleur et donc de l'architecture, nous avons mis en place un deuxième visiteur, `IRVisitor`. Son implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction du CFG et génère le code assembleur. On peut ansi rajouter un backend pour chaque architecture en écrivant le visiteur associé, sans toucher à l'IR.

Pour implémenter l'optimisation, il existe au moins 2 grandes architecture possibles symbolisés par une * dans le schéma suivant : 
AST * visité par (ASTVisitor) -> CFG * visité par (x86Visitor)  -> code type assembleur 
Nous avons privilégié la seconde option étant donné sa facilitation relative d'implémentation. 
On retrouvera ainsi dans `CFGOptimizer` un programme qui itére sur les instructions d'un CFG donné, identifie celles optimisables, supprime les anciennes et remplace par les nouvelles. Le résultat constitue un nouveau CFG, exploré à son tour par '`x86Visitor`'. L'optimiseur proposé rammène toute déclaration combinaison de constantes et d'opérateurs classiques (+, -, *, /, %, -, &, |, ^) à la simple déclaration de la constante qui en résulte et supprime les élements neutres des expressions variables. 

## Gestion de projet

Nous sommes partis sur une base de code commune à l'hexanome au cours la 3ème séance, en utilisant la plus avancée. Nous avons en même temps fait la transition vers l'IR. La séance d'après, nous avons pu travailler efficacement en parallèle avec un workflow centré autour de GitLab : des issues pour lister les tâches à faire, développées sur des branches de features, qu'on merge sur la branche main après avoir eu une revue de code. Les refactors importants (qui ne peuvent pas se faire en parallèle) comme le visiteur d'IR, se font hors séance. Nous prévoyons de continuer avec cette méthode de gestion.
