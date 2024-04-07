grammar ifcc;

axiom : prog EOF ;

prog : function+ ;

function : return_type VAR '(' parameters ')' '{' statement* '}' ;

return_type : TYPE | VOID ;

parameters : (TYPE VAR (',' TYPE VAR)*)? ;

statement
    : 'return' expr? ';'                                # ret
    | TYPE declareAssign (',' declareAssign)* ';'       # declaration
    | TYPE ( arrayDecl (',' arrayDecl)* ) ';'           # arrayDeclaration
    | '{' statement* '}'                                # block
    | 'if' '(' expr ')' if_block=statement ('else' else_block=statement)?   # if
    | 'while' '(' expr ')' body=statement               # while
    | 'break' ';'                                       # break
    | 'continue' ';'                                    # continue
    | expr ';'                                          # expression
    ;

declareAssign : VAR ('=' expr)? ;

arrayDecl : VAR '[' CONST ']' ('=' '{' expr (',' expr)* '}')?;

expr
    : ADD_SUB expr                      # sign
    | UNARY_OP expr                     # unary
    | increment                         # incr
    | increment                         # incr
    | expr MUL_DIV expr                 # mulDiv
    | expr ADD_SUB expr                 # addSub
    | expr BIT_AND expr                 # bitAnd
    | expr BIT_XOR expr                 # bitXor
    | expr BIT_OR expr                  # bitOr
    | expr COMP expr                    # comparison
    | expr LOGIC expr                   # logicop
    | VAR '(' (expr (',' expr)*)? ')'   # callIntFunction
    | CONST                             # const
    | CHAR                              # char
    | VAR                               # var
    | VAR assignmentop=('=' | '+=' | '-=' | '*=' | '/=') expr             # assignment
    | VAR '[' CONST ']'  assignmentop=('=' | '+=' | '-=' | '*=' | '/=') expr             # arrayAssignment
    | '(' expr ')'                      # par
    | VAR '['CONST']'                   # arrayAccess
    ;

increment
    : VAR INCREMENT                     # incrementafter
    | INCREMENT VAR                     # incrementbefore
    ;

ADD_SUB : '+' | '-' ;
MUL_DIV : '*' | '/' | '%' ;
INCREMENT : '++' | '--' ;
UNARY_OP : '!' ;
LOGIC : '||' | '&&' ;
COMP : '==' | '<=' | '>=' | '<' | '>' | '!=';
BIT_AND : '&' ;
BIT_OR : '|' ;
BIT_XOR : '^' ;

TYPE : 'int' | 'char';
VOID : 'void' ;

CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;
VAR : [_a-zA-Z][_a-zA-Z0-9]* ;
COMMENT : '/*' .*? '*/' -> skip ;
COMMENT2 : '//' .*? ('\n' | EOF) -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
