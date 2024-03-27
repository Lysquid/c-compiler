grammar ifcc;

axiom : prog EOF ;

prog : function+ ;

function : return_type VAR '(' parameters ')' '{' statement* '}' ;

return_type : TYPE | VOID ;

parameters : (TYPE VAR (',' TYPE VAR)*)? ;

statement
    : 'return' expr? ';'                                # ret
    | TYPE declareAssign (',' declareAssign)* ';'       # declaration
    | '{' statement* '}'                                # block
    | 'if' '(' expr ')' if_block=statement ('else' else_block=statement)?   # if
    | 'while' '(' expr ')' body=statement               # while
    | 'break' ';'                                       # break
    | 'continue' ';'                                    # continue
    | expr ';'                                          # expression
    ;

declareAssign : VAR ('=' expr)? ;

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
    | VAR '(' (expr (',' expr)*)? ')'   # callFunction
    | CONST                             # const
    | CHAR                              # char
    | VAR                               # var
    | VAR assignmentop=('=' | '+=' | '-=' | '*=' | '/=') expr             # assignment
    | '(' expr ')'                      # par
    ;

increment
    : VAR INCREMENT                     # incrementafter
    | INCREMENT VAR                     # incrementbefore
    ;

ADD_SUB : '+' | '-' ;
MUL_DIV : '*' | '/' | '%' ;
INCREMENT : '++' | '--' ;
UNARY_OP : '!' ;
COMP : '==' | '<=' | '>=' | '<' | '>' | '!=' ;
BIT_AND : '&' ;
BIT_OR : '|' ;
BIT_XOR : '^' ;

TYPE : 'int' | 'char';
VOID : 'void' ;

CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;
VAR : [_a-zA-Z][_a-zA-Z0-9]* ;
COMMENT : '/*' .*? '*/' -> skip ;
COMMENT2 : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
