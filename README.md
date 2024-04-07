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

Seuls le type `int` est supporté. Le type `char` fonctionne, et est traité comme un `int`.

#### Déclaration et affectation

Les déclarations de variable sont les même qu'en C : on peut déclarer plusieurs .

Il est possible d'affecter une valeur constante ou bien la valeur d'une autre variable à une variable. L'affection renvoyant la valeur affecté, on peut les enchaîner.

```c
int a;
int b = 2;
a = b;
int x=1, y, z=3;
int x = y = z = 2;
```

Comme pour avec GCC, redéclarer une variable, utiliser une variable non déclarée ou avant sa déclaration lève une erreur.

Les variables déclarées et non utilisés affichent un warning.

#### Caractères

Un unique caractère entre peut être utilisé pour assigner une variable (la valeur ASCII corespondante est stockée).

```c
int c1 = 'a';   // 97
char c2 = 'b';  // 98
```

Les caractère spéciaux tels que `\n` ne fonctionnent pas.

### Tableaux

Le compilateur ifcc permet de manipuler des tableaux 1D de manière restreinte.

Seules les constantes sont supportées lors de la déclaration d'un tableau et lors de l'accès à un élément d'un tableau. Autrement dit, seul `tab[CONST]` est accepté.

L'affectation d'un tableau à un autre tableau `t1 = t2` n'est pas supportée.

```c
int x = 0;
int t1[2]; //déclaration d'un tableau
int t2[2] = {1,2}; //déclaration et initialisation d'un tableau

x = t2[0]; //accès à un élément du tableau
t1[0] = 2; //affectation d'une valeur à un élément du tableau 
```

### Expressions

#### Expressions arithmétiques

Les opérateurs arithmétiques `+` `-` `*` `/` `%` et bit à bit `|` `&` `^` ainsi que les opérateurs unaires `!` et `-` sont supportés.

La priorité des opérateurs arithmétiques est respectée : les opérateurs multiplicatifs avant les opérateurs additifs, et ceux ayant la même priorité sont évalués dans l'ordre. Les parenthèses permettent de préciser la priorité des opérations.

```c
int a = (2 + (13 % 10)) * -6 / 2 + (1+(+1(1+1)))
int b = 8 & 1  //
```

#### Opérateurs d'incrémentation

IFCC reconnaît les opérateurs d'incrémentation `++` et `--`. S'ils sont placés devant une variable, alors la variable sera respectivement incrémentée ou décrémentée de 1 **avant** d'avoir sa valeur retournée. Dans le cas où ils sont placés après la variable, alors sa valeur sera incrémentée ou décrémentée de 1 **après** avoir sa valeur retournée.

```c
int a = 0;
int b = a++;  // ici, b = 0, c'est-à-dire la valeur de a AVANT incrémentation, puis a = 1
int c = ++a;  // ici, c = 2, c'est-à-dire la valeur de a APRES incrémentation, puis a = 2
```

#### Opérateurs d'affections

Les opérateurs `+=` `-=` `*=` `/=` sont supportés en plus de l'assignation classiques.

#### Opérateurs de comparaison

Il est possible de réaliser des comparaisons entre deux entiers (constantes ou variables) grâce aux opérateurs de comparaison `==` `!=` `<` `>` `<=` `>=`. La valeur retournée sera 1 si la comparaison est vraie, et 0 sinon. En C, ces opérateurs ont des priorités bien spécifiques, qui ne sont pas respectées ici : elles sont évaluées de gauche à droite.

```c
int a = 0;
int b = a < 4;  // ici, b = 1, comme 0 est bien inférieur à 4
int c = a == 1; // ici, c = 0, comme 0 n'est pas égal à 1
```

### Blocs avec portée

Les accolades définissent un bloc. Cela crée porté : on peut alors accéder au variable déclarée à l'intérieur et l’extérieur, y compris en cas de blocs imbriqués, mais on ne peut plus utiliser les variables définient à l'intérieur du bloc après en être sorti.

```c
int a = 1;
{
    a = 2;
    {
        c = b;
    }
    int b = 1;
}
a == 2;  // vrai
a = b;   // erreur: b est indéfini dans ce scope
```

#### Shadowing

Une variable redéfinie dans un bloc à la priorité devant celle définie dans les blocs parents, et ne les écrase pas.

```c
int a = 1;
{
    int a = 2;
    a == 2  // vrai
}
a == 1  // vrai
```

Ces bloc fonctionnent de la même manière dans les structures suivantes.

### Structures conditionnelles

Le compilateur IFCC supporte les structures conditionnelles de C `if`, `while` et `switch?`.

#### if

La structure `if (condition)` permet d'exécuter une instructions ou un bloc d'instructions si la valeur donnée en entrée est différente de 0.

```c
int a = 0;
if (42) {
    a = 6;
}
// a = 6 à la fin
```

Il est aussi possible de d'indiquer des instructions à exécuter dans le cas où la condition est égale à 0 avec
`else`. À noter que les bloc ne sont pas nécessaires s'il n'y a qu'une seule ligne dans chaque branche.

```c
int a = 0;
if (a > 5)
    a = 3;
else
    a = 42;
// ici a = 42
```

#### while

La boucle `while (condition)` fonctionne de manière similaire à un `if`. L'instructions ou le bloc d'instructions à la suite sont exécutées tant que la condition est différente de 0.

```c
int a = 0;
while (a < 5) {
    a++;
}
// ici a = 5
```

#### break et continue

#### switch

### Opérateurs logiques non paresseux

Il est possible de combiner deux conditions avec les opérateurs `&&` et `||`.

Contrairement à GCC, les opérateurs `&&` et `||` ne sont pas paresseux avec IFCC. Cela signifie que les deux expressions seront exécutées dans tous les cas.

#### ET logique

`a && b` retournera 1 si et seulement si `a` et `b` sont différents de 0. Dans tous les autres cas, 0 sera retourné.

```c
int a = 0;
if (a > 5 && a < 5) {
    a = 3;
} 

int b = 0;
if (b == 0 && b < 8) {
    b = 5;
}

// ici a = 0 et b = 5
```

#### OU logique

`a || b` retournera 1 si au moins `a` ou `b` est différent de 0. Dans le cas où a et b sont égaux à 0, 0 sera retourné.

```c
int a = 0;
if (a > 5 || a < 5) {
    a = 3;
} 

int b = 0;
if (b == 0 || b < 8) {
    b = 5;
}

// ici a = 3 et b = 5
```

### Fonctions

TODO: Zeyang

#### Définition de fonctions

(return peut être mis n'importe où)

#### Appel de fonctions

#### Fonctions d'entrées sortie

## Manuel programmeur

Antlr nous fourni l'AST, que nous visitons pour générer une **IR**, qui est elle même visitée pour générer le code assembleur.

### Visiteurs de l'AST

L'AST est actuellement visité par 2 visiteurs, héritant de la classe `BaseVisitor` générée par Antlr. Nous les avons séparez pour rendre le code plus clair, étant donnés que leurs fonctions sont relativement indépendantes.

#### Visiteur de type checking

Le premier est le `TypeCheckVisitor`, qui vérifie que les types  (définis dans `Types.h`) sont biens utilisés de façon cohérente.Voilà un exemple typique d'erreur à détecter :

```c
void f() {}

int main() {
    int a = f();    // retour void assigné à un int
}
```

Ce visiteur ne tient pas compte des blocs, il peut donc par exemple levé une erreur de type pour une variable indéfinie dans un scope. Ce visiteur aurait été réellement utile si nous avions implémenté d'autres type, ce qui n'a pas été le cas. Nous n'avons pas eu le temps d'implémenter le check des tableaux.

#### Visiteur de génération de l'IR

Le code de génération de l'IR se trouve dans `ASTVisitor` (visiteur volumineux qui mériterait d'être décomposé).

### IR

Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein de *control flow graph* `CFG` pour chaque fonction. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Chaque Basic Block contient un pointeur vers son `Scope`. C'est dans cette objet qu'est contenu la table des symboles, avec les méthodes permettant de manipuler les variables. Un scope contient un pointeur vers son scope parent : on a donc un arbre dans lequel on peut remonter pour *resolve* une variable.

### Génération de l'assembleur

Nous avons implémenté un design pattern visiteur pour parcourir l'IR, la classe `IRVisiteur` dans sa version abstraite. Le but est de découpler l'IR de la génération de code, et de donner une interface standard pour cette génération.

L'implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction des CFG et génère le code assembleur. On peut ainsi facilement rajouter un backend pour chaque architecture en écrivant le visiteur associé.

### Optimisation

#### Propagation des constantes

Les expressions arithmétiques contenant exclusivement des constantes ont été optimisées et sont remplacées directement par leur résultat lors de la génération du code assembleur.

```c
int a = 0;
a = 1 + 2 * 3;

// ici, l'expression arithmétique '1 + 2 * 3' sera remplacée par la constante '9' dans le code assembleur
// de manière plus précise, les instructions addl et imull sont remplacées par une seule instruction movl.
```

Les éléments neutres des opérateurs `+` `-` `*` sont supprimés lors de la génération du code assembleur.

```c
int a = 0;
int b = 0 + a * 1:

// ici, l'expression arithmétique '0 + a * 1' sera remplacée par la valeur de la variable 'a' dans le code assembleur
// de manière plus précise, les instructions addl et imull sont remplacées par des instructions movl.
```

Pour implémenter cette optimisation, il existe au moins 2 grandes architecture possibles symbolisés par une * dans le schéma suivant :

AST * visité par (ASTVisitor) -> CFG * visité par (x86Visitor)  -> code type assembleur

Nous avons privilégié la seconde option étant donné sa facilitation relative d'implémentation.

On retrouvera ainsi dans `CFGOptimizer` un programme qui itére sur les instructions d'un CFG donné, identifie celles optimisables, supprime les anciennes et remplace par les nouvelles. Le résultat constitue un nouveau CFG, exploré à son tour par `x86Visitor`. L'optimiseur proposé rammène toute déclaration combinaison de constantes et d'opérateurs classiques (+, -, *, /, %, -, &, |, ^) à la simple déclaration de la constante qui en résulte et supprime les élements neutres des expressions variables.

## Gestion de projet

Nous sommes partis sur une base de code commune à l'hexanome au cours la 3ème séance, en utilisant la plus avancée. Nous avons en même temps fait la transition vers l'IR. La séance d'après, nous avons pu travailler efficacement en parallèle avec un workflow centré autour de GitLab : des issues pour lister les tâches à faire, développées sur des branches de features, qu'on merge sur la branche main après avoir eu une revue de code. Les refactors importants (qui ne peuvent pas se faire en parallèle) comme le visiteur d'IR, se font hors séance. Nous prévoyons de continuer avec cette méthode de gestion.
