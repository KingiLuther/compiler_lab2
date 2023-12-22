%{
#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  line,col;
extern int  yywrap();
}

%}

%union {
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
%token <pos> SEMICOLON
%token <pos> RIGHTARR
%token <pos> ASSIGN
%token <pos> DOT
%token <pos> COMMA
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
%token <pos> RETURN
%token <pos> FN
%token <pos> STRUCT
%token <pos> LET
%token <pos> INT

%token <tokenId> ID

%token <tokenNum> NUM

%type <type> Type
%type <leftVal> LeftVal
%type <rightVal> RightVal
%type <rightValList> RightValList
%type <fnCall> FnCall
%type <indexExpr> IndexExpr
%type <arrayExpr> ArrayExpr
%type <memberExpr> MemberExpr
%type <arithExpr> ArithExpr
%type <arithUExpr> ArithUExpr
%type <arithBiOpExpr> ArithBiOpExpr
%type <boolBiOpExpr> BoolBiOpExpr
%type <boolUOpExpr> BoolUOpExpr
%type <boolExpr> BoolExpr
%type <comExpr> ComExpr
%type <boolUnit> BoolUnit
%type <programElementList> ProgramElementList
%type <programElement> ProgramElement
%type <exprUnit> ExprUnit
%type <structDef> StructDef
%type <paramDecl> ParamDecl
%type <varDecl> VarDecl
%type <varDeclScalar> VarDeclScalar
%type <varDeclArray> VarDeclArray
%type <varDeclList> VarDeclList
%type <varDeclStmt> VarDeclStmt
%type <varDef> VarDef
%type <varDefScalar> VarDefScalar
%type <varDefArray> VarDefArray
%type <assignStmt> AssignStmt 
%type <callStmt> CallStmt 
%type <ifStmt> IfStmt 
%type <whileStmt> WhileStmt 
%type <returnStmt> ReturnStmt 
%type <fnDeclStmt> FnDeclStmt 
%type <fnDecl> FnDecl 
%type <fnDef> FnDef
%type <codeBlockStmt> CodeBlockStmt
%type <codeBlockStmtList> CodeBlockStmtList
%type <program> Program

%left		ADD SUB
%left		MUL DIV

%start Program

%%                   /* beginning of rules section */
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
  $$ = A_ProgramNullStmt($1);
}
;

FnDeclStmt:FnDecl SEMICOLON
{
  $$=A_FnDeclStmt($1->pos,$1);
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

ReturnStmt: RETURN RightVal SEMICOLON
{
  $$=A_ReturnStmt($1, $2);
}
|RETURN SEMICOLON
{
  $$=A_ReturnStmt($1, NULL);
}
;

CallStmt: FnCall SEMICOLON
{
  $$=A_CallStmt($1->pos, $1);
}
;

WhileStmt: WHILE LPAR BoolExpr RPAR LBRA CodeBlockStmtList RBRA
{
  $$=A_WhileStmt($1, $3, $6);
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

FnDef: FnDecl LBRA CodeBlockStmtList RBRA
{
  $$ = A_FnDef($1->pos, $1, $3);
}
;

CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList
{
  $$ = A_CodeBlockStmtList($1, $2);
}
| CodeBlockStmt
{
  $$ = A_CodeBlockStmtList($1, NULL);
}
| 
{
  $$ = NULL;
}
;

ParamDecl: VarDeclList
{
  $$=A_ParamDecl($1);
}
;

FnDecl: FN ID LPAR ParamDecl RPAR RIGHTARR Type
{
  $$=A_FnDecl($1,$2->id, $4, $7);
}
|FN ID LPAR ParamDecl RPAR
{
  $$=A_FnDecl($1,$2->id, $4, NULL);
}
;

StructDef: STRUCT ID LBRA VarDeclList RBRA 
{
  $$=A_StructDef($1, $2->id, $4);
}
;

VarDeclList: VarDecl COMMA VarDeclList
{
  $$ = A_VarDeclList($1, $3);
}
| VarDecl
{
  $$= A_VarDeclList($1, NULL);
}
|
{
  $$=NULL;
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

VarDef : VarDefScalar
{
  $$=A_VarDef_Scalar($1->pos, $1);
}
| VarDefArray
{
  $$=A_VarDef_Array($1->pos, $1);
}
;

VarDefArray: ID LSQR NUM RSQR COLON Type ASSIGN LBRA RightValList RBRA
{
  $$=A_VarDefArray($1->pos,$1->id,$3->num, $6, $9);

}
;

VarDefScalar:ID COLON Type ASSIGN RightVal
{
  $$=A_VarDefScalar($1->pos, $1->id, $3 ,$5);
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

VarDeclArray:ID LSQR NUM RSQR COLON Type 
{
  $$=A_VarDeclArray($1->pos, $1->id, $3->num, $6);
}
;

VarDeclScalar:ID COLON Type 
{
  $$=A_VarDeclScalar($1->pos, $1->id, $3);
}
;

AssignStmt: LeftVal ASSIGN RightVal SEMICOLON
{
  $$=A_AssignStmt($1->pos,$1,$3);
}
;

LeftVal: ArrayExpr 
{
  $$=A_ArrExprLVal($1->pos, $1);
}
| MemberExpr
{
  $$=A_MemberExprLVal($1->pos, $1);
}
| ID
{
  $$=A_IdExprLVal($1->pos, $1->id);
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

BoolUnit: ComExpr
{
  $$=A_ComExprUnit($1->pos, $1);
}
| LPAR BoolExpr RPAR
{
  $$=A_BoolExprUnit($1, $2);
}
| BoolUOpExpr
{
  $$=A_BoolUOpExprUnit($1->pos, $1);
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


BoolExpr: BoolBiOpExpr
{
  $$=A_BoolBiOp_Expr($1->pos, $1);
}
| BoolUnit
{
  $$=A_BoolExpr($1->pos, $1);
}
;

BoolUOpExpr: NOT BoolUnit
{
  $$=A_BoolUOpExpr($1, A_not, $2);
}
;


// take arithExpr as the sample for modification.
BoolBiOpExpr : BoolExpr AND BoolExpr
{
  $$=A_BoolBiOpExpr($1->pos,A_and,$1,$3);
}
| BoolExpr OR BoolExpr
{
  $$=A_BoolBiOpExpr($1->pos,A_or,$1,$3);
}
;

ArithExpr :ArithBiOpExpr
{
  $$=A_ArithBiOp_Expr($1->pos, $1);
}
|ExprUnit
{
  $$ = A_ExprUnit($1->pos, $1);
}
;

ArithUExpr:SUB ExprUnit 
{
  $$ = A_ArithUExpr($1,A_neg,$2);
}
;

ArithBiOpExpr: ArithExpr ADD ArithExpr
{
  $$ = A_ArithBiOpExpr($1->pos, A_add, $1, $3);
}
| ArithExpr SUB ArithExpr
{
  $$ = A_ArithBiOpExpr($1->pos, A_sub, $1, $3);
}
| ArithExpr MUL ArithExpr
{
  $$ = A_ArithBiOpExpr($1->pos, A_mul, $1, $3);
}
| ArithExpr DIV ArithExpr
{
  $$ = A_ArithBiOpExpr($1->pos, A_div, $1, $3);
}
;



ExprUnit: ID
{
  $$=A_IdExprUnit($1->pos,$1->id);
}
| NUM
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


MemberExpr: LeftVal DOT ID
{
  $$=A_MemberExpr($1->pos, $1, $3->id);
}
;

ArrayExpr: LeftVal LSQR IndexExpr RSQR
{
  $$=A_ArrayExpr($1->pos, $1, $3);
}
;

IndexExpr:NUM
{
  $$=A_NumIndexExpr($1->pos, $1->num);
}
| ID
{
  $$=A_IdIndexExpr($1->pos, $1->id);
}
;

FnCall: ID LPAR RightValList RPAR
{
  $$=A_FnCall($1->pos, $1->id, $3);
}
;

RightValList: RightVal COMMA RightValList
{
  $$=A_RightValList($1, $3);
}
| RightVal
{
  $$=A_RightValList($1, NULL);
}
|
{
  $$=NULL;
}
;

Type: INT
{
  $$=A_NativeType($1,A_intTypeKind);
}
| ID
{
  $$=A_StructType($1->pos,$1->id);
}

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