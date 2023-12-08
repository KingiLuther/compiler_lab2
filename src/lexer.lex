%{
#include <stdio.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"
extern int line, col;
%}

digits [1-9][0-9]*|0
id [a-zA-Z_][a-zA-Z0-9_]*
%s COMMENT1
%s COMMENT2

%%
<INITIAL>"+" { yylval.pos = A_Pos(line,col);col += 1;return ADD; }
<INITIAL>"-" { yylval.pos = A_Pos(line,col);col += 1;return SUB; }
<INITIAL>"*" { yylval.pos = A_Pos(line,col);col += 1;return MUL; }
<INITIAL>"/" { yylval.pos = A_Pos(line,col);col += 1;return DIV; }
<INITIAL>"&&" { yylval.pos = A_Pos(line,col);col += 2;return AND; }
<INITIAL>"||" { yylval.pos = A_Pos(line,col);col += 2;return OR; }
<INITIAL>"!" { yylval.pos = A_Pos(line,col);col += 1;return NOT; }
<INITIAL>">" { yylval.pos = A_Pos(line,col);col += 1;return GT; }
<INITIAL>"<" { yylval.pos = A_Pos(line,col);col += 1;return LT; }
<INITIAL>">=" { yylval.pos = A_Pos(line,col);col += 2;return GE; }
<INITIAL>"<=" { yylval.pos = A_Pos(line,col);col += 2;return LE; }
<INITIAL>"==" { yylval.pos = A_Pos(line,col);col += 2;return EQ; }
<INITIAL>"!=" { yylval.pos = A_Pos(line,col);col += 2;return NE; }
<INITIAL>"=" { yylval.pos = A_Pos(line,col);col += 1;return ASSIGN; }
<INITIAL>"," { yylval.pos = A_Pos(line,col);col += 1;return COMMA; }
<INITIAL>";" { yylval.pos = A_Pos(line,col);col += 1;return SEMICOLON; }
<INITIAL>":" { yylval.pos = A_Pos(line,col);col += 1;return COLON; }
<INITIAL>"->" { yylval.pos = A_Pos(line,col);col += 2;return RVAL; }
\t { col += 4; }
\r { col = 0; }
<INITIAL>\n { line += 1; col = 1; }
<COMMENT2>\n { line += 1; col = 1; }
<COMMENT1>\n { line += 1; col = 1; BEGIN INITIAL; }
" " { col += 1;}
<INITIAL>"(" { yylval.pos = A_Pos(line,col);col += 1;return LEFTP; }
<INITIAL>")" { yylval.pos = A_Pos(line,col);col += 1;return RIGHTP; }
<INITIAL>"{" { yylval.pos = A_Pos(line,col);col += 1;return LEFTBRACE; }
<INITIAL>"}" { yylval.pos = A_Pos(line,col);col += 1;return RIGHTBRACE; }
<INITIAL>"[" { yylval.pos = A_Pos(line,col);col += 1;return LEFTBRACKET; }
<INITIAL>"]" { yylval.pos = A_Pos(line,col);col += 1;return RIGHTBRACKET; }
<INITIAL>"//" { col += 2;BEGIN COMMENT1; }
<INITIAL>"/*" { col += 2;BEGIN COMMENT2; }
<COMMENT2>"*/" { col += 2;BEGIN INITIAL; }
<COMMENT1>. { col += 1; }
<COMMENT2>. { col += 1; }
<INITIAL>[\.] { yylval.pos = A_Pos(line,col);col += 1;return MEM; }
<INITIAL>"let" { yylval.pos = A_Pos(line,col);col += 3;return LET; }
<INITIAL>"if" { yylval.pos = A_Pos(line,col);col += 2;return IF; }
<INITIAL>"else" { yylval.pos = A_Pos(line,col);col += 4;return ELSE; }
<INITIAL>"while" { yylval.pos = A_Pos(line,col);col += 5;return WHILE; }
<INITIAL>"int" { yylval.pos = A_Pos(line,col);col += 3;return INT; }
<INITIAL>"fn" { yylval.pos = A_Pos(line,col);col += 2;return FN; }
<INITIAL>"ret" { yylval.pos = A_Pos(line,col);col += 3;return RETURN; }
<INITIAL>"struct" { yylval.pos = A_Pos(line,col);col += 6;return STRUCT; }
<INITIAL>"break" { yylval.pos = A_Pos(line,col);col += 5;return BREAK; }
<INITIAL>"continue" { yylval.pos = A_Pos(line,col);col += 8;return CONTINUE; }
<INITIAL>{id} {
    char *str = (char*)calloc(strlen(yytext)+1, sizeof(char));
    strcpy(str, yytext);
    yylval.tokenId = A_TokenId(A_Pos(line,col), str);
    col += strlen(yytext);
    return ID;
}
<INITIAL>{digits} { yylval.tokenNum = A_TokenNum(A_Pos(line,col),atoi(yytext));col += strlen(yytext);return NUMBER;}
%%