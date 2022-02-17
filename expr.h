#include <iostream>
#include <string.h>

typedef enum {
  prec_none,      // = 0
  prec_add,       // = 1
  prec_mult,      // = 2
  prec_let        // = 3
} precedence_t;

class Val;

class Expr {
    public:
        virtual bool equals(Expr* e) = 0; 
        virtual int interp() = 0; 

        virtual bool has_variable() = 0;
        virtual Expr* subst(std::string var, Expr* e) = 0;

        virtual void print(std::ostream& out) = 0; 
        virtual void pretty_print(std::ostream& out) = 0; 
        virtual precedence_t pretty_print_at() = 0;

        virtual std::string to_string() = 0;
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
        precedence_t pretty_print_at();
        std::string to_string();
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
        precedence_t pretty_print_at();
        std::string to_string();
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
        precedence_t pretty_print_at();
        std::string to_string();
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
        precedence_t pretty_print_at();
        std::string to_string();
};

class _let : public Expr {
    public:
        std::string lhs;
        Expr* rhs; 
        Expr* body;

        _let(std::string lhs, Expr* rhs, Expr* body);

        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
        precedence_t pretty_print_at();
        std::string to_string();
};