grammar ifcc;

axiom : prog EOF ;

prog : (function)+ ;

function : return_type VAR '(' parameters ')' block ;

return_type : INT|VOID;

parameters : (INT VAR (',' INT VAR)*)? ;

block : '{' statement* '}' ;

statement
    : RETURN expr ';'                               # ret
    | INT VAR (',' VAR)* ';'                        # declaration
    | INT VAR '=' expr ';'                          # declarationAssignment
    | VAR '(' (expr (',' expr)*)? ')' ';'           # callVoidFunction
    | expr ';'                                      # expression
    | 'putchar(' expr ')' ';'                       # putchar
    | condblock                                     # condstatement
    | 'while' '(' expr ')' block                    # while
    ;

condblock
    : 'if' '(' expr ')' block elseblock?
    ;

elseblock
    : 'else' condblock # elseifblock
    | 'else' block # simpleelse
    ;

expr
    : ADD_SUB expr                      # sign
    | UNARY_OP expr                     # unary
    | increment                         # incr
    | expr MUL_DIV expr                 # mulDiv
    | expr ADD_SUB expr                 # addSub
    | expr BIT_AND expr                 # bitAnd
    | expr BIT_XOR expr                 # bitXor
    | expr BIT_OR expr                  # bitOr
    | expr COMP expr                    # comparison
    | VAR '(' (expr (',' expr)*)? ')'   # callIntFunction
    | VAR '=' expr                      # assignment
    | 'getchar()'                       # getchar
    | CONST                             # const
    | CHAR                              # char
    | VAR                               # var
    | '(' expr ')'                      # par
    ;

increment
    : VAR INCREMENT                     # incrementafter
    | INCREMENT VAR                     # incrementbefore
    ;

ADD_SUB : '+' | '-' ;
MUL_DIV : '*' | '/' | '%';
INCREMENT : '++' | '--';
UNARY_OP : '!' ;
COMP : '==' | '<=' | '>=' | '<' | '>' | '!=';
BIT_AND : '&' ;
BIT_OR : '|' ;
BIT_XOR : '^' ;

RETURN : 'return' ;
INT : 'int' ;
VOID : 'void' ;

CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;
VAR : [_a-zA-Z][_a-zA-Z0-9]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
