#include "ssa.h"
#include <cassert>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "bg_llvm.h"
#include "graph.hpp"
#include "liveness.h"
#include "printLLVM.h"

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;

// 结构体用于表示立即支配关系
struct imm_Dominator {
    LLVMIR::L_block* pred;               // 立即支配的前驱节点
    unordered_set<LLVMIR::L_block*> succs; // 后继节点集合
};

// 存储支配关系的全局变量
unordered_map<L_block*, unordered_set<L_block*>> dominators;
unordered_map<L_block*, imm_Dominator> tree_dominators;
unordered_map<L_block*, unordered_set<L_block*>> DF_array;
unordered_map<L_block*, Node<LLVMIR::L_block*>*> revers_graph;
unordered_map<Temp_temp*, AS_operand*> temp2ASoper;

// 初始化支配关系表
static void init_table() {
    dominators.clear();
    tree_dominators.clear();
    DF_array.clear();
    revers_graph.clear();
    temp2ASoper.clear();
}

// 对LLVM IR进行SSA转换
LLVMIR::L_prog* SSA(LLVMIR::L_prog* prog) {
    for (auto& fun : prog->funcs) {
        init_table();
        combine_addr(fun);
        mem2reg(fun);
        auto RA_bg = Create_bg(fun->blocks);
        SingleSourceGraph(RA_bg.mynodes[0], RA_bg,fun);
        // Show_graph(stdout,RA_bg);
        Liveness(RA_bg.mynodes[0], RA_bg, fun->args);
        Dominators(RA_bg);
        // printf_domi();
        tree_Dominators(RA_bg);
        // printf_D_tree();
        // 默认0是入口block
        computeDF(RA_bg, RA_bg.mynodes[0]);
        // printf_DF();
        Place_phi_fu(RA_bg, fun);
        Rename(RA_bg);
        combine_addr(fun);
    }
    return prog;
}

// 判断是否为内存变量
static bool is_mem_variable(L_stm* stm) {
    return stm->type == L_StmKind::T_ALLOCA && stm->u.ALLOCA->dst->kind == OperandKind::TEMP && stm->u.ALLOCA->dst->u.TEMP->type == TempType::INT_PTR && stm->u.ALLOCA->dst->u.TEMP->len == 0;
}

// 保证相同的AS_operand,地址一样 。常量除外
// 合并相同的AS_operand地址
void combine_addr(LLVMIR::L_func* fun) {
    unordered_map<Temp_temp*, unordered_set<AS_operand**>> temp_set;
    unordered_map<Name_name*, unordered_set<AS_operand**>> name_set;
    for (auto& block : fun->blocks) {
        for (auto& stm : block->instrs) {
            auto AS_operand_list = get_all_AS_operand(stm);
            for (auto AS_op : AS_operand_list) {
                if ((*AS_op)->kind == OperandKind::TEMP) {
                    temp_set[(*AS_op)->u.TEMP].insert(AS_op);
                } else if ((*AS_op)->kind == OperandKind::NAME) {
                    name_set[(*AS_op)->u.NAME].insert(AS_op);
                }
            }
        }
    }
    for (auto temp : temp_set) {
        AS_operand* fi_AS_op = **temp.second.begin();
        for (auto AS_op : temp.second) {
            *AS_op = fi_AS_op;
        }
    }
    for (auto name : name_set) {
        AS_operand* fi_AS_op = **name.second.begin();
        for (auto AS_op : name.second) {
            *AS_op = fi_AS_op;
        }
    }
}

// 将内存中的标量放入寄存器
void mem2reg(LLVMIR::L_func* fun) {
   //   Todo
   L_block* first_block = fun->blocks.front();
    unordered_map<Temp_temp*, AS_operand*> alloca_temp2ASoper;
    for (auto iter = first_block->instrs.begin(); iter != first_block->instrs.end();) {
        if (is_mem_variable(*iter)) {
            AS_operand* dst = (*iter)->u.ALLOCA->dst;
            auto xx = AS_Operand_Temp(Temp_newtemp_int());
            alloca_temp2ASoper[dst->u.TEMP] = xx;
            temp2ASoper[xx->u.TEMP] = xx;
            (*iter) = L_Move(AS_Operand_Const(0),xx);
            iter++;
        } else iter++;
    }
    for (L_block* block: fun->blocks) {
        for (auto iter = block->instrs.begin(); iter != block->instrs.end();) {
            if ((*iter)->type == L_StmKind::T_LOAD && (*iter)->u.LOAD->ptr->kind == OperandKind::TEMP && alloca_temp2ASoper.find((*iter)->u.LOAD->ptr->u.TEMP) != alloca_temp2ASoper.end()) {
                (*iter)->u.LOAD->dst->u.TEMP = alloca_temp2ASoper[(*iter)->u.LOAD->ptr->u.TEMP]->u.TEMP;
                iter = block->instrs.erase(iter);
            } else if ((*iter)->type == L_StmKind::T_STORE && (*iter)->u.STORE->ptr->kind == OperandKind::TEMP && alloca_temp2ASoper.find((*iter)->u.STORE->ptr->u.TEMP) != alloca_temp2ASoper.end()) {
                auto xx = alloca_temp2ASoper[(*iter)->u.STORE->ptr->u.TEMP];
                (*iter) = L_Move((*iter)->u.STORE->src, xx);
                iter++;
            } else iter++;
        }
    }
    combine_addr(fun);
}

// 计算支配节点
void Dominators(GRAPH::Graph<LLVMIR::L_block*>& bg) {
    //   Todo
       dominators.clear();
    for (auto block : bg.mynodes) {
        revers_graph[block.second->info] = block.second;
    }
    for (auto block_i : bg.mynodes) {
        if (block_i.second->inDegree()) {
            for (auto block_j : bg.mynodes) {
                dominators[block_i.second->info].insert(block_j.second->info);
            }
        } else {
            dominators[block_i.second->info].insert(block_i.second->info);
        }
    }
    bool changed = true;
    int i = 0;
    while (changed) {
        changed = false;
        i++;
        for (auto block : bg.mynodes) {
            if (block.second->inDegree() == 0)
                continue;
            unordered_set<LLVMIR::L_block*> next_dom;
            //  intersection D[p]
            auto preds = block.second->preds;
            if (preds.size()) {
                next_dom = dominators[bg.mynodes[*preds.begin()]->info];
            }
            for (auto pred : preds) {
                if (pred == *preds.begin())
                    continue;
                for (auto t = next_dom.begin(); t != next_dom.end();) {
                    if (dominators[bg.mynodes[pred]->info].find(*t) != dominators[bg.mynodes[pred]->info].end()) {
                        ++t;
                    } else {
                        t = next_dom.erase(t);
                    }
                }
            }
            next_dom.insert(block.second->info);
            if (!changed) {
                for (auto x : dominators[block.second->info]) {
                    if (next_dom.find(x) != next_dom.end()) {
                        continue;
                    } else {
                        changed = true;
                        break;
                    }
                }
            }
            dominators[block.second->info] = next_dom;
        }
    }
    // cout<<i<<endl;
}

void printf_domi() {
    printf("Dominator:\n");
    for (auto x : dominators) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

// 打印支配树
void printf_D_tree() {
    printf("dominator tree:\n");
    for (auto x : tree_dominators) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second.succs) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

// 打印DF集合
void printf_DF() {
    printf("DF:\n");
    for (auto x : DF_array) {
        printf("%s :\n", x.first->label->name.c_str());
        for (auto t : x.second) {
            printf("%s ", t->label->name.c_str());
        }
        printf("\n\n");
    }
}

// 计算支配树
void tree_Dominators(GRAPH::Graph<LLVMIR::L_block*>& bg) {
    //
        for (auto node:bg.mynodes){
        unordered_set<L_block*> candidate=dominators[node.second->info];
        candidate.erase(node.second->info);
        imm_Dominator imm;
        if (node.first==0){
            imm.pred=nullptr;
            tree_dominators.emplace(node.second->info,imm);
            continue;
        }
        for (auto n:candidate){
            bool flag=false; // n是否能支配其它支配点
            for (auto b:candidate){
                if (b != n && dominators[b].find(n)!=dominators[b].end()){
                    flag=true;
                    break;
                }
            }
            if (!flag){
                imm.pred=n;
                tree_dominators.emplace(node.second->info,imm);
                tree_dominators[n].succs.insert(node.second->info);
                break;
            }
        }
    }
}

// 计算DF集合
void computeDF(GRAPH::Graph<LLVMIR::L_block*>& bg, GRAPH::Node<LLVMIR::L_block*>* r) {
    //   Todo
    unordered_set<L_block*> df;
    for (auto y:r->succs){
        if (tree_dominators[bg.mynodes[y]->info].pred!=r->info){
            df.insert(bg.mynodes[y]->info);
        }
    }
    for (auto c:tree_dominators[r->info].succs){
        computeDF(bg, revers_graph[c]);
        for (auto w:DF_array[c]){
            if (r->info==w || dominators[w].find(r->info)==dominators[w].end())
                df.insert(w);
        }
    }
    DF_array.emplace(r->info,df);
}

// 只对标量做
// 插入Phi函数
void Place_phi_fu(GRAPH::Graph<LLVMIR::L_block*>& bg, L_func* fun) {
    //   Todo
    unordered_map<Temp_temp*, unordered_set<Node<LLVMIR::L_block *>*>> defsites;
    unordered_map<L_block*, unordered_set<Temp_temp*>> A_phi;
    for (auto node: bg.mynodes) {
        for (Temp_temp* temp: FG_def(node.second)) {
            if (temp2ASoper.find(temp) != temp2ASoper.end())
                defsites[temp].insert(node.second);
        }
    }
    for (auto pair: defsites) {
        Temp_temp* temp = pair.first;
        auto nodeSet = pair.second;
        while (!nodeSet.empty()) {
            auto node = *nodeSet.begin();
            nodeSet.erase(nodeSet.begin());
            for (L_block* block: DF_array[node->info]) {
                if (A_phi[block].find(temp) == A_phi[block].end()) {
                    vector<std::pair<AS_operand*, Temp_label*>> phi_vector;
                    for (int pred: *revers_graph[block]->pred())
                        phi_vector.push_back(make_pair(temp2ASoper[temp], bg.mynodes[pred]->info->label));
                    block->instrs.insert(next(block->instrs.begin()), L_Phi(temp2ASoper[temp], phi_vector)); // Rename阶段再改名
                    A_phi[block].insert(temp);
                    if (FG_def(revers_graph[block]).find(temp) == FG_def(revers_graph[block]).end())
                        nodeSet.insert(revers_graph[block]);
                }
            }
        }
    }
}

// 获取L_stm中定义的整数类型操作数
static list<AS_operand**> get_def_int_operand(LLVMIR::L_stm* stm) {
    list<AS_operand**> ret1 = get_def_operand(stm), ret2;
    for (auto AS_op : ret1) {
        if ((**AS_op).u.TEMP->type == TempType::INT_TEMP) {
            ret2.push_back(AS_op);
        }
    }
    return ret2;
}

// 获取L_stm中使用的整数类型操作数
static list<AS_operand**> get_use_int_operand(LLVMIR::L_stm* stm) {
    list<AS_operand**> ret1 = get_use_operand(stm), ret2;
    for (auto AS_op : ret1) {
        if ((**AS_op).u.TEMP->type == TempType::INT_TEMP) {
            ret2.push_back(AS_op);
        }
    }
    return ret2;
}

// 重命名临时寄存器
static void Rename_temp(GRAPH::Graph<LLVMIR::L_block*>& bg, GRAPH::Node<LLVMIR::L_block*>* n, unordered_map<Temp_temp*, stack<Temp_temp*>>& Stack) {
   //   Todo
   list<Temp_temp*> record;
    for (auto ir:n->info->instrs){
        if (ir->type!=L_StmKind::T_PHI){
            list<AS_operand**> all_use=get_use_int_operand(ir);
            for (auto& x:all_use){
                if (Stack.find((*x)->u.TEMP)!=Stack.end())
                    *x=AS_Operand_Temp(Stack[(*x)->u.TEMP].top());
            }
        }
        list<AS_operand**> all_def=get_def_int_operand(ir);
        for (auto& a:all_def){
            if (Stack.find((*a)->u.TEMP)!=Stack.end()){
                Temp_temp* a_i=Temp_newtemp_int();
                Stack[(*a)->u.TEMP].push(a_i);
                record.push_back((*a)->u.TEMP);
                *a=AS_Operand_Temp(a_i);
            }
        }
    }
    for (auto y:n->succs){
        Temp_label* labeln=n->info->label;
        for (auto ir:bg.mynodes[y]->info->instrs){
            if (ir->type==L_StmKind::T_PHI){
                for (auto &p:ir->u.PHI->phis){
                    if (p.second==labeln){
                        p.first=AS_Operand_Temp(Stack[p.first->u.TEMP].top());
                    }
                }
            }
        }
    }
    for (auto x:tree_dominators[n->info].succs){
        Rename_temp(bg,revers_graph[x],Stack);
    }
    for (auto a:record){
        Stack[a].pop();
    }
}

// 执行重命名
void Rename(GRAPH::Graph<LLVMIR::L_block*>& bg) {
   //   Todo
    unordered_map<Temp_temp*, stack<Temp_temp*>> stk;
    for (auto &iter : temp2ASoper)
    {
        stk[iter.first].push(iter.first);
    }
    Rename_temp(bg,bg.mynodes[0],stk);
}