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

static Graph<L_block*> RA_bg;
static unordered_map<Temp_label*, L_block*> block_env;
static unordered_set<int> extraSet;

Graph<L_block*>& Bg_graph() {
    return RA_bg;
}
unordered_map<Temp_label*, L_block*>& Bg_block_env() {
    return block_env;
}

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

static void Enter_bg(L_block* b1, L_block* b2) {
    Node<L_block*>* n1 = Look_bg(b1);
    Node<L_block*>* n2 = Look_bg(b2);
    RA_bg.addEdge(n1, n2);
    return;
}

/* input LLVMIR::L_block* *List after instruction selection for each block,
    generate a graph on the basic blocks */

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

// maybe useful
static void DFS(Node<L_block*>* r, Graph<L_block*>& bg) {
    extraSet.erase(r->nodeid());
    for (int node:*r->succ()){
        if (extraSet.find(node)!=extraSet.end()){
            Node<L_block*>* success=bg.mynodes[node];
            DFS(success,bg);
        }
    }
}

void SingleSourceGraph(Node<L_block*>* r, Graph<L_block*>& bg,L_func*fun) {
    extraSet.clear();
    for (auto node:bg.mynodes){
        extraSet.insert(node.first);
    }
    DFS(r,bg);
    for (int node:extraSet){
        fun->blocks.remove(bg.mynodes[node]->nodeInfo());
        NodeSet predSet = *bg.mynodes[node]->pred(), succSet = *bg.mynodes[node]->succ();
        for (int pred: predSet)
            bg.rmEdge(bg.mynodes[pred], bg.mynodes[node]);
        for (int succ: succSet)
            bg.rmEdge(bg.mynodes[node], bg.mynodes[succ]);
        bg.rmNode(bg.mynodes[node]);
        bg.nodecount--;
    }
}

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