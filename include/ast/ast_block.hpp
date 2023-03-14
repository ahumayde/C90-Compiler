#ifndef ast_block_hpp
#define ast_block_hpp

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

#include <memory>

#include "ast.hpp"

class Block;

typedef const Block *BlockPtr;

class Block {
// private:
//     BlockPtr translation_unit;
public:
    virtual ~Block() {}
    //! Tell and expression to print itself to the given stream
    virtual void print(std::ostream &dst) const =0;

    //! Evaluate the tree using the given mapping of variables to numbers
    // virtual void evaluate(std::ostream &dst) const { 
    //     throw std::runtime_error("Not implemented."); 
    // }
    virtual int getSize() const { return 1;}

    // virtual void generateRISC(std::ostream &dst, Scope &scope, int destReg) const {
    //     throw std::runtime_error("Not implemented."); 
    // }
    // virtual std::string getIdentifier() const {}

    // virtual int getConstant() const {}  
};


#endif