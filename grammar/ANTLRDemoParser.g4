parser grammar ANTLRDemoParser;

options {
    tokenVocab = ANTLRDemoLexer;
}

program: line* EOF;
line: expr NEWL;

expr
    : expr (MUL | DIV) expr    # MulDiv
    | expr (ADD | SUB) expr    # AddSub
    | LPAR expr RPAR           # Paren
    | NUM                      # Number
    ;
