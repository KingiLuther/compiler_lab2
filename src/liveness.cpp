#include "liveness.h"
#include <unordered_map>
#include <unordered_set>
#include "graph.hpp"
#include "llvm_ir.h"
#include "temp.h"

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;

// 表示特定程序点的活跃变量集合（in 和 out）
struct inOut {
    TempSet_ in;
    TempSet_ out;
};

// 表示特定程序点的使用和定义变量的集合
struct useDef {
    TempSet_ use;
    TempSet_ def;
};

// 存储每个基本块的in和out集合的全局表
static unordered_map<GRAPH::Node<LLVMIR::L_block*>*, inOut> InOutTable;
// 存储每个基本块的use和def集合的全局表
static unordered_map<GRAPH::Node<LLVMIR::L_block*>*, useDef> UseDefTable;

// 获取LLVM语句中所有操作数指针的列表
list<AS_operand**> get_all_AS_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->left));
            AS_operand_list.push_back(&(stm->u.BINOP->right));
            AS_operand_list.push_back(&(stm->u.BINOP->dst));

        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->dst));
            AS_operand_list.push_back(&(stm->u.LOAD->ptr));
        } break;
        case L_StmKind::T_STORE: {
            AS_operand_list.push_back(&(stm->u.STORE->src));
            AS_operand_list.push_back(&(stm->u.STORE->ptr));
        } break;
        case L_StmKind::T_LABEL: {
        } break;
        case L_StmKind::T_JUMP: {
        } break;
        case L_StmKind::T_CMP: {
            AS_operand_list.push_back(&(stm->u.CMP->left));
            AS_operand_list.push_back(&(stm->u.CMP->right));
            AS_operand_list.push_back(&(stm->u.CMP->dst));
        } break;
        case L_StmKind::T_CJUMP: {
            AS_operand_list.push_back(&(stm->u.CJUMP->dst));
        } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->src));
            AS_operand_list.push_back(&(stm->u.MOVE->dst));
        } break;
        case L_StmKind::T_CALL: {
            AS_operand_list.push_back(&(stm->u.CALL->res));
            for (auto& arg : stm->u.CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_VOID_CALL: {
            for (auto& arg : stm->u.VOID_CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_RETURN: {
            if (stm->u.RET->ret != nullptr)
                AS_operand_list.push_back(&(stm->u.RET->ret));
        } break;
        case L_StmKind::T_PHI: {
            AS_operand_list.push_back(&(stm->u.PHI->dst));
            for (auto& phi : stm->u.PHI->phis) {
                AS_operand_list.push_back(&(phi.first));
            }
        } break;
        case L_StmKind::T_ALLOCA: {
            AS_operand_list.push_back(&(stm->u.ALLOCA->dst));
        } break;
        case L_StmKind::T_GEP: {
            AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->index));
        } break;
        default: {
            printf("%d\n", (int)stm->type);
            assert(0);
        }
    }
    return AS_operand_list;
}

// 获取LLVM语句中表示定义的操作数指针的列表
std::list<AS_operand**> get_def_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    list<AS_operand**> ret_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->dst));
        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->dst));
        } break;
        case L_StmKind::T_STORE: {
        } break;
        case L_StmKind::T_LABEL: {
        } break;
        case L_StmKind::T_JUMP: {
        } break;
        case L_StmKind::T_CMP: {
            //  i1的局部变量不进行pass
            // AS_operand_list.push_back(&(stm->u.CMP->dst));
        } break;
        case L_StmKind::T_CJUMP: {
        } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->dst));
        } break;
        case L_StmKind::T_CALL: {
            AS_operand_list.push_back(&(stm->u.CALL->res));
        } break;
        case L_StmKind::T_VOID_CALL: {
        } break;
        case L_StmKind::T_RETURN: {
        } break;
        case L_StmKind::T_PHI: {
            AS_operand_list.push_back(&(stm->u.PHI->dst));
        } break;
        case L_StmKind::T_ALLOCA: {
            AS_operand_list.push_back(&(stm->u.ALLOCA->dst));
        } break;
        case L_StmKind::T_GEP: {
            AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
        } break;
        default: {
            printf("%d\n", (int)stm->type);
            assert(0);
        }
    }
    for (auto AS_op : AS_operand_list) {
        if ((*AS_op)->kind == OperandKind::TEMP) {
            ret_list.push_back(AS_op);
        }
    }
    return ret_list;
}

// 提取LLVM语句中定义的Temp_temp*的列表
list<Temp_temp*> get_def(L_stm* stm) {
    auto AS_operand_list = get_def_operand(stm);
    list<Temp_temp*> Temp_list;
    for (auto AS_op : AS_operand_list) {
        Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

// 获取LLVM语句中表示使用的操作数指针的列表
std::list<AS_operand**> get_use_operand(L_stm* stm) {
    list<AS_operand**> AS_operand_list;
    list<AS_operand**> ret_list;
    switch (stm->type) {
        case L_StmKind::T_BINOP: {
            AS_operand_list.push_back(&(stm->u.BINOP->left));
            AS_operand_list.push_back(&(stm->u.BINOP->right));
        } break;
        case L_StmKind::T_LOAD: {
            AS_operand_list.push_back(&(stm->u.LOAD->ptr));
        } break;
        case L_StmKind::T_STORE: {
            AS_operand_list.push_back(&(stm->u.STORE->src));
            AS_operand_list.push_back(&(stm->u.STORE->ptr));
        } break;
        case L_StmKind::T_LABEL: {
        } break;
        case L_StmKind::T_JUMP: {
        } break;
        case L_StmKind::T_CMP: {
            AS_operand_list.push_back(&(stm->u.CMP->left));
            AS_operand_list.push_back(&(stm->u.CMP->right));
        } break;
        case L_StmKind::T_CJUMP: {
            // AS_operand_list.push_back(&(stm->u.CJUMP->dst));
        } break;
        case L_StmKind::T_MOVE: {
            AS_operand_list.push_back(&(stm->u.MOVE->src));
        } break;
        case L_StmKind::T_CALL: {
            for (auto& arg : stm->u.CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_VOID_CALL: {
            for (auto& arg : stm->u.VOID_CALL->args) {
                AS_operand_list.push_back(&arg);
            }
        } break;
        case L_StmKind::T_RETURN: {
            if (stm->u.RET->ret != nullptr)
                AS_operand_list.push_back(&(stm->u.RET->ret));
        } break;
        case L_StmKind::T_PHI: {
            for (auto& phi : stm->u.PHI->phis) {
                AS_operand_list.push_back(&(phi.first));
            }
        } break;
        case L_StmKind::T_ALLOCA: {
        } break;
        case L_StmKind::T_GEP: {
            AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
            AS_operand_list.push_back(&(stm->u.GEP->index));
        } break;
        default: {
            printf("%d\n", (int)stm->type);
            assert(0);
        }
    }
    for (auto AS_op : AS_operand_list) {
        if ((*AS_op)->kind == OperandKind::TEMP) {
            ret_list.push_back(AS_op);
        }
    }
    return ret_list;
}

// 提取LLVM语句中使用的Temp_temp*的列表
list<Temp_temp*> get_use(L_stm* stm) {
    auto AS_operand_list = get_use_operand(stm);
    list<Temp_temp*> Temp_list;
    for (auto AS_op : AS_operand_list) {
        Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

// 初始化InOutTable和UseDefTable
static void init_INOUT() {
    InOutTable.clear();
    UseDefTable.clear();
}

// 用于访问给定基本块的out集合的
TempSet_& FG_Out(GRAPH::Node<LLVMIR::L_block*>* r) {
    return InOutTable[r].out;
}
// 用于访问给定基本块的in集合
TempSet_& FG_In(GRAPH::Node<LLVMIR::L_block*>* r) {
    return InOutTable[r].in;
}
// 用于访问给定基本块的def集合
TempSet_& FG_def(GRAPH::Node<LLVMIR::L_block*>* r) {
    return UseDefTable[r].def;
}
// 用于访问给定基本块的use集合
TempSet_& FG_use(GRAPH::Node<LLVMIR::L_block*>* r) {
    return UseDefTable[r].use;
}

// 计算每个基本块的use和def集合
static void Use_def(GRAPH::Node<LLVMIR::L_block*>* r, GRAPH::Graph<LLVMIR::L_block*>& bg, std::vector<Temp_temp*>& args) {
    for (auto arg : args)
        UseDefTable[r].def.insert(arg);
    for (auto block_node : bg.mynodes) {
        auto block = block_node.second->info;
        for (auto stm : block->instrs) {
            auto uses = get_use(stm);
            auto defs = get_def(stm);
             for (auto use : uses) {
                if(UseDefTable[block_node.second].def.find(use)==UseDefTable[block_node.second].def.end())
                    UseDefTable[block_node.second].use.insert(use);
            }
            for (auto def : defs) {
                UseDefTable[block_node.second].def.insert(def);
            }
        }
    }
}

static int gi=0;

// 执行活跃变量分析的一个迭代，更新每个基本块的in和out集合
static bool LivenessIteration(GRAPH::Node<LLVMIR::L_block*>* r, GRAPH::Graph<LLVMIR::L_block*>& bg) {
    bool changed = false;
    gi++;
    for (auto block_node : bg.mynodes) {
        auto block = block_node.second;
        // do in[n] = use[n] union (out[n] - def[n])
        auto in = TempSet_union(&FG_use(block), TempSet_diff(&FG_Out(block), &(FG_def(block))));

        // Now do out[n]=union_s in succ[n] (in[s])
        auto succ = block->succs;
        TempSet out = new TempSet_();  // out is an accumulator
        for (auto s : succ) {
            out = TempSet_union(out, &FG_In(bg.mynodes[s]));
        }
        // See if any in/out changed
        if (!(!changed&&TempSet_eq(&FG_In(block), in) && TempSet_eq(&FG_Out(block), out)))
            changed = true;
        // enter the new info
        InOutTable[block].in = *in;
        InOutTable[block].out = *out;
    }

    // Show_Liveness(stdout,bg);
    return changed;
}

// 用于打印有关活跃变量的信息以进行调试的辅助函数
void PrintTemps(FILE *out, TempSet set) {
    for(auto x:*set){
        printf("%d  ",x->num);
    }
}

// 用于打印有关活跃变量的信息以进行调试的辅助函数
void Show_Liveness(FILE* out, GRAPH::Graph<LLVMIR::L_block*>& bg) {
    fprintf(out, "\n\nNumber of iterations=%d\n\n", gi);
    for(auto block_node:bg.mynodes){
        fprintf(out, "----------------------\n");
        printf("block %s \n",block_node.second->info->label->name.c_str());
        fprintf(out, "def=\n"); PrintTemps(out, &FG_def(block_node.second)); fprintf(out, "\n");
        fprintf(out, "use=\n"); PrintTemps(out, &FG_use(block_node.second)); fprintf(out, "\n");
        fprintf(out, "In=\n");  PrintTemps(out, &FG_In(block_node.second)); fprintf(out, "\n");
        fprintf(out, "Out=\n"); PrintTemps(out, &FG_Out(block_node.second)); fprintf(out, "\n");
    }
}

// 以block为单位
// 在由bg表示的控制流图（CFG）上执行活跃变量分析的主要函数
void Liveness(GRAPH::Node<LLVMIR::L_block*>* r, GRAPH::Graph<LLVMIR::L_block*>& bg, std::vector<Temp_temp*>& args) {
    init_INOUT();
    Use_def(r, bg, args);
    gi=0;
    bool changed = true;
    while (changed)
        changed = LivenessIteration(r, bg);
}
