#include <iostream>
#include <string.h>

class Expr {
    virtual bool equals(Expr* e) = 0; 
};

class Num : public Expr {
    int val;

    bool equals(Expr* e);
}; 

class Add : public Expr {
    Expr* lhs;
    Expr* rhs;

    bool equals(Expr* e);
};

class Mult : public Expr {
    Expr* lhs;
    Expr* rhs;

    bool equals(Expr* e);
};

class Var : public Expr {
    std::string val;
    Expr* lhs;
    Expr* rhs;

    bool equals(Expr* e);
};