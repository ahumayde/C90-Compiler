#ifndef ast_assignment_hpp
#define ast_assignment_hpp
#include "ast_block.hpp"
class Assignment : public Block {
private:
    BlockPtr var;
    std::string op;
    BlockPtr expression;
    
public:
    Assignment(BlockPtr _var,std::string _op , BlockPtr _expression )
        : var(_var)
        , op(_op)
        , expression(_expression)
    {}
    ~Assignment() {
        delete var;
        delete expression;
    }

    std::string getOp() const { return op; }
    BlockPtr getExpression() const { return expression; }

    virtual void print(std::ostream &dst) const override {
        dst << "\n        New Assignment: [ ";
        var->print(dst);
        dst << " Operator: [ ";
        dst << op;
        dst << " ] ";
        expression->print(dst);
        dst << " ]";
    }

    virtual void generateRISC(std::ostream &dst, Context &context, std::string destReg) const override {
        try{
            std::string varname = var->getIdentifier();
            std::string reg = context.regs.nextFreeReg();
            context.regs.useReg(reg);
            expression->generateRISC(dst, context, reg);
            int offset = context.getVarInfo(varname).offset;
            dst << "sw " << reg << ", " << offset << "(s0)" << std::endl;
            context.regs.freeReg(reg);
        }
        
        catch (...) {
            dst<<"Error in Assignment";
        }

    }
 
};


#endif