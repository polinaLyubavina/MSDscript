#include <iostream>
#include <string.h>

class Expr {
    public:
        virtual bool equals(Expr* e) = 0; 
        virtual int interp() = 0; 
        virtual bool has_variable() = 0;
        virtual Expr* subst(std::string var, Expr* e) = 0;
        virtual void print(std::ostream& out) = 0; 
        virtual void pretty_print(std::ostream& out) = 0; 
};

class Num : public Expr {
    public:
        int val;

        Num(int val); 
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
}; 

class Add : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Add(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
};

class Mult : public Expr {
    public:
        Expr* lhs;
        Expr* rhs;

        Mult(Expr* lhs, Expr* rhs);
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
};

class Var : public Expr {
    public:
        std::string val;

        Var(std::string val); 
        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
};