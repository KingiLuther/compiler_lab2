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
  A_pos pos;
  A_program program;
  A_programElementList programElementList;
  A_programElement programElement;
  A_arithExpr arithExpr;
  A_exprUnit exprUnit;
  A_structDef structDef;
  A_varDeclStmt varDeclStmt;
  A_fnDeclStmt fnDeclStmt;
  A_fnDef fnDef;
  A_tokenId tokenId;
  A_tokenNum tokenNum;
  A_varDef varDef;
  A_varDecl varDecl;
  A_fnDecl fnDecl;
  A_codeBlockStmtList codeBlockStmtList;
  A_codeBlockStmt codeBlockStmt;
  A_type type;
  A_paramDecl paramDecl;
  A_varDeclList varDeclList;
  A_returnStmt returnStmt;
  A_whileStmt whileStmt;
  A_ifStmt ifStmt;
  A_callStmt callStmt;
  A_assignStmt assignStmt;
  A_rightVal rightVal;
  A_rightValList rightValList;
  A_leftVal leftVal;
  A_fnCall fnCall;
  A_boolExpr boolExpr;
  A_boolUnit boolUnit;
  A_indexExpr indexExpr;
}

%token <pos> ADD
%token <pos> SUB
%token <pos> UMINUS
%token <pos> MUL
%token <pos> DIV
%token <pos> AND
%token <pos> OR
%token <pos> NOT
%token <pos> GT
%token <pos> LT
%token <pos> GE
%token <pos> LE
%token <pos> EQ
%token <pos> NE
%token <pos> ASSIGN
%token <pos> COMMA
%token <pos> SEMICOLON // ;
%token <pos> COLON // :
%token <pos> LEFTP
%token <pos> RIGHTP
%token <pos> LEFTBRACE //{
%token <pos> RIGHTBRACE //}
%token <pos> LEFTBRACKET //[
%token <pos> RIGHTBRACKET //]
%token <pos> RVAL //->
%token <pos> MEM //.
%token <pos> LET
%token <pos> IF
%token <pos> ELSE
%token <pos> WHILE
%token <pos> INT
%token <pos> FN
%token <pos> RETURN
%token <pos> STRUCT
%token <pos> BREAK
%token <pos> CONTINUE

%token <tokenId> ID
%token <tokenNum> NUMBER

%right ASSIGN
%left OR
%left AND
%left EQ NE
%left GT LT GE LE
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS NOT


%type <program> Program
%type <arithExpr> ArithExpr
%type <programElementList> ProgramElementList
%type <programElement> ProgramElement
%type <exprUnit> ExprUnit
%type <structDef> StructDef
%type <varDeclStmt> VarDeclStmt
%type <fnDeclStmt> FnDeclStmt
%type <fnDef> FnDef
%type <fnDecl> FnDecl 
%type <varDecl> VarDecl
%type <varDef> VarDef
%type <codeBlockStmtList> CodeBlockStmtList
%type <codeBlockStmt> CodeBlockStmt
%type <type> Type
%type <paramDecl> ParamDecl
%type <varDeclList> VarDeclList
%type <returnStmt> ReturnStmt
%type <whileStmt> WhileStmt
%type <ifStmt> IfStmt
%type <callStmt> CallStmt
%type <assignStmt> AssignStmt
%type <rightVal> RightVal
%type <rightValList> RightValList
%type <leftVal> LeftVal
%type <fnCall> FnCall
%type <boolExpr> BoolExpr
%type <boolUnit> BoolUnit
%type <indexExpr> IndexExpr

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

VarDeclStmt: LET VarDecl SEMICOLON
{
  $$ = A_VarDeclStmt($1, $2);
}
| LET VarDef SEMICOLON
{
  $$ = A_VarDefStmt($1, $2);
}
;

VarDecl: ID LEFTBRACKET NUMBER RIGHTBRACKET COLON Type
{
  $$ = A_VarDecl_Array($1->pos, A_VarDeclArray($1->pos, $1->id, $3->num, $6));
}
| ID LEFTBRACKET NUMBER RIGHTBRACKET
{
  $$ = A_VarDecl_Array($1->pos, A_VarDeclArray($1->pos, $1->id, $3->num, NULL));
}
| ID COLON Type
{
  $$ = A_VarDecl_Scalar($1->pos, A_VarDeclScalar($1->pos, $1->id, $3));
}
| ID
{
  $$ = A_VarDecl_Scalar($1->pos, A_VarDeclScalar($1->pos, $1->id, NULL));
}
;

VarDef: ID LEFTBRACKET NUMBER RIGHTBRACKET COLON Type ASSIGN LEFTBRACE RightValList RIGHTBRACE
{
  $$ = A_VarDef_Array($1->pos, A_VarDefArray($1->pos, $1->id, $3->num, $6, $9));
}
| ID LEFTBRACKET NUMBER RIGHTBRACKET ASSIGN LEFTBRACE RightValList RIGHTBRACE
{
  $$ = A_VarDef_Array($1->pos, A_VarDefArray($1->pos, $1->id, $3->num, NULL, $7));
}
| ID COLON Type ASSIGN RightVal
{
  $$ = A_VarDef_Scalar($1->pos, A_VarDefScalar($1->pos, $1->id, $3, $5));
}
| ID ASSIGN RightVal
{
  $$ = A_VarDef_Scalar($1->pos, A_VarDefScalar($1->pos, $1->id, NULL, $3));
}
;

RightValList: RightVal COMMA RightValList
{
  $$ = A_RightValList($1, $3);
}
| RightVal
{
  $$ = A_RightValList($1, NULL);
}
|
{
  $$ = NULL;
}
;

StructDef: STRUCT ID LEFTBRACE VarDeclList RIGHTBRACE
{
  $$ = A_StructDef($1, $2->id, $4);
}
;

FnDeclStmt: FnDecl SEMICOLON
{
  $$ = A_FnDeclStmt($1->pos, $1);
}
;

FnDef: FnDecl LEFTBRACE CodeBlockStmtList RIGHTBRACE
{
  $$ = A_FnDef($1->pos, $1, $3);
}
;

FnDecl: FN ID LEFTP ParamDecl RIGHTP RVAL Type
{
  $$ = A_FnDecl($1, $2->id, $4, $7);
}
| FN ID LEFTP ParamDecl RIGHTP
{
  $$ = A_FnDecl($1, $2->id, $4, NULL);
}
;

ParamDecl: VarDeclList
{
  $$ = A_ParamDecl($1);
}
;

VarDeclList: VarDecl COMMA VarDeclList
{
  $$ = A_VarDeclList($1,$3);
}
| VarDecl
{
  $$ = A_VarDeclList($1, NULL);
}
|
{
  $$ = NULL;
}
;

Type: INT
{
  $$ = A_NativeType($1,A_intTypeKind);
}
| ID
{
  $$ = A_StructType($1->pos,$1->id);
}
;

CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList
{
  $$ = A_CodeBlockStmtList($1,$2);
}
|
{
  $$ = NULL;
}
;

CodeBlockStmt: BREAK SEMICOLON
{
  $$ = A_BlockBreakStmt($1);
}
| CONTINUE SEMICOLON
{
  $$ = A_BlockContinueStmt($1);
}
| ReturnStmt
{
  $$ = A_BlockReturnStmt($1->pos, $1);
}
| WhileStmt
{
  $$ = A_BlockWhileStmt($1->pos, $1);
}
| IfStmt
{
  $$ = A_BlockIfStmt($1->pos, $1);
}
| CallStmt
{
  $$ = A_BlockCallStmt($1->pos, $1);
}
| AssignStmt
{
  $$ = A_BlockAssignStmt($1->pos, $1);
}
| VarDeclStmt
{
  $$ = A_BlockVarDeclStmt($1->pos, $1);
}
| SEMICOLON
{
  $$ = A_BlockNullStmt($1);
}
;

ReturnStmt: RETURN RightVal SEMICOLON
{
  $$ = A_ReturnStmt($1, $2);
}
| RETURN SEMICOLON
{
  $$ = A_ReturnStmt($1, NULL);
}
;

WhileStmt: WHILE LEFTP BoolExpr RIGHTP LEFTBRACE CodeBlockStmtList RIGHTBRACE
{
  $$ = A_WhileStmt($1, $3, $6);
}
;

IfStmt: IF LEFTP BoolExpr RIGHTP LEFTBRACE CodeBlockStmtList RIGHTBRACE ELSE LEFTBRACE CodeBlockStmtList RIGHTBRACE
{
  $$ = A_IfStmt($1, $3, $6, $10);
}
| IF LEFTP BoolExpr RIGHTP LEFTBRACE CodeBlockStmtList RIGHTBRACE
{
  $$ = A_IfStmt($1, $3, $6, NULL);
}
;

CallStmt: FnCall SEMICOLON
{
  $$ = A_CallStmt($1->pos, $1);
}
;

AssignStmt: LeftVal ASSIGN RightVal SEMICOLON
{
  $$ = A_AssignStmt($1->pos, $1, $3);
}
;

LeftVal: LeftVal MEM ID
{
  $$ = A_MemberExprLVal($1->pos, A_MemberExpr($1->pos, $1, $3->id));
}
| LeftVal LEFTBRACKET IndexExpr RIGHTBRACKET
{
  $$ = A_ArrExprLVal($1->pos, A_ArrayExpr($1->pos, $1, $3));
}
| ID
{
  $$ = A_IdExprLVal($1->pos, $1->id);
}
;

RightVal: ArithExpr
{
  $$ = A_ArithExprRVal($1->pos, $1);
}
| BoolExpr
{
  $$ = A_BoolExprRVal($1->pos, $1);
}
;

ArithExpr: ArithExpr ADD ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_add, $1, $3));
}
| ArithExpr SUB ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_sub, $1, $3));
}
| ArithExpr MUL ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_mul, $1, $3));
}
| ArithExpr DIV ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_div, $1, $3));
}
| ExprUnit
{
  $$ = A_ExprUnit($1->pos, $1);
}
;

BoolExpr: BoolExpr AND BoolExpr
{
  $$ = A_BoolBiOp_Expr($1->pos, A_BoolBiOpExpr($1->pos, A_and, $1, $3));
}
| BoolExpr OR BoolExpr
{
  $$ = A_BoolBiOp_Expr($1->pos, A_BoolBiOpExpr($1->pos, A_or, $1, $3));
}
| BoolUnit
{
  $$ = A_BoolExpr($1->pos, $1);
}
;

BoolUnit: LEFTP BoolExpr RIGHTP
{
  $$ = A_BoolExprUnit($1, $2);
}
| NOT BoolUnit
{
  $$ = A_BoolUOpExprUnit($1, A_BoolUOpExpr($1, A_not, $2));
}
| ExprUnit LT ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_lt, $1, $3));
}
| ExprUnit LE ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_le, $1, $3));
}
| ExprUnit GT ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_gt, $1, $3));
}
| ExprUnit GE ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_ge, $1, $3));
}
| ExprUnit EQ ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_eq, $1, $3));
}
| ExprUnit NE ExprUnit
{
  $$ = A_ComExprUnit($1->pos, A_ComExpr($1->pos, A_ne, $1, $3));
}
;

ExprUnit: SUB ExprUnit %prec UMINUS
{
  $$ = A_ArithUExprUnit($1, A_ArithUExpr($1, A_neg, $2));
}
| LeftVal MEM ID
{
  $$ = A_MemberExprUnit($1->pos, A_MemberExpr($1->pos, $1, $3->id));
}
| LeftVal LEFTBRACKET IndexExpr RIGHTBRACKET
{
  $$ = A_ArrayExprUnit($1->pos, A_ArrayExpr($1->pos, $1, $3));
}
| FnCall
{
  $$ = A_CallExprUnit($1->pos, $1);
}
| LEFTP ArithExpr RIGHTP
{
  $$ = A_ArithExprUnit($1, $2);
}
| ID
{
  $$ = A_IdExprUnit($1->pos, $1->id);
}
| NUMBER
{
  $$ = A_NumExprUnit($1->pos, $1->num);
}
;

FnCall: ID LEFTP RightValList RIGHTP
{
  $$ = A_FnCall($1->pos, $1->id, $3);
}
;

IndexExpr: ID
{
  $$ = A_IdIndexExpr($1->pos, $1->id);
}
| NUMBER
{
  $$ = A_NumIndexExpr($1->pos, $1->num);
}
;

%%

extern "C"{
void yyerror(char * s)
{
  fprintf(stderr, "%s\n",s);
}
int yywrap()
{
  return(1);
}
}


