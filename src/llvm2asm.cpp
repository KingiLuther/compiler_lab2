#include "llvm_ir.h"
#include "asm_arm.h"
#include "temp.h"
#include "llvm2asm.h"

#include <queue>
#include <cassert>

using namespace std;
using namespace LLVMIR;
using namespace ASM;


static int stack_frame;
static bool alloc_frame = false;

static unordered_map<int, int> spOffsetMap;
static unordered_map<int, AS_relopkind> condMap;
static unordered_map<string, int> structLayout;

void structLayoutInit(vector<L_def*> &defs) {
    for (const auto &def : defs) {
        switch (def->kind) {
            case L_DefKind::SRT: {
                structLayout[def->u.SRT->name]=def->u.SRT->members.size()*4;
                break;
            }
            case L_DefKind::GLOBAL: {
                break;
            }
            case L_DefKind::FUNC: {
                break;
            }
        }
    }
}

void set_stack(L_func &func) {
    for (auto ir:(*func.blocks.begin())->instrs){
        if (ir->type==L_StmKind::T_ALLOCA){
            if (ir->u.ALLOCA->dst->kind==OperandKind::TEMP){
                if (ir->u.ALLOCA->dst->u.TEMP->type==TempType::INT_PTR){
                    int len = ir->u.ALLOCA->dst->u.TEMP->len>0 ? ir->u.ALLOCA->dst->u.TEMP->len : 1;
                    len = len*4;
                    spOffsetMap[ir->u.ALLOCA->dst->u.TEMP->num]=stack_frame;
                    stack_frame += len;
                } else if (ir->u.ALLOCA->dst->u.TEMP->type==TempType::STRUCT_PTR){
                    int len = ir->u.ALLOCA->dst->u.TEMP->len>0 ? ir->u.ALLOCA->dst->u.TEMP->len : 1;
                    len = len*structLayout[ir->u.ALLOCA->dst->u.TEMP->structname];
                    spOffsetMap[ir->u.ALLOCA->dst->u.TEMP->num]=stack_frame;
                    stack_frame += len;
                }
            }
        }
    }
}

void new_frame(list<AS_stm*> &as_list) {
    AS_reg* sp=new AS_reg(-1,-1);
    AS_reg* imm=new AS_reg(-3,stack_frame);
    as_list.push_back(AS_Binop(AS_binopkind::SUB_,sp,imm,sp));
}

void free_frame(list<AS_stm*> &as_list) {
    AS_reg* sp=new AS_reg(-1,-1);
    AS_reg* imm=new AS_reg(-3,stack_frame);
    as_list.push_back(AS_Binop(AS_binopkind::ADD_,sp,imm,sp));
}


void llvm2asmBinop(list<AS_stm*> &as_list, L_stm* binop_stm) {
    AS_reg* left;
    AS_reg* right;
    AS_reg* dst;
    AS_binopkind op;

    switch (binop_stm->u.BINOP->op) {
        case L_binopKind::T_plus: {
            op = AS_binopkind::ADD_;
            switch (binop_stm->u.BINOP->left->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x2: mov x2, #1
                    int instant = binop_stm->u.BINOP->left->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(2, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    left = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg directly: str x, ...
                    int src_num = binop_stm->u.BINOP->left->u.TEMP->num;
                    left = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }

            switch (binop_stm->u.BINOP->right->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // do not need to move the instant into reg, use #1 directly
                    int instant = binop_stm->u.BINOP->right->u.ICONST;
                    right = new AS_reg(-3, instant);
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg: str x, ...
                    int src_num = binop_stm->u.BINOP->right->u.TEMP->num;
                    right = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }

            break;
        }
        case L_binopKind::T_minus: {
            op=AS_binopkind::SUB_;
            switch (binop_stm->u.BINOP->left->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x2: mov x2, #1
                    int instant = binop_stm->u.BINOP->left->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(2, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    left = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg directly: str x, ...
                    int src_num = binop_stm->u.BINOP->left->u.TEMP->num;
                    left = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }

            switch (binop_stm->u.BINOP->right->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // do not need to move the instant into reg, use #1 directly
                    int instant = binop_stm->u.BINOP->right->u.ICONST;
                    right = new AS_reg(-3, instant);
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg: str x, ...
                    int src_num = binop_stm->u.BINOP->right->u.TEMP->num;
                    right = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }
            break;
        }
        case L_binopKind::T_mul: {
            op=AS_binopkind::MUL_;
            switch (binop_stm->u.BINOP->left->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x2: mov x2, #1
                    int instant = binop_stm->u.BINOP->left->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(2, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    left = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg directly: str x, ...
                    int src_num = binop_stm->u.BINOP->left->u.TEMP->num;
                    left = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }

            switch (binop_stm->u.BINOP->right->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x3: mov x3, #1
                    int instant = binop_stm->u.BINOP->right->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(3, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    right = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg: str x, ...
                    int src_num = binop_stm->u.BINOP->right->u.TEMP->num;
                    right = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }
            break;
        }
        case L_binopKind::T_div: {
            op=AS_binopkind::SDIV_;
            switch (binop_stm->u.BINOP->left->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x2: mov x2, #1
                    int instant = binop_stm->u.BINOP->left->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(2, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    left = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg directly: str x, ...
                    int src_num = binop_stm->u.BINOP->left->u.TEMP->num;
                    left = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }

            switch (binop_stm->u.BINOP->right->kind) {
                case OperandKind::ICONST: {
                    // store from the const: str #1, ...
                    // move the instant into x3: mov x3, #1
                    int instant = binop_stm->u.BINOP->right->u.ICONST;
                    AS_reg* src_mov = new AS_reg(-3, instant);
                    AS_reg* dst_mov = new AS_reg(3, 0);
                    as_list.push_back(AS_Mov(src_mov, dst_mov));
                    right = dst_mov;
                    break;
                }
                case OperandKind::TEMP: {
                    // store from the reg: str x, ...
                    int src_num = binop_stm->u.BINOP->right->u.TEMP->num;
                    right = new AS_reg(src_num, 0);
                    break;
                }
                case OperandKind::NAME: {
                    assert(0);
                }
            }
            break;
        }
    }
    as_list.push_back(AS_Binop(op,left,right,dst));
}


void llvm2asmLoad(list<AS_stm*> &as_list, L_stm* load_stm) {
    AS_reg* dst;
    AS_reg* ptr;
    dst=new AS_reg(load_stm->u.LOAD->dst->u.TEMP->num,0);
    if (load_stm->u.LOAD->ptr->kind==OperandKind::NAME){
        ptr=new AS_reg(3,0);
        AS_label* label=new AS_label(load_stm->u.LOAD->ptr->u.NAME->name->name);
        as_list.push_back(AS_Adr(label,ptr));
    } else if (load_stm->u.LOAD->ptr->kind==OperandKind::TEMP){
        int num=load_stm->u.LOAD->ptr->u.TEMP->num;
        if (spOffsetMap.find(num)!=spOffsetMap.end()){
            ptr=new AS_reg(-1,spOffsetMap[num]);
        } else{
            ptr=new AS_reg(num,0);
        }
    }
    as_list.push_back(AS_Ldr(dst,ptr));
}


void llvm2asmStore(list<AS_stm*> &as_list, L_stm* store_stm) {
    AS_reg* src;
    AS_reg* ptr;
    if (store_stm->u.STORE->src->kind==OperandKind::TEMP)
        src=new AS_reg(store_stm->u.STORE->src->u.TEMP->num,0);
    else if (store_stm->u.STORE->src->kind==OperandKind::ICONST)
        src=new AS_reg(-3,store_stm->u.STORE->src->u.ICONST);

    if (store_stm->u.STORE->ptr->kind==OperandKind::NAME){
        ptr=new AS_reg(3,0);
        AS_label* label=new AS_label(store_stm->u.STORE->ptr->u.NAME->name->name);
        as_list.push_back(AS_Adr(label,ptr));
    } else if (store_stm->u.STORE->ptr->kind==OperandKind::TEMP){
        int num=store_stm->u.STORE->ptr->u.TEMP->num;
        if (spOffsetMap.find(num)!=spOffsetMap.end()){
            ptr=new AS_reg(-1,spOffsetMap[num]);
        } else{
            ptr=new AS_reg(num,0);
        }
    }
    as_list.push_back(AS_Str(src,ptr));
}


void llvm2asmCmp(list<AS_stm*> &as_list, L_stm* cmp_stm) {
    AS_reg* left;
    AS_reg* right;
    if (cmp_stm->u.CMP->left->kind==OperandKind::TEMP){
        left=new AS_reg(cmp_stm->u.CMP->left->u.TEMP->num,0);
    } else if (cmp_stm->u.CMP->left->kind==OperandKind::ICONST){
        AS_reg* src;
        AS_reg* dst;
        src=new AS_reg(-3,cmp_stm->u.CMP->left->u.ICONST);
        dst=new AS_reg(2,0);
        as_list.push_back(AS_Mov(src,dst));
        left=dst;
    }
    if (cmp_stm->u.CMP->right->kind==OperandKind::TEMP)
        right=new AS_reg(cmp_stm->u.CMP->right->u.TEMP->num,0);
    else if (cmp_stm->u.CMP->right->kind==OperandKind::ICONST)
        right=new AS_reg(-3,cmp_stm->u.CMP->right->u.ICONST);
    as_list.push_back(AS_Cmp(left,right));
    AS_relopkind op;
    switch (cmp_stm->u.CMP->op)
    {
    case L_relopKind::T_eq:
        op=AS_relopkind::EQ_;
        break;
    case L_relopKind::T_ge:
        op=AS_relopkind::GE_;
        break;
    case L_relopKind::T_gt:
        op=AS_relopkind::GT_;
        break;
    case L_relopKind::T_le:
        op=AS_relopkind::LE_;
        break;
    case L_relopKind::T_lt:
        op=AS_relopkind::LT_;
        break;
    case L_relopKind::T_ne:
        op=AS_relopkind::NE_;
        break;
    default:
        break;
    }
    condMap[cmp_stm->u.CMP->dst->u.TEMP->num]=op;
}


void llvm2asmCJmp(list<AS_stm*> &as_list, L_stm* cjmp_stm) {
    // TODO
}

void llvm2asmRet(list<AS_stm*> &as_list, L_stm* ret_stm) {
    AS_reg* dst=new AS_reg(0,0);
    AS_reg* src;
    if (ret_stm->u.RET->ret->kind==OperandKind::TEMP)
        src=new AS_reg(ret_stm->u.RET->ret->u.TEMP->num,0);
    else if (ret_stm->u.RET->ret->kind==OperandKind::ICONST)
        src=new AS_reg(-3,ret_stm->u.RET->ret->u.ICONST);
    as_list.push_back(AS_Mov(src,dst));
    as_list.push_back(AS_Ret());
}

void llvm2asmGep(list<AS_stm*> &as_list, L_stm* gep_stm) {
    // Fixme: add here
}

void llvm2asmStm(list<AS_stm*> &as_list, L_stm &stm) {

    if (!alloc_frame && stm.type != L_StmKind::T_LABEL) {
        new_frame(as_list);
        alloc_frame = true;
    }

    switch (stm.type) {
        case L_StmKind::T_BINOP: {
            llvm2asmBinop(as_list, &stm);
            break;
        }
        case L_StmKind::T_LOAD: {
            llvm2asmLoad(as_list, &stm);
            break;
        }
        case L_StmKind::T_STORE: {
            llvm2asmStore(as_list, &stm);
            break;
        }
        case L_StmKind::T_LABEL: {
            auto label = new AS_label(stm.u.LABEL->label->name);
            as_list.push_back(AS_Label(label));
            break;
        }
        case L_StmKind::T_JUMP: {
            auto label = new AS_label(stm.u.JUMP->jump->name);
            as_list.push_back(AS_B(label));
            break;
        }
        case L_StmKind::T_CMP: {
            llvm2asmCmp(as_list, &stm);
            break;
        }
        case L_StmKind::T_CJUMP: {
            llvm2asmCJmp(as_list, &stm);
            break;
        }
        case L_StmKind::T_MOVE: {
            // Do nothing
            break;
        }
        case L_StmKind::T_CALL: {
            // Do nothing
            break;
        }
        case L_StmKind::T_VOID_CALL: {
            // Do nothing
            break;
        }
        case L_StmKind::T_RETURN: {
            llvm2asmRet(as_list, &stm);
            alloc_frame = false;
            break;
        }
        case L_StmKind::T_ALLOCA: {
            // Do nothing
            break;
        }
        case L_StmKind::T_GEP: {
            llvm2asmGep(as_list, &stm);
            break;
        }
        case L_StmKind::T_PHI: {
            // Do nothing
            break;
        }
        case L_StmKind::T_NULL: {
            // Do nothing
            break;
        }
    }
}

void allocReg(list<AS_stm*> &as_list){

    unordered_map<int,int> vregStart;
    unordered_map<int,int> vregEnd;
    auto setDef=[&](AS_reg *reg,int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        if (vregStart.find(regNo)==vregStart.end()){
            vregStart.insert({regNo,lineNo});
        }
    };
    auto setUse=[&](AS_reg *reg,int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        vregEnd.insert({regNo,lineNo});
    };
    int lineNo=0;
    for (const auto &stm: as_list){
        switch (stm->type){
            case AS_stmkind::BINOP:
                setDef(stm->u.BINOP->dst, lineNo);
                setUse(stm->u.BINOP->left, lineNo);
                setUse(stm->u.BINOP->right, lineNo);
                break;
            case AS_stmkind::MOV:
                setDef(stm->u.MOV->dst, lineNo);
                setUse(stm->u.MOV->src, lineNo);
                break;
            case AS_stmkind::LDR:
                setDef(stm->u.LDR->dst, lineNo);
                setUse(stm->u.LDR->ptr, lineNo);
                break;
            case AS_stmkind::STR:
                setUse(stm->u.STR->src, lineNo);
                setUse(stm->u.STR->ptr, lineNo);
                break;
            case AS_stmkind::CMP:
                setUse(stm->u.CMP->left, lineNo);
                setUse(stm->u.CMP->right, lineNo);
                break;
            case AS_stmkind::ADR:
                setDef(stm->u.ADR->reg, lineNo);
                break;
            default: break;
        }
        lineNo+=1;
    }

    // workaround for undef vreg
    for (const auto& iter: vregEnd){
        auto pos=vregStart.find(iter.first);
        if (pos==vregStart.end()){
            vregStart.insert(iter);
        }
    }

    /* cout<<"Live interval:\n";
    for (auto iter: vregStart){
        cout<<iter.first<<": ["<<iter.second<<", "<<vregEnd[iter.first]<<"]\n";
    } */


    // -1 invalid for allocation, 0 unallocated, >100 registerNo
    // x9-x15 x20-x28 is available
    vector<int> allocateRegs{9,10,11,12,13,14,15,20,21,22,23,24,25,26,27,28};
    vector<int> allocateTable;
    unordered_map<int,int> v2pMapping;
    allocateTable.resize(32);
    for (int i=0;i<32;++i){
        allocateTable[i]=-1;
    }
    for (auto ind: allocateRegs){
        allocateTable[ind]=0;
    }

    auto get_mapping=[&](int regNo,int lineNo){
        auto pos=v2pMapping.find(regNo);
        if (pos!=v2pMapping.end()) return pos->second;

        // find available reg
        for (int i=0;i<32;++i){
            int allocNo=allocateTable[i];
            if ((allocNo==0) || (allocNo>0 && vregEnd[allocNo]<lineNo)){
                v2pMapping[regNo]=i;
                allocateTable[i]=regNo;
                // cout<<regNo<<" -> "<<i<<"\n";
                return i;
            }
        }
        throw runtime_error("allocate register fail");

    };

    auto vreg_map=[&](AS_reg* reg, int lineNo){
        int regNo=reg->reg;
        if (regNo<100) return;
        reg->reg=get_mapping(regNo,lineNo);
    };
    
    lineNo=0;
    for (const auto &stm: as_list){
        switch (stm->type){
            case AS_stmkind::BINOP: 
                vreg_map(stm->u.BINOP->dst, lineNo);
                vreg_map(stm->u.BINOP->left, lineNo);
                vreg_map(stm->u.BINOP->right, lineNo);
                break;
            case AS_stmkind::MOV: 
                vreg_map(stm->u.MOV->dst, lineNo);
                vreg_map(stm->u.MOV->src, lineNo);
                break;
            case AS_stmkind::LDR: 
                vreg_map(stm->u.LDR->dst, lineNo);
                vreg_map(stm->u.LDR->ptr, lineNo);
                break;
            case AS_stmkind::STR: 
                vreg_map(stm->u.STR->src, lineNo);
                vreg_map(stm->u.STR->ptr, lineNo);
                break;
            case AS_stmkind::CMP: 
                vreg_map(stm->u.CMP->left, lineNo);
                vreg_map(stm->u.CMP->right, lineNo);
                break;
            case AS_stmkind::ADR:
                vreg_map(stm->u.ADR->reg, lineNo);
                break;
            default: 
                break;
        }
        lineNo+=1;
    }

    /* cout<<"regAlloc:\n";
    for (const auto& iter:v2pMapping){
        cout<<"x"<<iter.first<<" -> x"<<iter.second<<"\n";
    } */
}

AS_func* llvm2asmFunc(L_func &func) {
    list<AS_stm*> stms;

    auto p = new AS_func(stms);
    auto func_label = new AS_label(func.name);
    p->stms.push_back(AS_Label(func_label));

    for(const auto &block : func.blocks) {
        for (const auto &instr : block->instrs) {
            llvm2asmStm(p->stms, *instr);
        }
    }

    allocReg(p->stms);

    return p;
}

void llvm2asmDecl(vector<AS_decl*> &decls, L_def &def) {
    switch (def.kind) {
        case L_DefKind::GLOBAL: {
            return;
        }
        case L_DefKind::FUNC: {
            AS_decl* decl = new AS_decl(def.u.FUNC->name);
            decls.push_back(decl);
            break;
        }
        case L_DefKind::SRT: {
            return;
        }
    }
}

void llvm2asmGlobal(vector<AS_global*> &globals, L_def &def) {
    switch (def.kind) {
        case L_DefKind::GLOBAL: {
            // Fixme: add here
            break;
        }
        case L_DefKind::FUNC: {
            return;
        }
        case L_DefKind::SRT: {
            return;
        }
    }
}

AS_prog* llvm2asm(L_prog &prog) {
    std::vector<AS_global*> globals;
    std::vector<AS_decl*> decls;
    std::vector<AS_func*> func_list;

    auto as_prog = new AS_prog(globals, decls, func_list);

    structLayoutInit(prog.defs);

    // translate function definition
    for(const auto &def : prog.defs) {
        llvm2asmDecl(as_prog->decls, *def);
    }
    for(const auto &func : prog.funcs) {
        AS_decl* decl = new AS_decl(func->name);
        as_prog->decls.push_back(decl);
    }

    // translate global data
    for(const auto &def : prog.defs) {
        llvm2asmGlobal(as_prog->globals, *def);
    }

    // translate each llvm function
    for(const auto &func : prog.funcs) {
        set_stack(*func);
        as_prog->funcs.push_back(llvm2asmFunc(*func));
    }

    return as_prog;
}
