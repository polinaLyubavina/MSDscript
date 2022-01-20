#include <iostream>
#include <string.h>

class Expr {
    public:
        virtual bool equals(Expr* e) = 0; 
        virtual int interp() = 0; 
        virtual Expr* subst(std::string, Expr*) = 0;
};

class Num : public Expr {
    public:
        int val;

        Num(int val); 
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string, Expr*);
}; 

class Add : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Add(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string, Expr*);
};

class Mult : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Mult(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string, Expr*);
};

class Var : public Expr {
    public:
        std::string val;

        Var(std::string val); 
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string, Expr*);
};