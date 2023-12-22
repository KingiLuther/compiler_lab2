#include "printASM.h"
#include "asm_arm.h"
#include <iostream>

using namespace std;
using namespace ASM;

void ASM::printAS_global(std::ostream &os, ASM::AS_global *global) {
    os << global->label->name << ":" << endl;
    if (global->len>0){
        os << "\t\t" << ".zero" << "\t" << global->len;
    } else {
        os << "\t\t" << ".word" << "\t" << global->init;
    }
}

void ASM::printAS_decl(std::ostream &os, ASM::AS_decl *decl) {
    os << ".global" << decl->name << endl;
}


void ASM::printAS_stm(std::ostream &os, AS_stm *stm) {
    // Fixme: add here
    if (stm->type==AS_stmkind::ADR){
        os << "\t\tadr\t\t";
        printAS_reg(os,stm->u.ADR->reg);
        os << ", " << stm->u.ADR->label->name << endl;
    } else if (stm->type==AS_stmkind::B){
        os << "\t\tb\t\t" << stm->u.B->jump->name << endl;
    } else if (stm->type==AS_stmkind::BCOND){
        os << "\t\tb.";
        if (stm->u.BCOND->op==AS_relopkind::EQ_){
            os << "eq";
        } else if (stm->u.BCOND->op==AS_relopkind::GE_){
            os << "ge";
        } else if (stm->u.BCOND->op==AS_relopkind::GT_){
            os << "gt";
        } else if (stm->u.BCOND->op==AS_relopkind::LE_){
            os << "le";
        } else if (stm->u.BCOND->op==AS_relopkind::LT_){
            os << "lt";
        } else if (stm->u.BCOND->op==AS_relopkind::NE_){
            os << "ne";
        }
        os << "\t" << stm->u.BCOND->jump->name << endl;
    } else if (stm->type==AS_stmkind::BINOP){
        if (stm->u.BINOP->op==AS_binopkind::ADD_){
            os << "\t\tadd\t\t";
            printAS_reg(os,stm->u.BINOP->dst);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->left);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->right);
            os << endl;
        } else if (stm->u.BINOP->op==AS_binopkind::SUB_){
            os << "\t\tsub\t\t";
            printAS_reg(os,stm->u.BINOP->dst);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->left);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->right);
            os << endl;
        } else if (stm->u.BINOP->op==AS_binopkind::MUL_){
            os << "\t\tsub\t\t";
            printAS_reg(os,stm->u.BINOP->dst);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->left);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->right);
            os << endl;
        } else if (stm->u.BINOP->op==AS_binopkind::SDIV_){
            os << "\t\tsdiv\t";
            printAS_reg(os,stm->u.BINOP->dst);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->left);
            os << ", ";
            printAS_reg(os,stm->u.BINOP->right);
            os << endl;
        }
    } else if (stm->type==AS_stmkind::BL){
        os << "\t\tbl\t\t" << stm->u.BL->jump->name << endl;
    } else if (stm->type==AS_stmkind::CMP){
        os << "\t\tcmp\t\t";
        printAS_reg(os,stm->u.CMP->left);
        os << ", ";
        printAS_reg(os,stm->u.CMP->right);
        os << endl;
    } else if (stm->type==AS_stmkind::LABEL){
        os << stm->u.LABEL->name << ":" << endl;
    } else if (stm->type==AS_stmkind::LDR){
        os << "\t\tldr\t\t";
        printAS_reg(os,stm->u.LDR->dst);
        os << ", ";
        printAS_reg(os,stm->u.LDR->ptr);
        os << endl;
    } else if (stm->type==AS_stmkind::MOV){
        os << "\t\tmov\t\t";
        printAS_reg(os,stm->u.MOV->dst);
        os << ", ";
        printAS_reg(os,stm->u.MOV->src);
        os << endl;
    } else if (stm->type==AS_stmkind::RET){
        os << "ret" << endl;
    } else if (stm->type==AS_stmkind::STR){
        os << "\t\tstr\t\t";
        printAS_reg(os,stm->u.STR->src);
        os << ", ";
        printAS_reg(os,stm->u.STR->ptr);
        os << endl;
    }
}       
void ASM::printAS_reg(std::ostream &os, AS_reg *reg) {
    if (reg->reg>=0){
        os << "x" << reg->reg;
    } else if (reg->reg==-3){
        os << "#" << reg->offset;
    } else if (reg->reg==-1){
        if (reg->offset!=-1){
            if (reg->offset==0)
                os << "[sp]";
            else
                os << "[sp, #" << reg->offset << "]"; 
        } else {
            os << "sp";
        }
    }
}

void ASM::printAS_func(std::ostream &os, AS_func *func) {
    for(const auto &stm : func->stms) {
        printAS_stm(os, stm);
    }
}

void ASM::printAS_prog(std::ostream &os, AS_prog *prog) {

    os << ".section .data\n";
    for(const auto &global : prog->globals) {
        printAS_global(os, global);
    }

    os << ".section .text\n";

    for(const auto &decl : prog->decls) {
        printAS_decl(os, decl);
    }

    for(const auto &func : prog->funcs) {
        printAS_func(os, func);
    }
}