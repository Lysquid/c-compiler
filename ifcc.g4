grammar ifcc;

axiom : prog EOF ;

prog : (function)+ ;

function : return_type VAR '(' parameters ')' block ;

block : '{' statement* '}' ;

parameters : (INT VAR (',' INT VAR)*)? ;

statement
    : RETURN expr ';' # ret
    | INT VAR (',' VAR)* ';'    # declaration
    | INT VAR '=' expr ';'      # declarationAssignment
    | expr ';'                  # expression
    | 'if' '(' expr ')'  block  ('else'  block )? # ifcond
    | VAR '(' (expr (',' expr)*)? ')' ';' # callVoidFunction
    | 'putchar(' expr ')' ';'   # putchar
    ;

expr
    : ADD_SUB expr      # sign
    | UNARY_OP expr     # unary
    | expr MUL_DIV expr # mulDiv
    | expr ADD_SUB expr # addSub
    | expr BIT_AND expr # bitAnd
    | expr BIT_XOR expr # bitXor
    | expr BIT_OR expr  # bitOr
    | expr COMP expr    # comparison
    | VAR '(' (expr (',' expr)*)? ')' # callIntFunction
    | VAR '=' expr      # assignment
    | 'getchar()'       # getchar
    | CONST             # const
    | CARAC             # carac
    | VAR               # var
    | '(' expr ')'      # par
    ;

ADD_SUB : '+' | '-' ;
MUL_DIV : '*' | '/' | '%';
UNARY_OP : '!' ;
COMP : '==' | '<=' | '>=' | '<' | '>' | '!=';
BIT_AND : '&' ;
BIT_OR : '|' ;
BIT_XOR : '^' ;

RETURN : 'return' ;
CONST : [0-9]+ ;
CARAC : '\'' . '\'' ;
INT : 'int' ;
VOID : 'void' ;

return_type : INT|VOID;

VAR : [_a-zA-Z][_a-zA-Z0-9]* ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
