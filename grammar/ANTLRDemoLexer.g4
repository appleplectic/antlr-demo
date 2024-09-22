lexer grammar ANTLRDemoLexer;

ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';
LPAR: '(';
RPAR: ')';
NEWL: '\r'? '\n';
NUM : [0-9]+ ('.' [0-9]+)?;

WS  : [ \t]+ -> skip;