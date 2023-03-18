#ifndef ast_iteration_statement_hpp
#define ast_iteration_statement_hpp

#include "ast_block.hpp"

class While: public Block {
private:
    BlockPtr expression;
    BlockPtr cstatement;
public:
    While(BlockPtr _expression, BlockPtr _statement)
        : expression(_expression)
        , cstatement(_statement)
    {}
    ~While() {
        delete expression;
        delete cstatement;
    }
    virtual void print (std::ostream &dst) const override {
        dst << "\n    WHILE [ ";
        expression->print(dst);
        dst << " ]\n    DO [ ";
        cstatement->print(dst);
        dst << " ]";
    }
    
    virtual void generateRISC(std::ostream &dst, Context &context, std::string destReg) const override {
            std::string whilet = make_label("WHILE");
            std::string endt = make_label("END");
            
            label(dst,whilet);
            context.regs.useReg(destReg);
            expression->generateRISC(dst,context,destReg);
            context.regs.freeReg(destReg);
            Three_op(dst,"beq",destReg,"zero",endt);

            context.regs.useReg(destReg);
            cstatement->generateRISC(dst,context,destReg);
            context.regs.freeReg(destReg);
            One_op(dst,"j",whilet);

            label(dst,endt);
    }
};

#endif