/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    SUB = 259,                     /* SUB  */
    MUL = 260,                     /* MUL  */
    DIV = 261,                     /* DIV  */
    LT = 262,                      /* LT  */
    LE = 263,                      /* LE  */
    GT = 264,                      /* GT  */
    GE = 265,                      /* GE  */
    EQ = 266,                      /* EQ  */
    NE = 267,                      /* NE  */
    AND = 268,                     /* AND  */
    OR = 269,                      /* OR  */
    NOT = 270,                     /* NOT  */
    COLON = 271,                   /* COLON  */
    SEMICOLON = 272,               /* SEMICOLON  */
    RIGHTARR = 273,                /* RIGHTARR  */
    ASSIGN = 274,                  /* ASSIGN  */
    DOT = 275,                     /* DOT  */
    COMMA = 276,                   /* COMMA  */
    LPAR = 277,                    /* LPAR  */
    RPAR = 278,                    /* RPAR  */
    LSQR = 279,                    /* LSQR  */
    RSQR = 280,                    /* RSQR  */
    LBRA = 281,                    /* LBRA  */
    RBRA = 282,                    /* RBRA  */
    BREAK = 283,                   /* BREAK  */
    CONTINUE = 284,                /* CONTINUE  */
    WHILE = 285,                   /* WHILE  */
    IF = 286,                      /* IF  */
    ELSE = 287,                    /* ELSE  */
    RETURN = 288,                  /* RETURN  */
    FN = 289,                      /* FN  */
    STRUCT = 290,                  /* STRUCT  */
    LET = 291,                     /* LET  */
    INT = 292,                     /* INT  */
    ID = 293,                      /* ID  */
    NUM = 294                      /* NUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define LT 262
#define LE 263
#define GT 264
#define GE 265
#define EQ 266
#define NE 267
#define AND 268
#define OR 269
#define NOT 270
#define COLON 271
#define SEMICOLON 272
#define RIGHTARR 273
#define ASSIGN 274
#define DOT 275
#define COMMA 276
#define LPAR 277
#define RPAR 278
#define LSQR 279
#define RSQR 280
#define LBRA 281
#define RBRA 282
#define BREAK 283
#define CONTINUE 284
#define WHILE 285
#define IF 286
#define ELSE 287
#define RETURN 288
#define FN 289
#define STRUCT 290
#define LET 291
#define INT 292
#define ID 293
#define NUM 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser.yacc"

//   int val;
//   char* str;
  A_pos pos;
  A_tokenId tokenId;
  A_tokenNum tokenNum;
  A_type type;
  A_rightValList rightValList;
  A_fnCall fnCall;
  A_indexExpr indexExpr;
  A_arrayExpr arrayExpr;
  A_memberExpr memberExpr;
  A_exprUnit exprUnit;
  A_arithBiOpExpr arithBiOpExpr;
  A_arithUExpr arithUExpr;
  A_arithExpr arithExpr;
  A_boolBiOpExpr boolBiOpExpr;
  A_boolUOpExpr boolUOpExpr;
  A_boolExpr boolExpr;
  A_comExpr comExpr;
  A_boolUnit boolUnit;
  A_rightVal rightVal;
  A_leftVal leftVal;
  A_assignStmt assignStmt;
  A_varDeclScalar varDeclScalar;
  A_varDeclArray varDeclArray;
  A_varDecl varDecl;
  A_varDefScalar varDefScalar;
  A_varDefArray varDefArray;
  A_varDef varDef;
  A_varDeclStmt varDeclStmt;
  A_varDeclList varDeclList;
  A_structDef structDef;
  A_fnDecl fnDecl;
  A_paramDecl paramDecl;
  A_codeBlockStmtList codeBlockStmtList;
  A_fnDef fnDef;
  A_ifStmt ifStmt;
  A_whileStmt whileStmt;
  A_callStmt callStmt;
  A_returnStmt returnStmt;
  A_codeBlockStmt codeBlockStmt;
  A_fnDeclStmt fnDeclStmt;
  A_programElement programElement;
  A_programElementList programElementList;
  A_program program;

#line 193 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
