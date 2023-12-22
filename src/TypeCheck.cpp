#include "TypeCheck.h"
#include <string.h>

// maps to store the type information. Feel free to design new data structures if you need.
typeMap g_token2Type; // global token ids to type
typeMap funcparam_token2Type; // func params token ids to type
typeMap func2returnType;// func token ids to return type
paramMemberMap func2Param;//declared fun to param
paramMemberMap funcDef2Param;// defined fun to param
paramMemberMap struct2Members;

nameStack stk;


// private util functions. You can use these functions to help you debug.
void error_print(std::ostream* out, A_pos p, string info)
{
    *out << "Typecheck error in line " << p->line << ", col " << p->col << ": " << info << std::endl;
    exit(0);
}

bool findToken(string name){
    string native_types[] = {"int"};
    for (string native_type: native_types) {
        if (name == native_type)
            return true;
    }
    bool variable = g_token2Type.find(name) != g_token2Type.end();
    bool funcParam = funcparam_token2Type.find(name) != funcparam_token2Type.end();
    bool funcDeclId=func2Param.find(name)!=func2Param.end();
    bool funcDefId=funcDef2Param.find(name)!=funcDef2Param.find(name);
    bool structId=struct2Members.find(name)!=struct2Members.end();
    return variable || funcParam || funcDeclId || funcDefId || structId;
}

bool checkType(aA_type type){
    if (type == nullptr || type->type==A_dataType::A_nativeTypeKind)
        return true;
    else
        return struct2Members.find(*type->u.structType) != struct2Members.end();
}

TypeKind* getTokenType(string token){
    if (funcparam_token2Type.find(token) != funcparam_token2Type.end()){
        return funcparam_token2Type[token];
    }
    if (g_token2Type.find(token) != g_token2Type.end()){
        return g_token2Type[token];
    }
    return nullptr;
}

void erase_local_vars(vector<string>& local_var_ids) {
    for (string local_var_id: local_var_ids) {
        delete g_token2Type[local_var_id];
        g_token2Type.erase(local_var_id);
    }
}

void print_token_map(typeMap* map){
    for(auto it = map->begin(); it != map->end(); it++){
        std::cout << it->first << " : ";
        switch (it->second->type->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second->type->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second->type->u.structType);
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }
}

void check_FnDecl_Def(std::ostream* out, aA_fnDef fd);

// public functions
// This is the entrace of this file.
void check_Prog(std::ostream* out, aA_program p)
{
    // p is the root of AST tree.
    // check globel parts: var, struct
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programElementType::A_programVarDeclStmtKind:
            check_VarDecl(out,ele->u.varDeclStmt);
            break;
        case A_programElementType::A_programStructDefKind:
            check_StructDef(out,ele->u.structDef);
            break;
        default:
            break;
        }
    }
    // check funDecl part of funDef and funDecl
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programElementType::A_programFnDefKind:
            check_FnDecl_Def(out,ele->u.fnDef);
            break;
        case A_programElementType::A_programFnDeclStmtKind:
            check_FnDeclStmt(out,ele->u.fnDeclStmt);
            break;
        default:
            break;
        }
    }
    // check define part of funDef 
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programElementType::A_programFnDefKind:
            check_FnDef(out,ele->u.fnDef);
            break;
        default:
            break;
        }  
    }

    (*out) << "Typecheck passed!" << std::endl;
    return;
}

// type1与type2是否相同
bool compareType(aA_type type1,aA_type type2){
    if (type1 == nullptr || type2 == nullptr)
        return type1 == nullptr && type2 == nullptr;
    if (type1->type!=type2->type)
        return false;
    if (type1->type==A_dataType::A_nativeTypeKind){
        return type1->u.nativeType==type2->u.nativeType;
    } else if (type1->type==A_dataType::A_structTypeKind){
        return *type1->u.structType==*type2->u.structType;
    }
    return false;
}

// // 是否可以把type2类型的值赋给type1类型的变量
bool check_assign_type(aA_type type1,aA_type type2){
    if (type1 == nullptr || type2 == nullptr)
        return true;
    if (type1->type!=type2->type)
        return false;
    if (type1->type==A_dataType::A_nativeTypeKind){
        return type1->u.nativeType==type2->u.nativeType;
    } else if (type1->type==A_dataType::A_structTypeKind){
        return *type1->u.structType==*type2->u.structType;
    }
    return false;
}

// 是否可以把typeKind2类型的值赋给typeKind1类型的变量
bool check_assign_TypeKind(TypeKind* typeKind1, TypeKind* typeKind2){
    if (typeKind1->kind != typeKind2->kind || !check_assign_type(typeKind1->type, typeKind2->type))
        return false;
    return typeKind1->kind == A_kind::A_scalarKind || typeKind1->length == typeKind2->length;
}

// 右值是否能赋给type类型的左值（包括数组）
bool check_val_type(std::ostream* out, aA_rightVal rightVal, TypeKind* type){
    TypeKind* rightVal_type = check_RightVal(out, rightVal);
    return rightVal_type != nullptr && check_assign_TypeKind(type, rightVal_type);
}

void check_VarDecl(std::ostream* out, aA_varDeclStmt vd)
{
    // variable declaration statement 
    if (!vd)
        return;
    string name;
    vector<string>* local_var_ids = stk.empty() ? nullptr : stk.top();
    if (vd->kind == A_varDeclStmtType::A_varDeclKind){
        aA_varDecl varDecl = vd->u.varDecl;
        string tokenId;
        TypeKind* tokenType=new TypeKind();
        if (varDecl->kind == A_varDeclType::A_varDeclScalarKind){
            tokenId=*varDecl->u.declScalar->id;
            tokenType->kind=A_kind::A_scalarKind;
            tokenType->type=varDecl->u.declScalar->type;
        } else if (varDecl->kind == A_varDeclType::A_varDeclArrayKind){
            if (varDecl->u.declArray->len<=0)
                error_print(out,varDecl->u.declArray->pos,"array length must be positive!");
            tokenId=*varDecl->u.declArray->id;
            tokenType->kind=A_kind::A_arrayKind;
            tokenType->length=varDecl->u.declArray->len;
            tokenType->type=varDecl->u.declArray->type;
        }
        if (findToken(tokenId))
            error_print(out,varDecl->pos,"the varible '" + tokenId + "' has been declared!");
        else{
            if (!checkType(tokenType->type))
                error_print(out,tokenType->type->pos,"Unknown type!");
        }
        g_token2Type[tokenId]=tokenType;
        if (local_var_ids != nullptr)
            local_var_ids->emplace_back(tokenId);
    }
    else if (vd->kind == A_varDeclStmtType::A_varDefKind){
        aA_varDef varDef = vd->u.varDef;
        string tokenId;
        TypeKind* tokenType=new TypeKind();
        if (varDef->kind == A_varDefType::A_varDefScalarKind){
            tokenId=*varDef->u.defScalar->id;
            tokenType->kind=A_kind::A_scalarKind;
            tokenType->type=varDef->u.defScalar->type;
            aA_rightVal val=varDef->u.defScalar->val;
            if (!checkType(tokenType->type))
                error_print(out,tokenType->type->pos,"Unknown type!");
            if (!check_val_type(out,val,tokenType))
                error_print(out,val->pos,"type and value conflict!");
        } else if (varDef->kind == A_varDefType::A_varDefArrayKind){
            if (varDef->u.defArray->len<=0)
                error_print(out,varDef->u.defArray->pos,"array length must be positive!");
            tokenId=*varDef->u.defArray->id;
            tokenType->kind=A_kind::A_scalarKind;
            tokenType->type=varDef->u.defArray->type;
            vector<aA_rightVal> valList=varDef->u.defArray->vals;
            // if (valList.size()!=varDef->u.defArray->len)
            //     error_print(out,varDef->u.defArray->pos,"array size not equal to values!");
            if (!checkType(tokenType->type))
                error_print(out,tokenType->type->pos,"Unknown type!");
            for (auto val:valList){
                if (!check_val_type(out,val,tokenType))
                    error_print(out,val->pos,"array type and value conflict!");
            }
        }
        if (findToken(tokenId))
            error_print(out,vd->pos,"the varible '" + tokenId + "' has been declared!");
        g_token2Type[tokenId]=tokenType;
        if (local_var_ids != nullptr)
            local_var_ids->emplace_back(tokenId);
    }
    return;
}


void check_StructDef(std::ostream* out, aA_structDef sd)
{
    if (!sd)
        return;
    string structId=*sd->id;
    if (findToken(structId))
        error_print(out,sd->pos,"the token '" + structId + "' has been used.");
    vector<aA_varDecl> members=sd->varDecls;
    std::set<string> memberSet;
    for (auto mem:members){
        aA_type type;
        string memName;
        if (mem->kind==A_varDeclType::A_varDeclScalarKind){
            type=mem->u.declScalar->type;
            memName=*mem->u.declScalar->id;
        } else if (mem->kind==A_varDeclType::A_varDeclArrayKind){
            type=mem->u.declArray->type;
            memName=*mem->u.declArray->id;
            if (mem->u.declArray->len<=0)
                error_print(out,mem->u.declArray->pos,"Array length must be positive!");
        }
        if (!checkType(type))
            error_print(out,type->pos,"Unknown type!");
        if (memberSet.find(memName)!=memberSet.end())
            error_print(out,mem->pos,"Member Name cannot repeat!");
        memberSet.insert(memName);
    }
    struct2Members[structId]=&sd->varDecls;
    return;
}


void check_FnDecl(std::ostream* out, aA_fnDecl fd)
{
    // Example:
    //      fn main(a:int, b:int)->int
    if (!fd)
        return;
    string funcId=*fd->id;
    vector<aA_varDecl> params=fd->paramDecl->varDecls;
    std::set<string> paramSet;
    if (findToken(funcId))
        error_print(out,fd->pos,"the token '" + funcId + "' has been used!");
    if (!checkType(fd->type))
        error_print(out,fd->type->pos,"Function return type invalid!");
    if (func2Param.find(funcId)!=func2Param.end())
        error_print(out,fd->pos,"the function '" + funcId + "' has been declared!");
    if (funcDef2Param.find(funcId)!=funcDef2Param.find(funcId))
        error_print(out,fd->pos,"the function '" + funcId + "' has been defined!");
    for (auto param:params){
        string paramName;
        aA_type type;
        if (param->kind==A_varDeclType::A_varDeclScalarKind){
            paramName=*param->u.declScalar->id;
            type=param->u.declScalar->type;
        } else if (param->kind==A_varDeclType::A_varDeclArrayKind){
            paramName=*param->u.declArray->id;
            type=param->u.declArray->type;
            if (param->u.declArray->len<=0)
                error_print(out,param->pos,"Array length must be positive!");
        }
        if (!checkType(type))
            error_print(out,type->pos,"Function param type undefined!");
        if (paramSet.find(paramName)!=paramSet.end())
            error_print(out,param->pos,"Param id cannot repeat!");
        paramSet.insert(paramName);
    }
    func2Param[funcId]=&fd->paramDecl->varDecls;
    TypeKind* returnType=new TypeKind();
    returnType->kind=A_kind::A_scalarKind;
    returnType->type=fd->type;
    func2returnType[funcId]=returnType;
    return;
}

// check FnDecl part in FnDef
void check_FnDecl_Def(std::ostream* out, aA_fnDef fd){
    if (!fd)
        return;
    string funcId=*fd->fnDecl->id;
    vector<aA_varDecl> params=fd->fnDecl->paramDecl->varDecls;
    std::set<string> paramSet;
    if (findToken(funcId) && func2Param.find(funcId)==func2Param.end())
        error_print(out,fd->pos,"the token '" + funcId + "' has been used!");
    if (!checkType(fd->fnDecl->type))
        error_print(out,fd->fnDecl->type->pos,"Function return type invalid!");
    if (funcDef2Param.find(funcId)!=funcDef2Param.find(funcId))
        error_print(out,fd->pos,"the function '" + funcId + "' has been defined!");
    for (auto param:params){
        string paramName;
        aA_type type;
        if (param->kind==A_varDeclType::A_varDeclScalarKind){
            paramName=*param->u.declScalar->id;
            type=param->u.declScalar->type;
        } else if (param->kind==A_varDeclType::A_varDeclArrayKind){
            paramName=*param->u.declArray->id;
            type=param->u.declArray->type;
            if (param->u.declArray->len<=0)
                error_print(out,param->pos,"Array length must be positive!");
        }
        if (!checkType(type))
            error_print(out,type->pos,"Function param type undefined!");
        if (paramSet.find(paramName)!=paramSet.end())
            error_print(out,param->pos,"Param id cannot repeat!");
        paramSet.insert(paramName);
    }
    // 如果已声明，检查paramlist和返回值类型是否与声明相同
    if (func2Param.find(funcId)!=func2Param.end()){
        vector<aA_varDecl> paramDecl=*func2Param[funcId];
        vector<aA_varDecl> paramDef=fd->fnDecl->paramDecl->varDecls;
        if (paramDecl.size()!=paramDef.size())
            error_print(out,fd->fnDecl->pos,"function definition of '" + funcId + "' has a different number of params from its declaration.");
        for (int i=0;i<paramDecl.size();i++){
            if (paramDecl[i]->kind!=paramDef[i]->kind)
                error_print(out,paramDef[i]->pos,"Param kind not same");
            if (paramDecl[i]->kind==A_varDeclType::A_varDeclScalarKind){
                if (*paramDecl[i]->u.declScalar->id!=*paramDef[i]->u.declScalar->id ||
                    !compareType(paramDecl[i]->u.declScalar->type,paramDef[i]->u.declScalar->type))
                    error_print(out,paramDef[i]->pos,"the param '" + *paramDef[i]->u.declScalar->id + "' of function '" + funcId + "' doesn't match its declaration.");
            } else if (paramDecl[i]->kind==A_varDeclType::A_varDeclArrayKind){
                if (*paramDecl[i]->u.declArray->id!=*paramDef[i]->u.declArray->id ||
                    paramDecl[i]->u.declArray->len!=paramDef[i]->u.declArray->len ||
                    !compareType(paramDecl[i]->u.declArray->type,paramDef[i]->u.declArray->type))
                    error_print(out,paramDef[i]->pos,"the param '" + *paramDef[i]->u.declArray->id + "' of function '" + funcId + "' doesn't match its declaration.");
            }
        }

        aA_type returnType = func2returnType[funcId]->type;
        if (!compareType(returnType, fd->fnDecl->type))
            error_print(out, fd->fnDecl->type->pos, "the return value type of function '" + funcId + "' doesn't match its declaration.");
    } else {
        funcDef2Param[funcId]=&fd->fnDecl->paramDecl->varDecls;
        TypeKind* returnType=new TypeKind();
        returnType->kind=A_kind::A_scalarKind;
        returnType->type=fd->fnDecl->type;
        func2returnType[funcId]=returnType;
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
    for (auto paramDecl:fd->fnDecl->paramDecl->varDecls){
        TypeKind* type=new TypeKind();
        if (paramDecl->kind==A_varDeclType::A_varDeclScalarKind){
            type->kind=A_kind::A_scalarKind;
            type->type=paramDecl->u.declScalar->type;
            funcparam_token2Type[*paramDecl->u.declScalar->id]=type;
        } else if (paramDecl->kind==A_varDeclType::A_varDeclArrayKind){
            type->kind=A_kind::A_arrayKind;
            type->length=paramDecl->u.declArray->len;
            type->type=paramDecl->u.declArray->type;
            funcparam_token2Type[*paramDecl->u.declArray->id]=type;
        }
    }
    vector<string> local_var_ids;
    stk.push(&local_var_ids);
    for (auto stmt:fd->stmts){
        check_CodeblockStmt(out,stmt,fd->fnDecl->type);
    }
    erase_local_vars(local_var_ids);
    stk.pop();
    funcparam_token2Type.clear();
    return;
}


void check_CodeblockStmt(std::ostream* out, aA_codeBlockStmt cs, aA_type returnType){
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
        check_IfStmt(out, cs->u.ifStmt, returnType);
        break;
    case A_codeBlockStmtType::A_whileStmtKind:
        check_WhileStmt(out, cs->u.whileStmt, returnType);
        break;
    case A_codeBlockStmtType::A_callStmtKind:
        check_CallStmt(out, cs->u.callStmt);
        break;
    case A_codeBlockStmtType::A_returnStmtKind:
        check_ReturnStmt(out, cs->u.returnStmt, returnType);
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
    TypeKind* left_type;
    switch (as->leftVal->kind)
    {
        case A_leftValType::A_varValKind:{
            /* write your code here */
            string left_id = *as->leftVal->u.id;
            left_type = getTokenType(left_id);
            if (left_type == nullptr)
                error_print(out, as->leftVal->pos, "the varible '" + left_id + "' is not declared.");
            if (left_type->kind == A_kind::A_arrayKind)
                error_print(out, as->leftVal->pos, "the leftVal cannot be an array.");
        }
            break;
        case A_leftValType::A_arrValKind:{
            /* write your code here */
            aA_arrayExpr left_arr = as->leftVal->u.arrExpr;
            check_ArrayExpr(out, left_arr);
            left_type = new TypeKind();
            memcpy(left_type, getTokenType(*left_arr->arr), sizeof(TypeKind));
            left_type->kind = A_kind::A_scalarKind;
        }
            break;
        case A_leftValType::A_memberValKind:{
            /* write your code here */
            aA_memberExpr left_mem = as->leftVal->u.memberExpr;
            left_type = check_MemberExpr(out, left_mem);
            if (left_type->kind == A_kind::A_arrayKind)
                error_print(out, as->pos, "the leftVal cannot be an array.");
        }
            break;
    }
    if (!check_val_type(out, as->rightVal, left_type))
        error_print(out, as->pos, "the types of leftVal and rightVal don't match.");
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
    TypeKind* array_type = getTokenType(*ae->arr);
    if (array_type == nullptr)
        error_print(out, ae->pos, "the varible '" + *ae->arr + "' is not declared.");
    if (array_type->kind == A_kind::A_scalarKind)
        error_print(out, ae->pos, "'" + *ae->arr + "' is not an array.");
    aA_indexExpr ie = ae->idx;
    if (ie->kind == A_indexExprKind::A_numIndexKind && ie->u.num >= array_type->length)
        error_print(out, ie->pos, "array index out of range.");
}


TypeKind* check_MemberExpr(std::ostream* out, aA_memberExpr me){
    // check if the member exists and return the type of the member
    // you may need to check if the type of this expression matches with its 
    // leftvalue or rightvalue, so return its aA_type would be a good way. Feel 
    // free to change the design pattern if you need.
    if(!me)
        return nullptr;
    string tokenId=*me->structId;
    TypeKind* type=getTokenType(tokenId);
    if (type == nullptr)
        error_print(out, me->pos, "the varible '" + *me->structId + "' is not declared.");
    if (type->kind==A_kind::A_arrayKind || type->type->type==A_dataType::A_nativeTypeKind)
        error_print(out, me->pos, "'" + *me->structId + "' is not a struct.");
    vector<aA_varDecl> members=*struct2Members[*type->type->u.structType];
    for (auto mem:members){
        string memId;
        TypeKind* memType=new TypeKind();
        if (mem->kind==A_varDeclType::A_varDeclScalarKind){
            memId=*mem->u.declScalar->id;
            memType->kind=A_kind::A_scalarKind;
            memType->type=mem->u.declScalar->type;
        }
        if (mem->kind==A_varDeclType::A_varDeclArrayKind){
            memId=*mem->u.declArray->id;
            memType->kind=A_kind::A_arrayKind;
            memType->length=mem->u.declArray->len;
            memType->type=mem->u.declArray->type;
        }
        if (*me->memberId == memId)
            return memType;
        delete memType;
    }
    error_print(out,me->pos,"struct '" + *me->structId + "' doesn't have a member named '" + *me->memberId + "'.");
    return nullptr;
}


void check_IfStmt(std::ostream* out, aA_ifStmt is, aA_type returnType){
    if(!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    vector<string> local_var_ids;
    stk.push(&local_var_ids);
    for(aA_codeBlockStmt s : is->ifStmts){
        check_CodeblockStmt(out, s, returnType);
    }
    erase_local_vars(local_var_ids);
    local_var_ids.clear();
    for(aA_codeBlockStmt s : is->elseStmts){
        check_CodeblockStmt(out, s, returnType);
    }
    erase_local_vars(local_var_ids);
    stk.pop();
    return;
}

TypeKind* create_IntScalar_TypeKind(){
    TypeKind* type = new TypeKind();
    type->kind == A_kind::A_scalarKind;
    type->type = new aA_type_();
    type->type->type = A_dataType::A_nativeTypeKind;
    type->type->u.nativeType = A_nativeType::A_intTypeKind;
    return type;
}

TypeKind* check_RightVal(std::ostream* out, aA_rightVal rv){
    if (!rv)
        return nullptr;
    switch (rv->kind) {
        case A_rightValType::A_boolExprValKind:{
            check_BoolExpr(out, rv->u.boolExpr);
            return create_IntScalar_TypeKind();
        }
            break;
        case A_rightValType::A_arithExprValKind:{
            return check_ArithExpr(out, rv->u.arithExpr);
        }
            break;
    }
    return nullptr;
}

void check_BoolExpr(std::ostream* out, aA_boolExpr be){
    if(!be)
        return;
    switch (be->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:{
        /* write your code here */
        check_BoolExpr(out, be->u.boolBiOpExpr->left);
        check_BoolExpr(out, be->u.boolBiOpExpr->right);
    }
        break;
    case A_boolExprType::A_boolUnitKind:
        check_BoolUnit(out, be->u.boolUnit);
        break;
    default:
        break;
    }
    return;
}

void check_CompOperand(std::ostream* out, aA_exprUnit eu){
    if (!eu)
        return;
    TypeKind* type = check_ExprUnit(out, eu);
    if (type->kind != A_kind::A_scalarKind)
        error_print(out, eu->pos, "the operand of compExpr must be a scalar.");
    if (type->type == nullptr)
        return;
    if (type->type->type != A_dataType::A_nativeTypeKind)
        error_print(out, eu->pos, "the operand of compExpr must have a native type.");
}

void check_BoolUnit(std::ostream* out, aA_boolUnit bu){
    if(!bu)
        return;
    switch (bu->kind)
    {
        case A_boolUnitType::A_comOpExprKind:{
            /* write your code here */
            check_CompOperand(out, bu->u.comExpr->left);
            check_CompOperand(out, bu->u.comExpr->right);
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

void check_ArithOperand(std::ostream* out, aA_arithExpr ae){
    if (!ae)
        return;
    TypeKind* type = check_ArithExpr(out, ae);
    if (type->kind != A_kind::A_scalarKind)
        error_print(out, ae->pos, "the operand of arithExpr must be a scalar.");
    if (type->type == nullptr)
        return;
    if (type->type->type != A_dataType::A_nativeTypeKind)
        error_print(out, ae->pos, "the operand of arithExpr must have a native type.");
}

TypeKind* check_ArithExpr(std::ostream* out, aA_arithExpr ae){
    if (!ae)
        return nullptr;
    switch (ae->kind)
    {
        case A_arithExprType::A_arithBiOpExprKind:{
            /* write your code here */
            check_ArithOperand(out, ae->u.arithBiOpExpr->left);
            check_ArithOperand(out, ae->u.arithBiOpExpr->right);
            return create_IntScalar_TypeKind();
        }
            break;
        case A_arithExprType::A_exprUnitKind:
            return check_ExprUnit(out, ae->u.exprUnit);
            break;
        default:
            break;
    }
    return nullptr;
}

TypeKind* check_ExprUnit(std::ostream* out, aA_exprUnit eu){
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its 
    // leftvalue or rightvalue, so return its aA_type would be a good way. 
    // Feel free to change the design pattern if you need.
    if(!eu)
        return nullptr;
    TypeKind* ret;
    switch (eu->kind)
    {
        case A_exprUnitType::A_idExprKind:{
            /* write your code here */
            ret = getTokenType(*eu->u.id);
            if (ret == nullptr)
                error_print(out, eu->pos, "the varible '" + *eu->u.id + "' is not declared.");
        }
            break;
        case A_exprUnitType::A_numExprKind:{
            /* write your code here */
            ret = create_IntScalar_TypeKind();
        }
            break;
        case A_exprUnitType::A_fnCallKind:{
            /* write your code here */
            check_FuncCall(out, eu->u.callExpr);
            ret = func2returnType[*eu->u.callExpr->fn];
            if (ret->type == nullptr)
                error_print(out, eu->pos, "function '" + *eu->u.callExpr->fn + "' does not return a value.");
        }
            break;
        case A_exprUnitType::A_arrayExprKind:{
            /* write your code here */
            check_ArrayExpr(out, eu->u.arrayExpr);
            ret = new TypeKind();
            memcpy(ret, getTokenType(*eu->u.arrayExpr->arr), sizeof(TypeKind));
            ret->kind = A_kind::A_scalarKind;
        }
            break;
        case A_exprUnitType::A_memberExprKind:{
            /* write your code here */
            ret = check_MemberExpr(out, eu->u.memberExpr);
        }
            break;
        case A_exprUnitType::A_arithExprKind:{
            /* write your code here */
            ret = check_ArithExpr(out, eu->u.arithExpr);
        }
            break;
        case A_exprUnitType::A_arithUExprKind:{
            /* write your code here */
            ret = check_ExprUnit(out, eu->u.arithUExpr->expr);
            if (ret->kind != A_kind::A_scalarKind || ret->type->type != A_dataType::A_nativeTypeKind)
                error_print(out, eu->pos, "- can only act on variables of nativeType.");
        }
            break;
    }
    return ret;
}


void check_FuncCall(std::ostream* out, aA_fnCall fc){
    if(!fc)
        return;
    vector<aA_varDecl> varDeclList;
    if (func2Param.find(*fc->fn)!=func2Param.end()){
        varDeclList=*func2Param[*fc->fn];
    } else if (funcDef2Param.find(*fc->fn)!=funcDef2Param.end()){
        varDeclList=*funcDef2Param[*fc->fn];
    }else{
        error_print(out,fc->pos,"the function '" + *fc->fn + "' is not declared");
    }
    if (varDeclList.size()!=fc->vals.size())
        error_print(out,fc->pos,"param number not equal!");
    for (int i=0;i<varDeclList.size();i++){
        TypeKind* type=new TypeKind();
        if (varDeclList[i]->kind==A_varDeclType::A_varDeclScalarKind){
            type->kind=A_kind::A_scalarKind;
            type->type=varDeclList[i]->u.declScalar->type;
            if (!check_val_type(out,fc->vals[i],type))
                error_print(out,fc->vals[i]->pos,"param type not equal!");
        } else if(varDeclList[i]->kind==A_varDeclType::A_varDeclArrayKind){
            type->kind=A_kind::A_arrayKind;
            type->type=varDeclList[i]->u.declArray->type;
            type->length=varDeclList[i]->u.declArray->len;
            if (!check_val_type(out,fc->vals[i],type))
                error_print(out,fc->vals[i]->pos,"array param type not equal");
        }
    }
    return ;
}


void check_WhileStmt(std::ostream* out, aA_whileStmt ws, aA_type returnType){
    if(!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    vector<string> local_var_ids;
    stk.push(&local_var_ids);
    for(aA_codeBlockStmt s : ws->whileStmts){
        check_CodeblockStmt(out, s, returnType);
    }
    erase_local_vars(local_var_ids);
    stk.pop();
    return;
}


void check_CallStmt(std::ostream* out, aA_callStmt cs){
    if(!cs)
        return;
    check_FuncCall(out, cs->fnCall);
    return;
}


void check_ReturnStmt(std::ostream* out, aA_returnStmt rs, aA_type returnType){
    if(!rs)
        return;
    TypeKind* rv_type = check_RightVal(out, rs->retVal);
    if (!returnType){
        if (rv_type)
            error_print(out, rs->retVal->pos, "the function doesn't return a value.");
    } else {
        if (!rv_type)
            error_print(out, rs->pos, "the function should return a value.");
        else {
            if (rv_type->kind != A_kind::A_scalarKind)
                error_print(out, rs->retVal->pos, "the return value must be a scalar.");
            if (!check_assign_type(returnType, rv_type->type))
                error_print(out, rs->retVal->pos, "the return value type doesn't match the declaration.");
        }
    }
    return;
}

