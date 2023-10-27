%{
#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s);
extern int  yywrap();
}

%}


%union {
  int val;
  char* str;
  A_pos pos;
  A_type type;
  A_varDecl varDecl;
  A_varDef varDef;
  A_rightVal rightVal;
  A_arithExpr arithExpr;
  A_boolExpr boolExpr;
  A_arithBiOpExpr arithBiOpExpr;
  A_arithUExpr arithUExpr;
  A_exprUnit exprUnit;
  A_fnCall fnCall;
  A_indexExpr indexExpr;
  A_arrayExpr arrayExpr;
  A_memberExpr memberExpr;
  A_boolUnit boolUnit;
  A_boolBiOpExpr boolBiOpExpr;
  A_boolUOpExpr boolUOpExpr;
  A_comExpr comExpr;
  A_leftVal leftVal;
  A_assignStmt assignStmt;
  A_rightValList rightValList;
  A_varDefScalar varDefScalar;
  A_varDefArray varDefArray;
  A_varDeclScalar varDeclScalar;
  A_varDeclArray varDeclArray;
  A_varDeclStmt varDeclStmt;
  A_varDeclList varDeclList;
  A_structDef structDef;
  A_paramDecl paramDecl;
  A_fnDecl fnDecl;
  A_fnDef fnDef;
  A_codeBlockStmt codeBlockStmt;
  A_ifStmt ifStmt;
  A_whileStmt whileStmt;
  A_fnDeclStmt fnDeclStmt;
  A_callStmt callStmt;
  A_returnStmt returnStmt;
  A_programElement programElement;
  A_codeBlockStmtList codeBlockStmtList;
  A_programElementList programElementList;
  A_program program;
  A_tokenId tokenId;
  A_tokenNum tokenNum;
}

%token <pos> ADD
%token <pos> SUB
%token <pos> MUL
%token <pos> DIV
%token <pos> LT
%token <pos> LE
%token <pos> GT
%token <pos> GE
%token <pos> EQ
%token <pos> NE
%token <pos> AND
%token <pos> OR
%token <pos> NOT
%token <pos> COLON
%token <pos> RIGHTARR
%token <pos> ASSIGN
%token <pos> DOT
%token <pos> LPAR
%token <pos> RPAR
%token <pos> LSQR
%token <pos> RSQR
%token <pos> LBRA
%token <pos> RBRA
%token <pos> BREAK
%token <pos> CONTINUE
%token <pos> WHILE
%token <pos> IF
%token <pos> ELSE
%token <pos> RET
%token <pos> FN
%token <pos> STRUCT
%token <pos> LET
%token <pos> INT
%token <pos> SEMICOLON
%token <val> NUM
%token <str> ID

%type <type> Type
%type <tokenId> TokenId
%type <tokenNum> TokenNum
%type <leftVal> LeftVal
%type <rightVal> RightVal
%type <rightValList> RightValList
%type <fnCall> FnCall
%type <indexExpr> IndexExpr
%type <arrayExpr> ArrayExpr
%type <memberExpr> MemberExpr
%type <exprUnit> ExprUnit
%type <arithExpr> ArithExpr
%type <arithUExpr> ArithUExpr
%type <boolBiOpExpr> BoolBiOpExpr
%type <boolUOpExpr> BoolUOpExpr
%type <boolExpr> BoolExpr
%type <boolUnit> BoolUnit
%type <comExpr> ComExpr
%type <assignStmt> AssignStmt
%type <varDeclStmt> VarDeclStmt
%type <varDecl> VarDecl
%type <varDeclScalar> VarDeclScalar
%type <varDeclArray> VarDeclArray
%type <varDeclList> VarDeclList
%type <varDef> VarDef
%type <varDefScalar> VarDefScalar
%type <varDefArray> VarDefArray
%type <structDef> StructDef
%type <fnDeclStmt> FnDeclStmt
%type <fnDecl> FnDecl
%type <paramDecl> ParamDecl
%type <fnDef> FnDef
%type <codeBlockStmt> CodeBlockStmt
%type <callStmt> CallStmt
%type <ifStmt> IfStmt
%type <whileStmt> WhileStmt
%type <returnStmt> ReturnStmt
%type <codeBlockStmt> CodeBlockStmt
%type <codeBlockStmtList> CodeBlockStmtList
%type <programElement> ProgramElement
%type <programElementList> ProgramElementList
%type <program> Program
%start Program

%%                   /* beginning of rules section */
Type: INT
{
  $$ = A_NativeType($1->pos, "int");
}
| ID
{
  $$ = A_StructType($1->pos, $1);
}
;

TokenId: ID
{
  $$ = A_TokenId(A_Pos(line,col), $1);
}
;

TokenNum: NUM
{
  $$ = A_TokenNum(A_Pos(line,col), $1);
}
;

LeftVal: TokenId
{
  $$=A_IdExprLVal($1->pos, $1->id);
}
| ArrayExpr
{
  // there's some questions.
  $$=A_ArrExprLVal($1->pos, $3);
}
| MemberExpr
{
  $$=A_MemberExprLVal($1->pos, $1);
}
;

RightVal: ArithExpr
{
  $$=A_ArithExprRVal($1->pos,$1);
}
| BoolExpr
{
  $$=A_BoolExprRVal($1->pos,$1);
}
;

RightValList: RightVal COMMA RightValList
{
  $$ = A_RightValList($2->pos, $1, $3);
}
| RightVal
{
  $$ = A_RightValList($1->pos, $1, NULL);
}
;

FnCall: TokenId LPAR RightValList RPAR
{
  // $1->id?
  $$ = A_FnCall($1->pos, A_Id($1->pos, $1), $3);
}
;

IndexExpr:TokenNum
{
  $$=A_NumIndexExpr($1->pos, $1->num);
}
| TokenId
{
  $$=A_IdIndexExpr($1->pos, $1->id);
}
;

ArrayExpr: TokenId LSQR IndexExpr RSQR
{
  $$=A_ArrayExpr($1->pos, $1->id, $3);
}
;

MemberExpr: TokenId DOT TokenId
{
  $$=A_MemberExpr($1->pos, $1->id, $3->id);
}
;

ExprUnit: TokenId
{
  $$=A_IdExprUnit($1->pos,$1->id);
}
| TokenNum
{
  $$=A_NumExprUnit($1->pos,$1->num);
}
| LPAR ArithExpr RPAR
{
  $$=A_ArithExprUnit($1, $2);
}
| FnCall
{
  $$=A_CallExprUnit($1->pos,$1);
}
| ArrayExpr
{
  $$=A_ArrayExprUnit($1->pos,$1);
}
| MemberExpr
{
  $$=A_MemberExprUnit($1->pos,$1);
}
| ArithUExpr
{
  $$=A_ArithUExprUnit($1->pos,$1);
}
;

ArithExpr: ArithExpr ADD ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_add, $1, $3);
}
| ArithExpr SUB ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_sub, $1, $3);
}
| ArithExpr MUL ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_mul, $1, $3);
}
| ArithExpr DIV ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_div, $1, $3);
}
| ExprUnit
{
  $$ = A_ExprUnit($1->pos, $1);
}
;

ArithUExpr: SUB ArithExpr
{
  $$ = A_ArithUOpExpr($1->pos, A_neg, $2);
}
| ExprUnit
{
  $$ = A_ExprUnit($1->pos, $1);
}
;

ArithUExpr:SUB ExprUnit
{
  $$ = A_ArithUExpr($1,A_neg,$2);
}
;

BoolBiOpExpr : BoolExpr AND BoolUnit
{
  $$=A_BoolBiOpExpr($1->pos,A_and,$1,$3);
}
| BoolExpr OR BoolUnit
{
  $$=A_BoolBiOpExpr($1->pos,A_or,$1,$3);
}
;

BoolUOpExpr: NOT BoolUnit
{
  $$=A_BoolUOpExpr($1, A_not, $2);
}
;

BoolUnit: ComExpr
{
  $$=A_ComExprUnit($1->pos, $1);
}
| BoolExpr
{
  $$=A_BoolExprUnit($1->pos, $1);
}
| BoolUOpExpr
{
  $$=A_BoolUOpExprUnit($1->pos, $1);
}
;

BoolExpr: BoolBiOpExpr
{
  $$=A_BoolBiOp_Expr($1->pos, $1);
}
| BoolUnit
{
  $$=A_BoolExpr($1->pos, $1);
}
;

ComExpr: ExprUnit LT ExprUnit
{
  $$=A_ComExpr($1->pos,A_lt,$1,$3);
}
| ExprUnit LE ExprUnit
{
  $$=A_ComExpr($1->pos,A_le,$1,$3);
}
| ExprUnit GT ExprUnit
{
  $$=A_ComExpr($1->pos,A_gt,$1,$3);
}
| ExprUnit GE ExprUnit
{
  $$=A_ComExpr($1->pos,A_ge,$1,$3);
}
| ExprUnit EQ ExprUnit
{
  $$=A_ComExpr($1->pos,A_eq,$1,$3);
}
| ExprUnit NE ExprUnit
{
  $$=A_ComExpr($1->pos,A_ne,$1,$3);
}
;

AssignStmt: LeftVal ASSIGN RightVal SEMICOLON
{
  $$=A_AssignStmt($1->pos,$1,$3);
}
;


VarDeclStmt: LET VarDecl SEMICOLON
{
  $$ = A_VarDeclStmt($1, $2);
}
| LET VarDef SEMICOLON
{
  $$ = A_VarDefStmt($1, $2);
}
;

VarDecl: VarDeclScalar
{
  $$=A_VarDecl_Scalar($1->pos, $1);
}
| VarDeclArray
{
  $$=A_VarDecl_Array($1->pos, $1);
}
;

VarDeclScalar:TokenId COLON Type
{
  $$=A_VarDeclScalar($1->pos, $1->id, $3);
}
;

VarDeclArray:TokenId LSQR TokenNum RSQR COLON Type
{
  $$=A_VarDeclArray($1->pos, $1->id, $3->num, $6);
}
;

VarDef : VarDefScalar
{
  $$=A_VarDef_Scalar($1->pos, $1);
}
| VarDefArray
{
  $$=A_VarDef_Array($1->pos, $1);
}
;

VarDefScalar:TokenId COLON Type ASSIGN RightVal
{
  $$=A_VarDefScalar($1->pos, $1->id, $3 ,$5);
}
;

VarDefArray: TokenId LSQR TokenNum RSQR COLON Type ASSIGN LBRA RightValList RBRA
{
  $$=A_VarDefArray($1->pos,$1->id,$3->num, $6, $9);

}
;

VarDeclList: VarDecl VarDeclList
{
  $$ = A_VarDeclList($1, $2);
}
|
{
  $$ = NULL;
}
;

StructDef: STRUCT TokenId LBRA VarDeclList RBRA {
  $$=A_StructDef($1, $2->id, $4);
}
;

FnDeclStmt:FnDecl SEMICOLON
{
  $$=A_FnDeclStmt($1->pos,$1);
}
;

FnDecl: FN TokenId LPAR ParamDecl RPAR RIGHTARR Type
{
  $$=A_FnDecl($1,$2->id, $4, $7);
}

ParamDecl: VarDeclList
{
  $$=A_ParamDecl($1);
}
;

FnDef: FnDecl LBRA CodeBlockStmtList RBRA
{
  $$ = A_FnDef($1->pos, $1, $3);
}
;

ReturnStmt: RET RightVal SEMICOLON
{
  $$=A_ReturnStmt($1, $2);
}
;

CallStmt: FnCall SEMICOLON
{
  $$=A_CallStmt($1->pos, $1);
}
;

IfStmt: IF LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA
{
  $$=A_IfStmt($1, $3, $6, NULL);
}
| IF LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA ELSE LBRA CodeBlockStmtList RBRA
{
  $$=A_IfStmt($1, $3, $6, $10);
}
;

WhileStmt: WHILE LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA
{
  $$=A_WhileStmt($1, $3, $6);
}
;

ReturnStmt: RET RightVal SEMICOLON
{
  $$=A_ReturnStmt($1, $2);
}
;

CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList
{
  $$ = A_CodeBlockStmtList($1, $2);
}
|
{
  $$ = NULL;
}
;

CodeBlockStmt: VarDeclStmt
{
  $$ = A_BlockVarDeclStmt($1->pos, $1);
}
| AssignStmt
{
  $$ = A_BlockAssignStmt($1->pos, $1);
}
| CallStmt
{
  $$ = A_BlockCallStmt($1->pos, $1);
}
| IfStmt
{
  $$ = A_BlockIfStmt($1->pos, $1);
}
| WhileStmt
{
  $$ = A_BlockWhileStmt($1->pos, $1);
}
| ReturnStmt
{
  $$ = A_BlockReturnStmt($1->pos, $1);
}
| CONTINUE SEMICOLON
{
  $$ = A_BlockContinueStmt($1);
}
| BREAK SEMICOLON
{
  $$ = A_BlockBreakStmt($1);
}
| SEMICOLON
{
  $$ = A_BlockNullStmt($1);
}
;
Program: ProgramElementList
{
  root = A_Program($1);
  $$ = A_Program($1);
}
;

ProgramElementList: ProgramElement ProgramElementList
{
  $$ = A_ProgramElementList($1, $2);
}
|
{
  $$ = NULL;
}
;

ProgramElement: VarDeclStmt
{
  $$ = A_ProgramVarDeclStmt($1->pos, $1);
}
| StructDef
{
  $$ = A_ProgramStructDef($1->pos, $1);
}
| FnDeclStmt
{
  $$ = A_ProgramFnDeclStmt($1->pos, $1);
}
| FnDef
{
  $$ = A_ProgramFnDef($1->pos, $1);
}
| SEMICOLON
{
  $$ = A_ProgramNullStmt($1->pos);
}
;

%%

extern "C"{
void yyerror(char * s)
{
  fprintf(stderr, "Error: %s in line %d, col %d\n",s,line,col);
}
int yywrap()
{
  return(1);
}
}
