grammar ifcc;

axiom : prog EOF ;

prog : INT 'main' '(' ')' '{' statement* ret '}' ;

statement
    : INT VAR (',' VAR)* ';'    # declaration
    | INT VAR '=' expr ';'      # declarationAssignment
    | expr ';' # expression
    ;

ret: RETURN expr ';' ;

expr
    : ADD_SUB expr      # sign
    | UNARY_OP expr     # unary
    | expr MUL_DIV expr # mulDiv
    | expr ADD_SUB expr # addSub
    | expr COMP expr    # comparison
    | VAR '=' expr      # assignment
    | CONST             # const
    | VAR               # var
    | '(' expr ')'      # par
    ;

ADD_SUB : '+' | '-' ;
MUL_DIV : '*' | '/' ;
UNARY_OP : '!' ;
COMP : '==' | '<=' | '>=' | '<' | '>';

RETURN : 'return' ;
CONST : [0-9]+ ;
INT : 'int' ;
VAR : [a-zA-Z][a-zA-Z0-9]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
