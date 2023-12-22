#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include <unordered_map>
#include <stack>
#include <set>

enum A_kind{
    A_scalarKind,
    A_arrayKind
};

struct TypeKind
{
    A_kind kind;
    aA_type type;
    int length=0;
};

// you can use this type to store the type a token.
typedef std::unordered_map<string, TypeKind*> typeMap; 

// you can use this map to store the members of a struct or params of a function.
typedef std::unordered_map<string, vector<aA_varDecl>*> paramMemberMap;

// use this stack to store local variable names
typedef std::stack<vector<string>*> nameStack;

void check_Prog(std::ostream* out, aA_program p);
void check_VarDecl(std::ostream* out, aA_varDeclStmt vd);
void check_StructDef(std::ostream* out, aA_structDef sd);
void check_FnDecl(std::ostream* out, aA_fnDecl fd);
void check_FnDeclStmt(std::ostream* out, aA_fnDeclStmt fd);
void check_FnDef(std::ostream* out, aA_fnDef fd);
void check_CodeblockStmt(std::ostream* out, aA_codeBlockStmt cs, aA_type returnType);
void check_AssignStmt(std::ostream* out, aA_assignStmt as);
void check_ArrayExpr(std::ostream* out, aA_arrayExpr ae);
TypeKind* check_MemberExpr(std::ostream* out, aA_memberExpr me);
void check_IfStmt(std::ostream* out, aA_ifStmt is, aA_type returnType);
TypeKind* check_RightVal(std::ostream* out, aA_rightVal rv);
void check_BoolExpr(std::ostream* out, aA_boolExpr be);
void check_BoolUnit(std::ostream* out, aA_boolUnit bu);
TypeKind* check_ArithExpr(std::ostream* out, aA_arithExpr ae);
TypeKind* check_ExprUnit(std::ostream* out, aA_exprUnit eu);
void check_FuncCall(std::ostream* out, aA_fnCall fc);
void check_WhileStmt(std::ostream* out, aA_whileStmt ws, aA_type returnType);
void check_CallStmt(std::ostream* out, aA_callStmt cs);
void check_ReturnStmt(std::ostream* out, aA_returnStmt rs, aA_type returnType);

