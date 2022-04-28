#ifndef expr_h

#include <iostream>
#include <string.h>

#include "pointer.h"
#include "env.h"

#endif

typedef enum {
    prec_none,      // = 0
    prec_bool,      // = 1
    prec_add,       // = 2  +
    prec_mult,      // = 3  *
    prec_let,       // = 4
    prec_if,        //5
    prec_fun,       //6
    prec_equal      //7
} precedence_t;

class Val;

//Expr is a base class. It is an abstract (virtual) class & shoudn't be instantiated by itself.
CLASS(Expr) {
    
    public:
        virtual ~Expr() { }
        virtual bool equals(PTR(Expr) compared_against) = 0;
        virtual PTR(Val) interp(PTR(Env) env) = 0;
        virtual std::string to_string() = 0;
        virtual void print(std::ostream& output) = 0;
        virtual void pretty_print(std::ostream& output) = 0;
        virtual void pretty_print_at(std::ostream& out, int precedence) = 0;
};

class NumExpr : public Expr {
    public:
        int val;

        //constructor
        NumExpr(int val);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class AddExpr : public Expr {
    public:
        PTR(Expr) lhs;
        PTR(Expr) rhs;

        //constructor
        AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class MultExpr : public Expr {
    public:
        PTR(Expr) lhs;
        PTR(Expr) rhs;
    
        //constructor
        MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class VarExpr : public Expr {
    public:
        std::string val;
    
        //constructor
        VarExpr(std::string val);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class LetExpr : public Expr {
    public:
        std::string lhs;
        PTR(Expr) rhs;
        PTR(Expr) body;

        //constructor
        LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body);
        
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class BoolExpr : public Expr {
    public:
        bool val;
       
        //constructor
        BoolExpr(bool input);
        
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class EqualExpr : public Expr {
    public:
        PTR(Expr) lhs;
        PTR(Expr) rhs;

        //constructor
        EqualExpr(PTR(Expr) lhs, PTR(Expr) rhs);
        
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class IfExpr : public Expr {
    public:
        PTR(Expr) test_input;
        PTR(Expr) then_input;
        PTR(Expr) else_input;

        //constructor
        IfExpr(PTR(Expr) input, PTR(Expr) then_input, PTR(Expr) else_input);
        
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class FunExpr : public Expr {
    public:
        std::string formal_arg;
        PTR(Expr) body;
    
        //constructor
        FunExpr(std::string formal_arg, PTR(Expr) body);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};

class CallExpr : public Expr {
    public:
        PTR(Expr) to_be_called;
        PTR(Expr) actual_arg;
    
        //constructor
        CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);
    
        bool equals(PTR(Expr) compared_against);
        PTR(Val) interp(PTR(Env) env);
        void print(std::ostream& output);
        void pretty_print(std::ostream& output);
        void pretty_print_at(std::ostream& out, int precedence);
        std::string to_string();
};
