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

### Antlr4

Installez Antlr4, avec le gestionnaire de système, ou en exécutant le script `./install-antlr.sh`

Dans le repertoire `makefile`, faites une copie du makefile pour votre platforme, et appelez le `config.mk`. Si vous avec utilisez le script d'installation, cette étape n'est pas nécessaire.

### Utilisation

Compilez le projet : `make -j` (le flag permet de compiler en parallèle)

Vous pouvez maintenant compiler un programme de notre sous ensemble du C vers x86 avec `./ifcc program.c`

### Tests

Compilez et exécutez les tests :
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

---

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

Seul le type `int` est supporté. Le type `char` fonctionne, et est traité comme un `int`.

#### Déclaration et affectation

Les déclarations de variables sont les mêmes qu'en C : on peut en déclarer plusieures.

Il est possible d'affecter une valeur constante ou bien la valeur d'une autre variable à une variable. L'affection renvoyant la valeur affectée, on peut les enchaîner.

```c
int a;
int b = 2;
a = b;
int x=1, y, z=3;
int x = y = z = 2;
```

Comme pour avec GCC, redéclarer une variable, utiliser une variable non déclarée ou avant sa déclaration lève une erreur.

Les variables déclarées et non utilisées affichent un warning.

#### Caractères

Un unique caractère peut être utilisé pour assigner une variable (la valeur ASCII corespondante est stockée).

```c
int c1 = 'a';   // 97
char c2 = 'b';  // 98
```

Les caractères spéciaux tels que `\n` ne fonctionnent pas.

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

Les opérateurs `+=` `-=` `*=` `/=` sont supportés en plus de l'assignation classique.

#### Opérateurs de comparaison

Il est possible de réaliser des comparaisons entre deux entiers (constantes ou variables) grâce aux opérateurs de comparaison `==` `!=` `<` `>` `<=` `>=`. La valeur retournée sera 1 si la comparaison est vraie, et 0 sinon. En C, ces opérateurs ont des priorités bien spécifiques, qui ne sont pas respectées ici : elles sont évaluées de gauche à droite.

```c
int a = 0;
int b = a < 4;  // ici, b = 1, comme 0 est bien inférieur à 4
int c = a == 1; // ici, c = 0, comme 0 n'est pas égal à 1
```

### Blocs avec portée

Les accolades définissent un bloc. Cela crée une portée : on peut alors accéder à la variable déclarée à l'intérieur et l’extérieur, y compris en cas de blocs imbriqués, mais on ne peut plus utiliser les variables définies à l'intérieur du bloc après en être sorti.

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

Une variable redéfinie dans un bloc a la priorité devant celle définie dans les blocs parents, et ne les écrase pas.

```c
int a = 1;
{
    int a = 2;
    a == 2  // vrai
}
a == 1  // vrai
```

Ces blocs fonctionnent de la même manière dans les structures suivantes.

### Structures conditionnelles

Le compilateur IFCC supporte les structures conditionnelles de C `if`, `while` et `switch?`.

#### if

La structure `if (condition)` permet d'exécuter une instruction ou un bloc d'instructions si la valeur donnée en entrée est différente de 0.

```c
int a = 0;
if (42) {
    a = 6;
}
// a = 6 à la fin
```

Il est aussi possible de d'indiquer des instructions à exécuter dans le cas où la condition est égale à 0 avec
`else`. À noter que les blocs ne sont pas nécessaires s'il n'y a qu'une seule ligne dans chaque branche.

```c
int a = 0;
if (a > 5)
    a = 3;
else
    a = 42;
// ici a = 42
```

#### while

La boucle `while (condition)` fonctionne de manière similaire à un `if`. L'instruction ou le bloc d'instructions à la suite sont exécutés tant que la condition est différente de 0.

```c
int a = 0;
while (a < 5) {
    a++;
}
// ici a = 5
```

#### break et continue

Les instruction `break` et `continue` sont comme dans le language C. Elles doivent seulement être mises dans le boucle `while`.
L'instruction `break` permet de terminer prématurément l'exécution de la boucle `while` et de sortir de celle-ci. Par exemple:

```c
int i = 0;
    
while (i < 10) {
    // Si i atteint 5, sortir de la boucle
    if (i == 5) {
        break;
    } 
    i++;
}
// ici i = 5
```

L'instruction `continue` permet de passer à l'itération suivante de la boucle `while` sans exécuter le reste du code à l'intérieur de la boucle pour l'itération actuelle. Par exemple: 

```c
int i = 0;
int j = 0;
while (i < 5) {
    i++;
    // Si i est pair, passer à l'itération suivante
    if (i % 2 == 0) {
        continue;
    }
    j++;
}
// ici j = 3 parce qu'il y a 3 nombres impairs de 1 à 5.
```

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

Le compilateur supporte la définition et l'utilisation des fonctions, qui retourne seulement une variable de type int/char/void.

#### Définition de fonctions

La définition des fonctions est comme dans le language C. Par exemple:

```c
int func1(int a, int b){
    return a+b;
}
```

Le return peut être mis n'importe où. Pour une fonction qui retourne int/char, il faut définir au moins un return dans le bloc principal de cette fonction.

Pour une fonction qui retourne void, return sans expression ou pas de return sont tous valides. Par exemple:

```c
void func2(int a, int b){
    return; // cette instruction return peut être supprimée.
}
```

Dans notre compilateur, le return avec une expression dans une fonction void n'est pas valide, mais dans le compilateur GCC c'est valide. 

```c
void func3(int a, int b){
    return a; // Dans GCC c'est valide, et un warning est généré, mais dans notre compilateur nous le considère comme une erreur.
}
```

#### Appel de fonctions

L'appel de fonctions doivent être mis après la définition de cette fonction. Dans le compilateur, on le considère comme une expression.

Par exemple:

```c
int b = 3;
int a = func1(b, 5);
// ici a = 3+5 = 8
func2(a, b); // fonction void
```

Notez qu'une variable ne peut pas être affectée à un appel de fonction qui retourne de type void.

Le nombre des paramètres dans l'appel doit correspondre au nombre des paramètres de la fonction définie.

#### Fonctions d'entrée/sortie

Dans notre compilateur, nous avons prédéfini 2 fonctions d'entrée sortie: putchar et getchar. L'utilisateur peut directement l'utiliser.

```c
int a = getchar();
// L'utilisateur peut saisir un caractère, et la variable a va être affectée au code ascii de ce caractère. 
// Par exemple si on saisi le caractère 'a', alors a = 97.

putchar(a+1);
// Le programme affiche le caractère dont le code ascii est égale à la valeur de a+1.
// Pour l'exemple au dessus, ici on affiche 'b'.
```

Notez que l'utilisateur ne peut pas redéfinir une fonction appelée putchar ou getchar.

---

## Manuel programmeur

Antlr nous fourni l'AST, que nous visitons pour générer une **IR**, qui est elle même visitée pour générer le code assembleur.

### Visiteurs de l'AST

L'AST est actuellement visitée par 2 visiteurs, héritant de la classe `BaseVisitor` générée par Antlr. Nous les avons séparés pour rendre le code plus clair, étant donné que leurs fonctions sont relativement indépendantes.

#### Visiteur de type checking

Le premier est le `TypeCheckVisitor`, qui vérifie que les types (définis dans `Types.h`) sont bien utilisés de façon cohérente. Voilà un exemple typique d'erreur à détecter :

```c
void f() {}

int main() {
    int a = f();    // retour void assigné à un int
}
```

Ce visiteur ne tient pas compte des blocs, il peut donc par exemple lever une erreur de type pour une variable indéfinie dans un scope. Ce visiteur aurait été réellement utile si nous avions implémenté d'autres types, ce qui n'a pas été le cas. Nous n'avons pas eu le temps d'implémenter le check des tableaux.

#### Visiteur de génération de l'IR

Le code de génération de l'IR se trouve dans `ASTVisitor`. Le plus gros du code du compilateur se trouve dans ce visiteur, qui mériterait d'être décomposé.

### IR

Comme dans le template fourni, l'IR est composée d'instructions `Instr`, regroupées en `BasicBlock` au sein de *control flow graph* `CFG` pour chaque fonction. La différence est que chaque instruction est une classe héritant de `Instr`, avec ses attributs spécifiques.

Chaque Basic Block contient un pointeur vers son `Scope`. C'est dans cet objet qu'est contenu la table des symboles, avec les méthodes permettant de manipuler les variables. Un scope contient un pointeur vers son scope parent : on a donc un arbre dans lequel on peut remonter pour *resolve* une variable.

### Génération de l'assembleur

Nous avons implémenté un design pattern visiteur pour parcourir l'IR, la classe `IRVisitor` dans sa version abstraite. Le but est de découpler l'IR de la génération de code, et de donner une interface standard pour cette génération.

L'implémentation concrète pour l'architecture x86, `x86Visitor`, visite chaque instruction des CFG et génère le code assembleur. On peut ainsi facilement rajouter un backend pour chaque architecture en écrivant le visiteur associé.

### Optimisation : propagation des constantes

Les expressions arithmétiques contenant exclusivement des constantes ont été optimisées et sont remplacées directement par leur résultat lors de la génération du code assembleur.

```c
int a = 0;
a = 1 + 2 * 3;
```

Ici, l'expression arithmétique `1 + 2 * 3` sera remplacée par la constante `9` dans le code assembleur. De manière plus précise, les instructions `addl` et `imull` sont remplacées par une seule instruction `movl`.

Les éléments neutres des opérateurs `+` `-` `*` sont supprimés lors de la génération du code assembleur.

```c
int a = 0;
int b = 0 + a * 1:
```

Ici, l'expression arithmétique `0 + a * 1` sera remplacée par la valeur de la variable `a` dans le code assembleur. De manière plus précise, les instructions `addl` et `imull` sont remplacées par des instructions `movl`.

Pour implémenter cette optimisation, il existe au moins 2 grandes architectures possibles symbolisées par une * dans le schéma suivant :

AST * visité par (ASTVisitor) -> CFG * visité par (x86Visitor)  -> code type assembleur

Nous avons privilégié la seconde option étant donné sa relative facilité d'implémentation.

On retrouvera ainsi dans `CFGOptimizer` un programme qui itére sur les instructions d'un CFG donné, identifie celles optimisables, supprime les anciennes et remplace par les nouvelles. Le résultat constitue un nouveau CFG, exploré à son tour par `x86Visitor`. L'optimiseur proposé ramène toute déclaration combinaison de constantes et d'opérateurs classiques (`+` `-` `*` `/` `%` `-` `&` `|` `^`) à la simple déclaration de la constante qui en résulte et supprime les elements neutres des expressions variables.

### Tests

Le framework de tests a été modifié pour exécuter les tests en parallèle. Bien que cela permettait initialement de diviser le temps d’exécution par deux, la différence n'est plus très grande avec notre jeu de tests actuel.

---

## Gestion de projet

Nous sommes partis sur une base de code commune à l'hexanome au cours la 3ème séance, partant de la version plus avancée. Nous avons en même temps fait la transition vers l'IR, ce qui n'a pas forcément été simple.

Les séances suivantes, nous avons pu travailler efficacement en parallèle avec un workflow centré autour de GitLab : des issues pour lister les tâches à faire, développées sur des branches de features, que l'on merge ensuite sur la branche main après avoir eu une revue de code.

Les refactors importants (qui ne peuvent pas se faire en parallèle), comme le visiteur d'IR, se font hors séance. Certaines features complexes telles que l'optimisation et les tableaux ont été codées en peer coding pour limiter les erreurs.

Les tests ont été écrits pour la plupart au fur et à mesure de l'implémentation des fonctionnalités. Vers la fin, certains membres du groupe ont essayé de mettre à l'épreuve nos implémentations avec des tests en boite noire, ce qui nous a permis de trouver et corriger de nombreux bugs.
