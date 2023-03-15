#ifndef ast_compound_statement_hpp
#define ast_compound_statement_hpp

#include "ast_block.hpp"

class Compound_Statement : public Block {
private:

    std::vector<BlockPtr> *dlist;
    std::vector<BlockPtr> *slist;

public:
    Compound_Statement(std::vector<BlockPtr> * _dlist, std::vector<BlockPtr> * _list) : dlist(_dlist), slist(_list) {}

    Compound_Statement(std::vector<BlockPtr> *_list) : slist(_list) {}

    ~Compound_Statement() {
        for (auto i : *slist){
            delete i;
        }
        delete slist;
        for (auto i : *dlist){
            delete i;
        }
        delete dlist;
    }

    // int getSize() { 
    //     int size = 0;
    //     for (auto it : *slist){
    //         size += it->getSize();
    //     }
    // }

    std::vector<BlockPtr> getDec()  const { return *dlist; }
    std::vector<BlockPtr> getList() const { return *slist; }

    virtual void print(std::ostream &dst) const override {
        dst << "\n    Compound Statement [";
        if (dlist != nullptr) {
            dst << "\n    Declaration List [";
            for (auto i : *dlist){
                i->print(dst);
            }
            dst<<"\n    ]";
        }
        for (auto i : *slist){
            i->print(dst);
        }
        dst<<"\n    ]";
    }

     virtual void generateRISC(std::ostream &dst, Context &context, std::string destReg) const override {
        context.scope.newScope();
        dst<<"\naddi sp,sp ";
        context.offset += (dlist->size() * -4 /*+ slist->size() * -4*/);
        dst<<context.offset;
        dst<<"\n";
        dst<<"sw s0 " << 4 - context.offset << "(sp)\n";
        dst<<"addi s0,sp," <<  - 1 * context.offset << "\n";
        if (dlist != nullptr) {
            for (auto i : *dlist){
                i->generateRISC(dst, context, destReg);
            }
        }
        for (auto i : *slist){
            i->generateRISC(dst, context, destReg);
        }
        dst<<"lw s0," << 4 - context.offset << "(sp)\n";
        dst<<"addi sp,sp," << -1 * context.offset << "\n";
        context.offset += (dlist->size() * 4 /*+ slist->size() * 4*/);
        context.scope.popScope();


    }
    
};
#endif
