%{
#include <stdio.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"

extern int line, col;
%}

%s COMMENT_INLINE
%s COMMENT_MULTILINE

%%

<COMMENT_INLINE>{
\t { col+=4; }
\r\n { line++;col=1;BEGIN INITIAL;}
\n { line++;col=1;BEGIN INITIAL;}
\r { line++;col=1;BEGIN INITIAL;}
. {}
}

<COMMENT_MULTILINE>{
"*/" {  BEGIN INITIAL;  }
\t   { col+=4; }
\r\n      { line++;col=1;}
\n      { line++;col=1;}
\r      { line++;col=1;}
. {}
}

<INITIAL>{
"//" {BEGIN COMMENT_INLINE;}
"/*" {BEGIN COMMENT_MULTILINE;}
"+"	{ col++;yylval.pos=A_Pos(line,col); return ADD; }
"-"	{ col++;yylval.pos=A_Pos(line,col); return SUB; }
"*"	{ col++;yylval.pos=A_Pos(line,col); return MUL; }
"/"	{ col++;yylval.pos=A_Pos(line,col); return DIV; }
"("	{ col++;yylval.pos=A_Pos(line,col); return LPAR; }
")"	{ col++;yylval.pos=A_Pos(line,col); return RPAR; }
"["	{ col++;yylval.pos=A_Pos(line,col); return LSQR; }
"]"	{ col++;yylval.pos=A_Pos(line,col); return RSQR; }
"{"	{ col++;yylval.pos=A_Pos(line,col); return LBRA; }
"}"	{ col++;yylval.pos=A_Pos(line,col); return RBRA; }
";"	{ col++;yylval.pos=A_Pos(line,col); return SEMICOLON; }
":"	{ col++;yylval.pos=A_Pos(line,col); return COLON; }
"."	{ col++;yylval.pos=A_Pos(line,col); return DOT; }
","	{ col++;yylval.pos=A_Pos(line,col); return COMMA; }
"="	{ col++;yylval.pos=A_Pos(line,col); return ASSIGN; }
"<"	{ col++;yylval.pos=A_Pos(line,col); return LT; }
">"	{ col++;yylval.pos=A_Pos(line,col); return GT; }
"<="	{ col+=2; yylval.pos=A_Pos(line,col);return LE; }
">="	{ col+=2; yylval.pos=A_Pos(line,col);return GE; }
"=="	{ col+=2; yylval.pos=A_Pos(line,col);return EQ; }
"!="	{ col+=2; yylval.pos=A_Pos(line,col);return NE; }
"&&"	{ col+=2; yylval.pos=A_Pos(line,col);return AND; }
"||"	{ col+=2; yylval.pos=A_Pos(line,col);return OR; }
"!"	{ col++; yylval.pos=A_Pos(line,col);return NOT; }
"->"	{ col+=2; yylval.pos=A_Pos(line,col);return RIGHTARR; }


"fn"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return FN; }
"struct"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return STRUCT; }
"let"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return LET; }

"if"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return IF; }
"else"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return ELSE; }
"while"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return WHILE; }
"break"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return BREAK; }
"continue"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return CONTINUE; }
"ret"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return RETURN; }

"int"	{ col+=yyleng;yylval.pos=A_Pos(line,col);return INT; }


[a-zA-Z_]+([a-zA-Z0-9_]*) 	{ 
    int len = yyleng;
    char* new_text = (char*)malloc((len+1)*sizeof(char));
    strcpy(new_text, yytext);
    new_text[len]='\0';
    col+=yyleng;
    yylval.tokenId = A_TokenId(A_Pos(line, col), new_text);  
    return ID; 

}
[1-9][0-9]*|0	{ 
    col+=yyleng; 
    yylval.tokenNum = A_TokenNum(A_Pos(line, col),atoi(yytext));
    return NUM;
}



" "   { col++; }
\t   { col+=4; }
\r\n      { line++;col=1;}
\n      { line++;col=1;}
\r      { line++;col=1;}
.	{ printf("Unknown text %s in line %d, col %d\n", yytext, line, col); }

}
%%