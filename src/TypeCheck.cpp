#include "TypeCheck.h"

// maps to store the type information. Feel free to design new data structures if you need.
typeMap g_token2Type; // global token ids to type
typeMap funcparam_token2Type; // func params token ids to type
typeMap funcparam_token2Type; // func params token ids to type
vector<typeMap*> local_token2Type; // local ids to type, works as a stack

paramMemberMap func2Param;
paramMemberMap struct2Members;


// private util functions. You can use these functions to help you debug.
void error_print(std::ostream* out, A_pos p, string info)
{
    *out << "Typecheck error in line " << p->line << ", col " << p->col << ": " << info << std::endl;
    exit(0);
}


void print_token_map(typeMap* map){
    for(auto it = map->begin(); it != map->end(); it++){
        std::cout << it->first << " : ";
        switch (it->second->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second->u.structType);
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }
}


// public functions
// This is the entrace of this file.
void check_Prog(std::ostream* out, aA_program p)
{
    // p is the root of AST tree.
    for (auto ele : p->programElements) {
    /*
        Write your code here.

        Hint:
        1. Design the order of checking the program elements to meet the requirements that funtion declaration and global variable declaration can be used anywhere in the program.

        2. Many types of statements indeed collapse to some same units, so a good abstract design will help you reduce the amount of your code.
    */
        if(ele->kind == A_programVarDeclStmtKind) {
            check_VarDecl(out, ele->u.varDeclStmt);
        }else if (ele->kind == A_programStructDefKind){
            check_StructDef(out, ele->u.structDef);
        }
    }

    for (auto ele : p->programElements) {
        if(ele->kind == A_programFnDeclStmtKind){
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
        }
        else if (ele->kind == A_programFnDefKind){
            check_FnDecl(out, ele->u.fnDef->fnDecl);
        }
    }

    for (auto ele : p->programElements){
        if(ele->kind == A_programFnDefKind){
            check_FnDef(out, ele->u.fnDef);
        }
        else if (ele->kind == A_programNullStmtKind){
            // do nothing
        }
    }

    (*out) << "Typecheck passed!" << std::endl;
    return;
}


void check_VarDecl(std::ostream* out, aA_varDeclStmt vd)
{
    // variable declaration statement
    if (!vd)
        return;
    string name;
    if (vd->kind == A_varDeclStmtType::A_varDeclKind){
        // if declaration only
        // Example:
        //   let a:int;
        //   let a[5]:int;

        /* write your code here*/
    }
    else if (vd->kind == A_varDeclStmtType::A_varDefKind){
        // if both declaration and initialization
        // Example:
        //   let a:int = 5;

        /* write your code here */
    }
    return;
}


void check_StructDef(std::ostream* out, aA_structDef sd)
{
    if (!sd)
        return;
    // structure definition
    // Example:
    //      struct A{
    //          a:int;
    //          b:int;
    //      }

    /* write your code here */
    if (!sd)
        return;
    string name = *sd->id;
    if (struct2Members.find(name) != struct2Members.end())
        error_print(out, sd->pos, "This id is already defined!");
    struct2Members[name] = &(sd->varDecls);
    return;
}


void check_FnDecl(std::ostream* out, aA_fnDecl fd)
{
    // Example:
    //      fn main(a:int, b:int)->int
    if (!fd)
        return;

    /*
        write your code here
        Hint: you may need to check if the function is already declared
    */
    // if already declared, should match
    if (func2Param.find(name) != func2Param.end()){
        // is function ret val matches
        if(!comp_aA_type(func2retType[name], fd->type))
            error_print(out, fd->pos, "The function return type doesn't match the declaration!");
        // is function params matches decl
        if(func2Param[name]->size() != fd->paramDecl->varDecls.size())
            error_print(out, fd->pos, "The function param list doesn't match the declaration!");
        for (int i = 0; i<func2Param[name]->size(); i++){
            if(!comp_aA_type(func2Param[name]->at(i)->u.declScalar->type, fd->paramDecl->varDecls[i]->u.declScalar->type))
                error_print(out, fd->pos, "The function param type doesn't match the declaration!");
        }
    }else{
        // if not defined as a function
        // if defined as a variable
        if(find_token(name))
            error_print(out, fd->pos, "This id is already defined as a variable!");
        else{
            // else, record this
            func2retType[name] = fd->type;
            func2Param[name] = &fd->paramDecl->varDecls;
            // func param list should not duplicate
            for (int i = 0; i<fd->paramDecl->varDecls.size(); i++){
                for (int j = i+1; j<fd->paramDecl->varDecls.size(); j++){
                    if(get_varDecl_id(fd->paramDecl->varDecls[i]).compare(get_varDecl_id(fd->paramDecl->varDecls[j])) == 0)
                        error_print(out, fd->pos, "The function parameter list should not duplicate!");
                }
            }
        }

    }
    return;
}


void check_FnDeclStmt(std::ostream* out, aA_fnDeclStmt fd)
{
    // Example:
    //      fn main(a:int, b:int)->int;
    if (!fd)
        return;
    check_FnDecl(out, fd->fnDecl);
    return;
}


void check_FnDef(std::ostream* out, aA_fnDef fd)
{
    // Example:
    //      fn main(a:int, b:int)->int{
    //          let c:int;
    //          c = a + b;
    //          return c;
    //      }
    if (!fd)
        return;
    check_FnDecl(out, fd->fnDecl);
    /*
        write your code here
        Hint: you may pay attention to the function parameters, local variables and global variables.
    */
    for (aA_varDecl vd : fd->fnDecl->paramDecl->varDecls)
    {
        if(vd->kind == A_varDeclType::A_varDeclScalarKind)
            funcparam_token2Type[*vd->u.declScalar->id] = vd->u.declScalar->type;
        else if(vd->kind == A_varDeclType::A_varDeclArrayKind)
            funcparam_token2Type[*vd->u.declArray->id] = vd->u.declArray->type;
    }

    local_token2Type.push_back(new typeMap());
    for (aA_codeBlockStmt stmt : fd->stmts)
    {
        check_CodeblockStmt(out, stmt);
        // return value type should match
        if(stmt->kind == A_codeBlockStmtType::A_returnStmtKind)
            check_LeftRightVal(out, fd->fnDecl->type, stmt->u.returnStmt->retVal);
        // else if (stmt->kind == A_codeBlockStmtType::A_varDeclStmtKind)
        //     local_vars.push_back(*stmt->u.varDeclStmt->u.varDecl->u.declArray->id);
    }
    local_token2Type.pop_back();

    // erase local vars defined in this function
    funcparam_token2Type.clear();
    return;
}


void check_CodeblockStmt(std::ostream* out, aA_codeBlockStmt cs){
    if(!cs)
        return;
    switch (cs->kind)
    {
    case A_codeBlockStmtType::A_varDeclStmtKind:
        check_VarDecl(out, cs->u.varDeclStmt);
        break;
    case A_codeBlockStmtType::A_assignStmtKind:
        check_AssignStmt(out, cs->u.assignStmt);
        break;
    case A_codeBlockStmtType::A_ifStmtKind:
        check_IfStmt(out, cs->u.ifStmt);
        break;
    case A_codeBlockStmtType::A_whileStmtKind:
        check_WhileStmt(out, cs->u.whileStmt);
        break;
    case A_codeBlockStmtType::A_callStmtKind:
        check_CallStmt(out, cs->u.callStmt);
        break;
    case A_codeBlockStmtType::A_returnStmtKind:
        check_ReturnStmt(out, cs->u.returnStmt);
        break;
    default:
        break;
    }
    return;
}


void check_AssignStmt(std::ostream* out, aA_assignStmt as){
    if(!as)
        return;
    string name;
    switch (as->leftVal->kind)
    {
        case A_leftValType::A_varValKind:{
            /* write your code here */
        }
            break;
        case A_leftValType::A_arrValKind:{
            /* write your code here */
        }
            break;
        case A_leftValType::A_memberValKind:{
            /* write your code here */
        }
            break;
    }
    return;
}


void check_ArrayExpr(std::ostream* out, aA_arrayExpr ae){
    if(!ae)
        return;
    /*
        Example:
            a[1] = 0;
        Hint:
            check the validity of the array index
    */
}


aA_type check_MemberExpr(std::ostream* out, aA_memberExpr me){
    // check if the member exists and return the tyep of the member
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way. Feel
    // free to change the design pattern if you need.
    if(!me)
        return nullptr;
    /*
        Example:
            a.b
    */
    return nullptr;
}


void check_IfStmt(std::ostream* out, aA_ifStmt is){
    if(!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    for(aA_codeBlockStmt s : is->ifStmts){
        check_CodeblockStmt(out, s);
    }
    for(aA_codeBlockStmt s : is->elseStmts){
        check_CodeblockStmt(out, s);
    }
    return;
}


void check_BoolExpr(std::ostream* out, aA_boolExpr be){
    if(!be)
        return;
    switch (be->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:
        /* write your code here */
        break;
    case A_boolExprType::A_boolUnitKind:
        check_BoolUnit(out, be->u.boolUnit);
        break;
    default:
        break;
    }
    return;
}


void check_BoolUnit(std::ostream* out, aA_boolUnit bu){
    if(!bu)
        return;
    switch (bu->kind)
    {
        case A_boolUnitType::A_comOpExprKind:{
            /* write your code here */
            aA_type leftTyep = check_ExprUnit(out, bu->u.comExpr->left);
            aA_type rightTyep = check_ExprUnit(out, bu->u.comExpr->right);
            if(leftTyep->type != A_dataType::A_nativeTypeKind || rightTyep->type != A_dataType::A_nativeTypeKind)
                error_print(out, bu->pos, "None native type are not comparable!");
            if(leftTyep->u.nativeType != rightTyep->u.nativeType)
                error_print(out, bu->pos, "The two operands should be the same type!");
        }
            break;
        case A_boolUnitType::A_boolExprKind:
            /* write your code here */
            check_BoolExpr(out, bu->u.boolExpr);
            break;
        case A_boolUnitType::A_boolUOpExprKind:
            /* write your code here */
            check_BoolUnit(out, bu->u.boolUOpExpr->cond);
            break;
        default:
            break;
    }
    return;
}


aA_type check_ExprUnit(std::ostream* out, aA_exprUnit eu){
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way.
    // Feel free to change the design pattern if you need.
    if(!eu)
        return nullptr;
    aA_type ret;
    switch (eu->kind)
    {
        case A_exprUnitType::A_idExprKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_numExprKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_fnCallKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_arrayExprKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_memberExprKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_arithExprKind:{
            /* write your code here */
        }
            break;
        case A_exprUnitType::A_arithUExprKind:{
            /* write your code here */
        }
            break;
    }
    return ret;
}


void check_FuncCall(std::ostream* out, aA_fnCall fc){
    if(!fc)
        return;
    // Example:
    //      foo(1, 2);

    /* write your code here */
    return ;
}


void check_WhileStmt(std::ostream* out, aA_whileStmt ws){
    if(!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    for(aA_codeBlockStmt s : ws->whileStmts){
        check_CodeblockStmt(out, s);
    }
    return;
}


void check_CallStmt(std::ostream* out, aA_callStmt cs){
    if(!cs)
        return;
    check_FuncCall(out, cs->fnCall);
    return;
}


void check_ReturnStmt(std::ostream* out, aA_returnStmt rs){
    if(!rs)
        return;
    return;
}
