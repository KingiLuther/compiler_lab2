#include "bg_llvm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "graph.hpp"
#include "printLLVM.h"
#include "temp.h"
/* graph on AS_ basic blocks. This is useful to find dominance
   relations, etc. */

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;

static Graph<L_block*> RA_bg;   //表示基本块之间关系的图
static unordered_map<Temp_label*, L_block*> block_env;  // 用于映射Temp_label*到相应基本块L_block*的无序映射

//  提供对全局图的访问函数
Graph<L_block*>& Bg_graph() {
    return RA_bg;
}
//  提供对块环境映射的访问函数
unordered_map<Temp_label*, L_block*>& Bg_block_env() {
    return block_env;
}

// 在图中查找给定基本块的节点，如果找不到则创建新节点
Node<L_block*>* Look_bg(L_block* b) {
    Node<L_block*>* n1 = nullptr;
    for (auto n : *RA_bg.nodes()) {
        if (n.second->nodeInfo() == b) {
            n1 = n.second;
            break;
        }
    }
    if (n1 == nullptr)
        return RA_bg.addNode(b);
    else
        return n1;
}

//  在图中添加由两个基本块表示的边
static void Enter_bg(L_block* b1, L_block* b2) {
    Node<L_block*>* n1 = Look_bg(b1);
    Node<L_block*>* n2 = Look_bg(b2);
    RA_bg.addEdge(n1, n2);
    return;
}

/* input LLVMIR::L_block* *List after instruction selection for each block,
    generate a graph on the basic blocks */
// 接受LLVM基本块的列表，构建了一个基本块图
Graph<L_block*>& Create_bg(list<L_block*>& bl) {
    RA_bg = Graph<L_block*>();
    block_env = unordered_map<Temp_label*, L_block*>();

    for (auto block : bl) {
        block_env.insert({block->label, block});
        RA_bg.addNode(block);
    }

    for (auto block : bl) {
        unordered_set<Temp_label*> succs = block->succs;
        for (auto label : succs) {
            Enter_bg(block, block_env[label]);
        }
    }
    return RA_bg;
}

static void DFS(Node<L_block*>* r, Graph<L_block*>& bg) {
    if (r->color == 1)
        return;
    r->color = 1;
    for (auto succ_id : r->succs) {
        auto succ = bg.mynodes[succ_id];
        DFS(succ, bg);
    }
}

// 图的修剪
// 从给定的起始节点执行DFS，标记可达的基本块，并删除不可达的基本块
void SingleSourceGraph(Node<L_block*>* r, Graph<L_block*>& bg,L_func*fun) {
    unordered_map<L_block*,std::list<L_block*>::iterator>iter_map;
    for(auto block=fun->blocks.begin();block!=fun->blocks.end();++block){
        iter_map.insert({*block,block});
    }
    DFS(r, bg);
    for (auto x = bg.mynodes.begin(); x != bg.mynodes.end();) {
        if (x->second->color == 0) {
            for (auto pred : x->second->preds) {
                bg.mynodes[pred]->succs.erase(x->second->mykey);
            }
            for (auto succ : x->second->succs) {
                bg.mynodes[succ]->preds.erase(x->second->mykey);
            }
            // printL_block(cout,x->second->info);
            fun->blocks.erase(iter_map[x->second->info]);
            x = bg.mynodes.erase(x);
        } else {
            ++x;
        }
    }
    for (auto& x : bg.mynodes) {
        x.second->color = 0;
    }
    return;
}

// 打印图的信息，包括每个基本块的前驱和后继基本块
void Show_graph(FILE* out,GRAPH::Graph<LLVMIR::L_block*>&bg){
    for(auto block_node:bg.mynodes){
        auto block=block_node.second->info;
        fprintf(out,"%s \n",block->label->name.c_str());
        fprintf(out,"pred  %zu  ",block_node.second->preds.size());
        for(auto pred:block_node.second->preds){
            fprintf(out,"%s  ",bg.mynodes[pred]->info->label->name.c_str());
        }
        fprintf(out,"\n");
        fprintf(out,"succ  %zu  ",block_node.second->succs.size());
        for(auto succ:block_node.second->succs){
            fprintf(out,"%s  ",bg.mynodes[succ]->info->label->name.c_str());
        }
        fprintf(out,"\n");
    }
}