#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;

protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left), right(_right)
    {
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getLeft() const
    {
        return left;
    }

    ExpressionPtr getRight() const
    {
        return right;
    }


    /*virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        left->print(dst);
        dst << " ";
        dst << getOpcode();
        dst << " ";
        right->print(dst);
        dst << " )";
    }*/
    
};

class AddOperator : public Operator{
/*protected:
        virtual const char *getOpcode() const override
        {return "+";}*/
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
    virtual int translate(const std::map<std::string, double> &bindings, const std::string dest_reg)const override 
    {
        double left = getLeft()->translate(bindings, "$3");
        double righ = getRight()->translate (bindings, "$4");
        std::cout << "addiu" << dest_reg << " $3 $4" << std::endl;
    }
};

class SubOperator : public Operator{
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
    virtual int translate(const std::map<std::string, double> &bindings, const std::string dest_reg)const override 
    {
        double left = getLeft()->translate(bindings, "$3");
        double righ = getRight()->translate (bindings, "$4");
        std::cout << "subiu" << dest_reg << " $3 $4" << std::endl;
    }
};

class MulOperator : public Operator{
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
        virtual int translate(const std::map<std::string, double> &bindings, const std::string dest_reg)const override 
    {
        double left = getLeft()->translate(bindings, "$3");
        double righ = getRight()->translate (bindings, "$4");
        std::cout << "multu" << dest_reg << " $3 $4" << std::endl;
    }
};

class DivOperator : public Operator{
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
        virtual int translate(const std::map<std::string, double> &bindings, const std::string dest_reg)const override 
    {
        double left = getLeft()->translate(bindings, "$3");
        double righ = getRight()->translate (bindings, "$4");
        std::cout << "divu" << dest_reg << " $3 $4" << std::endl;
    }
};

class LogicalAndOperator : public Operator{
public:
    LogicalAndOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
};

class LogicalOrOperator : public Operator{
public:
    LogicalOrOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
};

class LogicalRightShiftOperator : public Operator{
public:
    LogicalRightShiftOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
};

class LogicalLeftShiftOperator : public Operator{
public:
    LogicalLeftShiftOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right){}
};

#endif
