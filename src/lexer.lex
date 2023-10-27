%{
#include <stdio.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"
extern int line, col;
%}

// TODO:
// your lexer
"+"             { return ADD; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"<"             { return LT; }
"<="            { return LE; }
">"             { return GT; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }
":"             { return COLON; }
"->"            { return RIGHTARR; }
"="             { return ASSIGN; }
"."             { return DOT; }
"("             { return LPAR; }
")"             { return RPAR; }
"["             { return LSQR; }
"]"             { return RSQR; }
"{"             { return LBRA; }
"}"             { return RBRA; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"while"         { return WHILE; }
"if"            { return IF; }
"else"          { return ELSE; }
"ret"           { return RET; }
"fn"            { return FN; }
"struct"        { return STRUCT; }
"let"           { return LET; }
"int"           { return INT; }
";"             { return SEMICOLON; }
[1-9][0-9]*     { yylval.pos = A_newPos(line, col); return NUM; }
[a-zA-Z][a-zA-Z0-9]* { yylval.pos = A_newPos(line, col); yylval.str = strdup(yytext); return ID; }
[ \t\n]+        { /* Skip whitespace and newlines */ }
.               { /* Handle unrecognized characters */ }

%%

int main(int argc, char* argv[]) {
    // Initialization code
    // ...
    yyparse();
    // Clean-up code
    // ...
    return 0;
}