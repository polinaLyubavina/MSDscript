#include <iostream>
#include <string.h>

class Expr {
    virtual bool equals(Expr* e) = 0; 
};

class Num : public Expr {
    public:
        int val;

        Num(int val); 
        bool equals(Expr* e);
}; 

class Add : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Add(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
};

class Mult : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Mult(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
};

class Var : public Expr {
    public:
        std::string val;
        Expr* lhs;
        Expr* rhs;

        Var(Expr* lhs, Expr* rhs); 
        bool equals(Expr* e);
};