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
    : CONST # constExpr 
    | SIGN CONST # signConstExpr
    | VAR  # varExpr
    | SIGN VAR # signVarExpr
    | expr MULT_DIV expr # mult_div
    | expr ADD_SUB expr # add_sub
    | '(' expr ')' # par
    ;

return_stmt: RETURN expr ';' ;

RETURN : 'return' ;
CONST : [0-9]+ ;
INT : 'int' ;
VAR : [a-zA-Z][a-zA-Z0-9]* ;

SIGN
    : '+'
    | '-'
    ;

ADD_SUB
    : '+' 
    | '-' 
    ;

MULT_DIV
    : '*' 
    | '/' 
    ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
