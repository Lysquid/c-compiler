grammar ifcc;

axiom : prog EOF ;

prog : INT 'main' '(' ')' '{' statements return_stmt '}' ;

statements : statement* ;

statement 
    : INT VAR (',' VAR)* ';' #declarationStatement
    | INT VAR '=' expr ';' #definitionStatement 
    | VAR '=' expr ';' #assignementStatement
    ;

expr
    : ADD_SUB expr # signExpr
    | UNARY_OP expr # unaryExpr
    | expr MULT_DIV expr # mult_div
    | expr ADD_SUB expr # add_sub
    | CONST # constExpr
    | VAR  # varExpr
    | '(' expr ')' # par
    ;

return_stmt: RETURN expr ';' ;


RETURN : 'return' ;
CONST : [0-9]+ ;
INT : 'int' ;
VAR : [a-zA-Z][a-zA-Z0-9]* ;

ADD_SUB
    : '+'
    | '-'
    ;

MULT_DIV
    : '*'
    | '/'
    ;

UNARY_OP
    : '!'
    ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
