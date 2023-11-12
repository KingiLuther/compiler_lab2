#include "TypeCheck.h"

// maps to store the type information. Feel free to design new data structures if you need.
typeMap g_token2Type; // global token ids to type
typeMap funcparam_token2Type; // func params token ids to type, temp variables
typeMap func2retType;

paramMemberMap func2Param; // func2Params: func name -> func param declarations, global storage
paramMemberMap struct2Members; // struct name -> sturct param declarations

std::unordered_map<std::string, std::string> funcDecl;

int cur = 1;

std::string cur_func_name = "";


void clearCur()
{
    vector<string> allDeleteNames;
    for (auto i : g_token2Type)
    {
        if (i.second->cur == cur)
        {
            allDeleteNames.push_back(i.first);
        }
    }
    for (auto i : allDeleteNames)
        g_token2Type.erase(i);

    cur--;
}

// private util functions. You can use these functions to help you debug.
void error_print(std::ostream *out, A_pos p, string info)
{
    *out << "Typecheck error in line " << p->line << ", col " << (p->col + 1)<< ": " << info << std::endl;
    exit(0);
}

void print_token_map(typeMap *map)
{
    for (auto it = map->begin(); it != map->end(); it++)
    {
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
void check_Prog(std::ostream *out, aA_program p)
{
    /*
    Write your code here.

    Hint:
    1. Design the order of checking the program elements to meet the requirements that funtion declaration and global variable declaration can be used anywhere in the program.

    2. Many types of statements indeed collapse to some same units, so a good abstract design will help you reduce the amount of your code.
    */
    // p is the root of AST tree.
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programVarDeclStmtKind:
        {
            check_VarDeclStmt(out, ele->u.varDeclStmt);
        }
        break;
        case A_programStructDefKind:
        {
            check_StructDef(out, ele->u.structDef);
        }
        break;
        case A_programFnDeclStmtKind:
        {
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
        }
        break;
        case A_programFnDefKind:
        {
            check_FnDef(out, ele->u.fnDef);
        }
        break;
        default:
        break;
        }

    }
    (*out) << "Typecheck passed!" << std::endl;
    return;
}

void check_multiDeclaration(std::ostream *out, string name, A_pos pos)
{
    if (g_token2Type.find(name) != g_token2Type.end())
    {
        error_print(out, pos, name + " dplicates with global variable");
    }
    if (struct2Members.find(name) != struct2Members.end())
    {
        error_print(out, pos, name + " dplicates with struct variable!");
    }
    if (funcDecl.find(name) != funcDecl.end())
    {
        error_print(out, pos, name + " dplicates with func name!");
    }
    if (funcparam_token2Type.find(name) != funcparam_token2Type.end())
    {
        error_print(out, pos, "This name " + name + " has been declared in func variable list!");
    }
}

void check_VarDeclScalar(std::ostream *out, aA_varDeclScalar varDeclScalar)
{
    if (!varDeclScalar)
        return;
    string name = *(varDeclScalar->id);
    check_multiDeclaration(out, name, varDeclScalar->pos);
    varDeclScalar->type->is_array = false;
    varDeclScalar->type->cur = cur;
    g_token2Type[name] = varDeclScalar->type;
}

void check_VarDeclArray(std::ostream *out, aA_varDeclArray varDeclArray)
{
    if (!varDeclArray)
        return;
    string name = *(varDeclArray->id);
    check_multiDeclaration(out, name, varDeclArray->pos);
    varDeclArray->type->is_array = true;
    varDeclArray->type->len = varDeclArray->len;
    varDeclArray->type->cur = cur;
    g_token2Type[name] = varDeclArray->type;
}

void check_varDecl(std::ostream *out, aA_varDecl varDecl)
{
    check_VarDeclValid(out, varDecl);
    switch (varDecl->kind)
    {
    case A_varDeclScalarKind:
    {
        check_VarDeclScalar(out, varDecl->u.declScalar);
        break;
    }
    case A_varDeclArrayKind:
    {
        check_VarDeclArray(out, varDecl->u.declArray);
        break;
    }
    }
}

aA_type getIntType(){
    aA_type intType = new aA_type_;
    intType->is_array = false;
    intType->type=A_dataType::A_nativeTypeKind;
    return intType;
}

aA_type check_arithBiopExpr(std::ostream * out, aA_arithBiOpExpr biopExpr){
    aA_type operand1Type = check_arithExprValValid(out,biopExpr->left);
    aA_type operand2Type = check_arithExprValValid(out,biopExpr->right);
    if(check_aATypeSame(getIntType(),operand1Type) == false)
        error_print(out,operand1Type->pos,"ArithType 1 is not int!");
    if (check_aATypeSame(getIntType(), operand2Type) == false)
        error_print(out, operand2Type->pos, "ArithType 2 is not int!");
    return operand1Type;
}

aA_type check_arithExprValValid(std::ostream *out, aA_arithExpr arithExpr)
{
    if(arithExpr == nullptr)
        return nullptr;
    switch (arithExpr->kind)
    {
    case (A_arithExprType::A_exprUnitKind):
    {
        return check_ExprUnit(out, arithExpr->u.exprUnit);
        break;
    }
    case (A_arithExprType::A_arithBiOpExprKind):
    {
        return check_arithBiopExpr(out,arithExpr->u.arithBiOpExpr);
        break;
    }
    }
    return nullptr;
}

aA_type check_rightValValid(std::ostream *out, aA_rightVal rightVal)
{
    if(rightVal == nullptr)
        return nullptr;
    if(rightVal->kind == A_rightValType::A_arithExprValKind){
        return check_arithExprValValid(out, rightVal->u.arithExpr);
    }
    return nullptr;
}

void check_varDefScalar(std::ostream *out, aA_varDefScalar varDefScalar)
{
    if (!varDefScalar)
        return;
    string name = *(varDefScalar->id);
    check_multiDeclaration(out, name, varDefScalar->pos);
    aA_type rightValType = check_rightValValid(out, varDefScalar->val);
    aA_type leftValType = varDefScalar->type;
    if (rightValType->type != leftValType->type)
    {
        error_print(out, rightValType->pos, "Right Value type incompatible with left type");
    }
    else if (rightValType->type == A_dataType::A_structTypeKind)
    {
        string rightValStructName = *(rightValType->u.structType);
        string leftValStructName = *(leftValType->u.structType);
        if (rightValStructName != leftValStructName)
        {
            error_print(out, rightValType->pos, "Right Value struct incompatible with left struct");
        }
    }
    varDefScalar->type->is_array = false;
    varDefScalar->type->cur = cur;
    g_token2Type[*(varDefScalar->id)] = varDefScalar->type;
}


void check_varDefArray(std::ostream *out, aA_varDefArray varDefArray)
{
    if (!varDefArray)
        return;
    check_multiDeclaration(out, *(varDefArray->id), varDefArray->pos);
    if (varDefArray->len < varDefArray->vals.size())
        error_print(out, varDefArray->pos, "Too many parameters for a var def array!");
    for (int i = 0; i < varDefArray->vals.size(); i++)
    {
        aA_type rightValType = check_rightValValid(out, varDefArray->vals[i]);
        if (rightValType == nullptr)
            error_print(out, rightValType->pos, "Right Value not valid!");
        if (rightValType->is_array == true)
            error_print(out, rightValType->pos, "Right value is an array!");
        aA_type leftValType = varDefArray->type;
        if (rightValType->type != leftValType->type)
            error_print(out, rightValType->pos, "Right Value type incompatible with left type");
        if (rightValType->type == A_dataType::A_structTypeKind)
        {
            string rightValStructName = *(rightValType->u.structType);
            string leftValStructName = *(leftValType->u.structType);
            if (rightValStructName != leftValStructName)
                error_print(out, rightValType->pos, "Right Value struct incompatible with left struct");
        }
    }
    varDefArray->type->is_array = true;
    varDefArray->type->len = varDefArray->len;
    varDefArray->type->cur = cur;
    g_token2Type[*(varDefArray->id)] = varDefArray->type;
}

void check_varDef(std::ostream *out, aA_varDef vd)
{
    check_VarDefValid(out, vd);
    switch (vd->kind)
    {
    case A_varDefScalarKind:
    {
        check_varDefScalar(out, vd->u.defScalar);
        break;
    }
    case A_varDefArrayKind:
    {
        check_varDefArray(out, vd->u.defArray);
        break;
    };
    }
}

void check_VarDeclStmt(std::ostream *out, aA_varDeclStmt vd)
{
    if (!vd)
        return;
    if (vd->kind == A_varDeclStmtType::A_varDeclKind)
    {
        check_varDecl(out, vd->u.varDecl);
    }

    else if (vd->kind == A_varDeclStmtType::A_varDefKind)
    {
        check_varDef(out, vd->u.varDef);
    }
    return;
}

string getVarDeclName(aA_varDecl x)
{
    if(x == nullptr)
        return nullptr;
    switch (x->kind)
    {

        case (A_varDeclType::A_varDeclArrayKind):
        {
            return *(x->u.declArray->id);
        }
        break;
        case (A_varDeclType::A_varDeclScalarKind):
        {
            return *(x->u.declScalar->id);
        }
        break;
    }
    return "";
}

string getATypeName(aA_type type)
{
    switch (type->type)
    {
    case (A_dataType::A_nativeTypeKind):
    {
        return "int";
    }
    case (A_dataType::A_structTypeKind):
    {
        return *(type->u.structType);
    }
    }
    return "nulltype";
}

aA_type getVarDeclType(aA_varDecl x)
{
    aA_type ret = nullptr;
    switch (x->kind)
    {
    case (A_varDeclType::A_varDeclScalarKind):
    {
        x->u.declScalar->type->is_array = false;
        return x->u.declScalar->type;
    }
    break;
    case (A_varDeclType::A_varDeclArrayKind):
    {
        x->u.declArray->type->is_array = true;
        return x->u.declArray->type;
    }
    break;
    }
    return ret;
}

aA_type getVarDefType(aA_varDef x)
{
    if(x == nullptr)
        return nullptr;
    aA_type ret = nullptr;
    switch (x->kind)
    {
        case (A_varDefType::A_varDefScalarKind):
        {
            x->u.defScalar->type->is_array=false;
            return x->u.defScalar->type;
        }
        break;
        case (A_varDefType::A_varDefArrayKind):
        {
            x->u.defArray->type->is_array = true;
            return x->u.defArray->type;
        }
        break;
    }
    return ret;
}

void check_typeValid(std::ostream *out, aA_type varType)
{
    if (!varType)
        return;
    string name = getATypeName(varType);
    if (name != "int" && struct2Members.find(name) == struct2Members.end())
        error_print(out, varType->pos, "not int!");
}

void check_VarDeclValid(std::ostream *out, aA_varDecl varDecl)
{
    aA_type varType = getVarDeclType(varDecl);
    check_typeValid(out, varType);
}

void check_VarDefValid(std::ostream *out, aA_varDef varDef)
{
    aA_type varType = getVarDefType(varDef);
    check_typeValid(out, varType);
}

void check_MultiParams(std::ostream *out, vector<aA_varDecl> varDeclList)
{
    vector<string> paramNames;
    for (auto varDecl : varDeclList)
    {
        check_VarDeclValid(out, varDecl);
        string name = getVarDeclName(varDecl);
        for (auto paramName : paramNames)
        {
            if (name == paramName)
            {
                error_print(out, varDecl->pos, "dplicate variable name!");
            }
        }
        paramNames.push_back(name);
    }
}

void check_StructDef(std::ostream *out, aA_structDef sd)
{
    if (!sd)
        return;
    string name = *(sd->id);
    check_multiDeclaration(out, *(sd->id), sd->pos);
    check_MultiParams(out, sd->varDecls);
    struct2Members[name] = sd->varDecls;
    return;
}

void check_FnDecl(std::ostream *out, aA_fnDecl fd)
{
    // Example:
    //      fn main(a:int, b:int)->int
    if (!fd)
        return;
    string name = *(fd->id);
    check_MultiParams(out, fd->paramDecl->varDecls);
    check_typeValid(out, fd->type);

    return;
}

void check_FnDeclStmt(std::ostream *out, aA_fnDeclStmt fd)
{
    // Example:
    //      fn main(a:int, b:int)->int;
    if (!fd)
        return;
    string name = *(fd->fnDecl->id);
    check_multiDeclaration(out, name, fd->pos);
    check_FnDecl(out, fd->fnDecl);
    func2Param[name] = fd->fnDecl->paramDecl->varDecls;
    funcDecl[name] = "func_decl";
    func2retType[name] = fd->fnDecl->type;
    return;
}

bool check_aATypeSame(aA_type a, aA_type b)
{
    if(a->is_bool == true && b->is_bool == true)
        return true;
    else if(a->is_bool == true || b->is_bool == true)
        return false;
    else
    {
        if (a->is_array == b->is_array)
        {
            if (a->type == b->type)
            {
                if (a->type == A_dataType::A_nativeTypeKind)
                {
                    return true;
                }
                else
                {
                    if (*(a->u.structType) == *(b->u.structType))
                    {
                        return true;
                    }
                    else
                        return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }

}

void check_FnDef(std::ostream *out, aA_fnDef fd)
{
    // Example:
    //      fn main(a:int, b:int)->int{
    //          let c:int;
    //          c = a + b;
    //          return c;
    //      }
    if (!fd)
        return;
    string name = *(fd->fnDecl->id);
    if (funcDecl.find(name) == funcDecl.end())
    {
        check_multiDeclaration(out, name, fd->pos);
        check_FnDecl(out, fd->fnDecl);
        func2Param[name] = fd->fnDecl->paramDecl->varDecls;
        funcDecl[name] = "func_def";
        func2retType[name] = fd->fnDecl->type;
    }
    else if (funcDecl[name] == "func_decl")
    {
        check_FnDecl(out, fd->fnDecl);
        auto curList = fd->fnDecl->paramDecl->varDecls;
        auto prevList = func2Param[name];
        for (int i = 0; i < curList.size(); i++)
        {
            auto curNode = getVarDeclType(curList[i]);
            auto prevNode = getVarDeclType(prevList[i]);
            if (getVarDeclName(curList[i]) != getVarDeclName(prevList[i]))
            {
                error_print(out, curNode->pos, "function definition doesn't match the declaration");
            }
            if (check_aATypeSame(curNode, prevNode) == false)
            {
                error_print(out, curNode->pos, "function definition doesn't match the declaration");
            }
        }
        auto curReturnType = fd->fnDecl->type;
        auto prevReturnType = func2retType[name];
        if (check_aATypeSame(curReturnType, prevReturnType) == false)
        {
            error_print(out, curReturnType->pos, "function definition doesn't match the declaration");
        }
        funcDecl[name] = "func_def";
        for (auto i : fd->fnDecl->paramDecl->varDecls)
        {
            func2Param[name].push_back(i);
        }
    }
    else if (funcDecl[name] == "func_def")
    {
        error_print(out, fd->pos, "Multiple function definition!");
    }

    vector<aA_varDecl> varDeclVec = func2Param[name];
    for (auto i : varDeclVec)
    {
        aA_type type = getVarDeclType(i);
        string s = getVarDeclName(i);
        funcparam_token2Type[s] = type;
    }
    cur++;
    cur_func_name = name;
    for (auto stmt : fd->stmts)
    {
        check_CodeblockStmt(out, stmt);
    }
    clearCur();
    funcparam_token2Type.clear();
    cur_func_name="";
    return;
}

void check_CodeblockStmt(std::ostream *out, aA_codeBlockStmt cs)
{
    if (!cs)
        return;
    switch (cs->kind)
    {
    case A_codeBlockStmtType::A_varDeclStmtKind:
        check_VarDeclStmt(out, cs->u.varDeclStmt);
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

aA_type idToType(std::ostream * out,A_pos pos,string id)
{
    if (funcparam_token2Type.find(id) != funcparam_token2Type.end())
        return funcparam_token2Type[id];
    else if (g_token2Type.find(id) != g_token2Type.end())
        return g_token2Type[id];
    else if(func2Param.find(id)!= func2Param.end())
        error_print(out,pos,"cannot assign a value to function");
    return nullptr;
}

aA_type check_leftValValid(std::ostream *out, aA_leftVal leftVal)
{
    switch (leftVal->kind){
        case (A_leftValType::A_varValKind):
        {
            string name = *(leftVal->u.id);
            aA_type leftValType = idToType(out,leftVal->pos,name);
            if (leftValType == nullptr)
                error_print(out, leftVal->pos, "Left Val here is not declared!");
            return leftValType;
        }
        break;
        case (A_leftValType::A_arrValKind):
        {
            return check_ArrayExpr(out,leftVal->u.arrExpr);
        }
        break;
        case (A_leftValType::A_memberValKind):
        {
            return check_MemberExpr(out,leftVal->u.memberExpr);
        }
        break;
    }
    return nullptr;
}

void check_AssignStmt(std::ostream *out, aA_assignStmt as)
{
    if (!as)
        return;
    aA_type rightValType = check_rightValValid(out, as->rightVal);
    aA_type leftValType = check_leftValValid(out, as->leftVal);
    if (check_aATypeSame(leftValType, rightValType) != true)
        error_print(out, as->pos, "The type of left val and right val doesn't match");
    return;
}

aA_type check_ArrayExpr(std::ostream *out, aA_arrayExpr ae)
{
    /*
    Example:
        a[1] = 0;
    Hint:
        check the validity of the array index
    */
    if (!ae)
        return nullptr;
    string arrName = *(ae->arr);
    aA_type arrType = idToType(out,ae->pos,arrName);
    if (arrType == nullptr)
        error_print(out, ae->pos, "Array name is not declared!");
    if (arrType->is_array == false)
        error_print(out, ae->pos, "This variable " + arrName + " is a scalar type!");
    switch (ae->idx->kind){
        case (A_indexExprKind::A_numIndexKind):
        {
            aA_type retType = new aA_type_;
            retType->cur = arrType->cur;
            retType->is_array = false;
            retType->pos = arrType->pos;
            retType->type = arrType->type;
            retType->u = arrType->u;
            return retType;
        }
        break;
        case (A_indexExprKind::A_idIndexKind):
        {
            string bTypeName = *(ae->idx->u.id);
            aA_type bType = idToType(out, ae->idx->pos ,bTypeName);
            if (bType == nullptr)
                error_print(out, ae->idx->pos, "The name of the val in array here is not declared!");
            if (bType->is_array == true)
                error_print(out, ae->idx->pos, "The name of the val in array here is an array!");
            if (bType->type == A_dataType::A_structTypeKind)
                error_print(out, ae->idx->pos, "The name of the val in array here is a struct!");
            aA_type retType = new aA_type_;
            retType->cur = arrType->cur;
            retType->is_array = false;
            retType->pos = arrType->pos;
            retType->type = arrType->type;
            retType->u = arrType->u;
            return retType;
        }

    }
    return nullptr;
}

aA_type check_MemberExpr(std::ostream *out, aA_memberExpr me)
{
    // check if the member exists and return the type of the member
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way. Feel
    // free to change the design pattern if you need.
    if (!me)
        return nullptr;
    /*
        Example:
            a.b
    */
    string structVarName = *(me->structId);
    aA_type structVarType = idToType(out,me->pos ,structVarName);
    if (structVarType == nullptr)
        error_print(out, me->pos, "The variable " + structVarName + " defined here is not declared!");
    if (structVarType->is_array == true)
        error_print(out, me->pos, "The variable " + structVarName + " used here is an array!");
    if (structVarType->type == A_dataType::A_nativeTypeKind)
        error_print(out, me->pos, "The variable " + structVarName + " used here is a int!");
    string innerVarName = *(me->memberId);
    vector<aA_varDecl> varDeclVec = struct2Members[*(structVarType->u.structType)];
    aA_type matchType = nullptr;
    for (auto varDecl : varDeclVec)
    {
        string varDeclName = getVarDeclName(varDecl);
        if (varDeclName == innerVarName){
            matchType = getVarDeclType(varDecl);
        }

    }
    if (matchType == nullptr)
        error_print(out, me->pos, "The inner variable " + innerVarName + " used in this struct is not defined!");
    return matchType;
}

void check_IfStmt(std::ostream *out, aA_ifStmt is)
{
    if (!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    cur++;
    for (aA_codeBlockStmt s : is->ifStmts)
        check_CodeblockStmt(out, s);
    clearCur();

    cur++;
    for (aA_codeBlockStmt s : is->elseStmts)
        check_CodeblockStmt(out, s);
    clearCur();

    return;
}

aA_type getBoolType(){
    aA_type type = new aA_type_;
    type->is_bool=true;
    type->is_array=false;
    return type;
}

aA_type check_BoolExpr(std::ostream *out, aA_boolExpr be)
{
    if (!be)
        return nullptr;
    switch (be->kind)
    {
        case A_boolExprType::A_boolBiOpExprKind:{
            aA_type type1 = check_BoolExpr(out,be->u.boolBiOpExpr->left);
            aA_type type2 = check_BoolExpr(out,be->u.boolBiOpExpr->right);
            if(check_aATypeSame(getBoolType(),type1) == false)
                error_print(out,be->pos,"left val type and bool not same!");
            if(check_aATypeSame(getBoolType(), type2) == false)
                error_print(out,be->pos,"right val type and bool not same");
            aA_type retType = new aA_type_;
            retType->is_array=false;
            retType->is_bool=true;
            retType->pos=be->pos;
            return retType;
        }
        break;
        case A_boolExprType::A_boolUnitKind:{
            aA_type type1 = check_BoolUnit(out, be->u.boolUnit);
            if(check_aATypeSame(getBoolType(), type1) == false)
                error_print(out, be->pos, "val type and bool not same");
            return type1;
        }
        break;

        default:
            break;
    }
    return nullptr;
}

aA_type check_BoolUnit(std::ostream *out, aA_boolUnit bu)
{
    if (!bu)
        return nullptr;
    switch (bu->kind)
    {
    case A_boolUnitType::A_comOpExprKind:
    {
        aA_type exprUnit1 = check_ExprUnit(out,bu->u.comExpr->left);
        aA_type exprUnit2 = check_ExprUnit(out,bu->u.comExpr->right);
        if(check_aATypeSame(exprUnit1,getIntType()) == false)
            error_print(out,bu->u.comExpr->left->pos,"Left expr type not int!");
        if(check_aATypeSame(exprUnit2,getIntType()) == false)
            error_print(out, bu->u.comExpr->right->pos, "Right expr type not int!");
        aA_type retType = new aA_type_;
        retType->is_array = false;
        retType->is_bool = true;
        retType->pos = bu->pos;
        return retType;
    }
    break;
    case A_boolUnitType::A_boolExprKind:
    {
        return check_BoolExpr(out,bu->u.boolExpr);
    }
        break;
    case A_boolUnitType::A_boolUOpExprKind:{
        return check_BoolUnit(out,bu->u.boolUOpExpr->cond);
        break;
    }
    default:
        break;
    }
    return nullptr;
}

aA_type check_ExprUnit(std::ostream *out, aA_exprUnit eu)
{
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way.
    // Feel free to change the design pattern if you need.
    if (!eu)
        return nullptr;
    aA_type ret = nullptr;
    switch (eu->kind)
    {
    case A_exprUnitType::A_numExprKind:
    {
        ret = new aA_type_;
        ret->is_array = false;
        ret->pos = eu->pos;
        ret->type = A_dataType::A_nativeTypeKind;
        ret->u.nativeType = A_nativeType::A_intTypeKind;
        return ret;
    }
    break;
    case A_exprUnitType::A_idExprKind:
    {
        string name = *(eu->u.id);
        auto t = idToType(out,eu->pos,name);
        if (t == nullptr)
            error_print(out, eu->pos, "Var name " + name + " not found");
        return t;
    }
    break;

    case A_exprUnitType::A_fnCallKind:
    {
        aA_type fnRetType = check_FnCall(out,eu->u.callExpr);
        if(check_aATypeSame(getIntType(),fnRetType) == false){
            error_print(out,eu->pos, "The func return type is not compatible with expr Unit");
        }
        return fnRetType;
    }
    break;
    case A_exprUnitType::A_arrayExprKind:
    {
        return check_ArrayExpr(out,eu->u.arrayExpr);
    }
    break;
    case A_exprUnitType::A_memberExprKind:
    {
        return check_MemberExpr(out,eu->u.memberExpr);
    }
    break;
    case A_exprUnitType::A_arithExprKind:
    {
        return check_arithExprValValid(out,eu->u.arithExpr);
    }
    break;
    case A_exprUnitType::A_arithUExprKind:
    {
        return check_ExprUnit(out,eu->u.arithUExpr->expr);
    }
    break;
    }
    return ret;
}

aA_type check_FnCall(std::ostream *out, aA_fnCall fc)
{
    if (!fc)
        return nullptr;
    string fnName = *(fc->fn);
    if(func2retType.find(fnName)==func2retType.end())
        error_print(out,fc->pos,"Cannot find the corresponding function name "+ fnName);
    auto varDeclVec = func2Param[fnName];
    if(varDeclVec.size()!=fc->vals.size())
        error_print(out, fc->pos, "The fn Call stmt's parameters size not equal to the func declaration's in fn name "+fnName);
    for(int i = 0;i < varDeclVec.size();i++){
        auto varDecl = varDeclVec[i];
        auto rightVal = fc->vals[i];
        if(!check_aATypeSame(getVarDeclType(varDecl),check_rightValValid(out,rightVal))){
            error_print(out, fc->pos, "The " + std::to_string(i) + " th parameter in fnCall doesn't match the one in fn declaration in fn name" + fnName);
        }
    }
    return func2retType[fnName];
}

void check_WhileStmt(std::ostream *out, aA_whileStmt ws)
{
    if (!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    cur++;
    for (aA_codeBlockStmt s : ws->whileStmts)
    {
        check_CodeblockStmt(out, s);
    }
    clearCur();
    return;
}

void check_CallStmt(std::ostream *out, aA_callStmt cs)
{
    if (!cs)
        return;
    check_FnCall(out, cs->fnCall);
    return;
}

void check_ReturnStmt(std::ostream *out, aA_returnStmt rs)
{
    if (!rs)
        return;
    aA_type rightValType = check_rightValValid(out,rs->retVal);
    aA_type funcRetType = func2retType[cur_func_name];
    if(check_aATypeSame(funcRetType,rightValType) == false){
        error_print(out,rs->pos,"The ret value's type is incompatible with the func declarations's return type!");
    }
    return;
}