#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_block.hpp"

class Function : public Block {
private:
    std::string specifier;
    BlockPtr declarator;
    BlockPtr cstatement;
// protected:
public:
    Function(std::string s, BlockPtr d, BlockPtr c) : specifier(s), declarator(d), cstatement(c) {}

    virtual ~Function() {
        delete declarator;
        delete cstatement;
    }

    std::string getSpecifier() const {
        return specifier;
    }

    BlockPtr getDeclarator() const {
        return declarator;
    }

    BlockPtr getStatement() const {
        return cstatement;
    }

    virtual void print(std::ostream &dst) const override {
        dst<<"New Function: [";
        dst<<" Function Type: ";
        dst<<"[ "<<getSpecifier()<<" ] ";
        dst<<"Function Name: [ ";
        getDeclarator()->print(dst);
        dst<<" ] ] [";
        getStatement()->print(dst);
        dst<<"\n] ";

    }

    virtual void generateRISC(std::ostream &dst , Context &context , std::string destReg) const override {
        try{
            dst<<".text"<<std::endl;
            dst<<".globl "<<declarator->getIdentifier()<<std::endl;
            dst<<declarator->getIdentifier()<<":"<<std::endl;
            // std::string reg = context.regs.nextFreeReg();
            // context.regs.useReg(reg);
            cstatement->generateRISC(dst, context, "a0");
            // dst<<"\nmv a0,"+reg+"\njr ra";
            // context.regs.freeReg(reg);
            dst<<"jr ra"<<std::endl;
            // EVALUATE SIZE OF SYMBOLS USED IN COMPOUND STATEMENT
        }
        catch (...) {
            dst<<"Error in Function";
        }


    }


};

#endif
