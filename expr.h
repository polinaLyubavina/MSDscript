#include <iostream>
#include <string.h>

typedef enum {
  prec_none,      // = 0
  prec_add,       // = 1
  prec_mult       // = 2
} precedence_t;

class Expr {
    public:
        virtual bool equals(Expr* e) = 0; 
        virtual int interp() = 0; 

        virtual bool has_variable() = 0;
        virtual Expr* subst(std::string var, Expr* e) = 0;

        virtual void print(std::ostream& out) = 0; 
        virtual void pretty_print(std::ostream& out) = 0; 
<<<<<<< HEAD
        virtual void pretty_print_at(std::ostream& out) = 0;
=======
        virtual precedence_t pretty_print_at(std::ostream& out) = 0;
>>>>>>> work

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
<<<<<<< HEAD
        void pretty_print_at(std::ostream& out);
=======
        precedence_t pretty_print_at(std::ostream& out);
>>>>>>> work
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
<<<<<<< HEAD
        void pretty_print_at(std::ostream& out);
=======
        precedence_t pretty_print_at(std::ostream& out);
>>>>>>> work
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
<<<<<<< HEAD
        void pretty_print_at(std::ostream& out);
=======
        precedence_t pretty_print_at(std::ostream& out);
>>>>>>> work
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
<<<<<<< HEAD
        void pretty_print_at(std::ostream& out);
=======
        precedence_t pretty_print_at(std::ostream& out);
        std::string to_string();
};

class _let : public Expr {
    public:
        std::string name;
        Expr* val; 
        Expr* rhs;

        _let(std::string name, Expr* val, Expr* rhs);

        bool equals(Expr* e);
        int interp(); 
        bool has_variable();
        Expr* subst(std::string var, Expr* e);
        void print(std::ostream& out);
        void pretty_print(std::ostream& out);
        precedence_t pretty_print_at(std::ostream& out);
>>>>>>> work
        std::string to_string();
};