#ifndef val_h

#include <iostream>
#include <string.h>

#include "pointer.h"
#include "env.h"

#endif

class Expr;

CLASS(Val) {
    public:
        virtual bool equals(Val* input) = 0; 
        virtual PTR(Val) add_to(Val* input) = 0;
        virtual PTR(Expr) to_expr() = 0;
        virtual PTR(Val) call(Val* actual_argument) = 0;
        virtual PTR(Val) mult_to(Val* input) = 0;
//        virtual Val* interp() = 0;
        virtual std::string to_string() = 0;

};

class NumVal : public Val {
    public:
        int val;

        //constructor
        NumVal(int input);
    
        bool equals(PTR(Val) input);
        PTR(Val) add_to(PTR(Val) input);
        PTR(Expr) to_expr();
        PTR(Val) call(PTR(Val) actual_argument);
        PTR(Val) mult_to(PTR(Val) input);
        std::string to_string();
//        Val* interp();
};

class BoolVal : public Val {
    public:
        bool input;
        
        //constructor
        BoolVal(bool input);
    
        bool equals(PTR(Val) input);
        PTR(Val) add_to(PTR(Val) input);
        PTR(Expr) to_expr();
        PTR(Val) call(PTR(Val) actual_argument);
        PTR(Val) mult_to(PTR(Val) input);
        std::string to_string();
//        Val* interp();
};

class FunVal : public Val {
    public:
        std::string formal_arg;
        PTR(Expr) body;
        PTR(Env) env;
    
        //constructor
        FunVal(std::string formal_arg, PTR(Expr) body);
    
        bool equals(PTR(Val) input);
        PTR(Val) add_to(PTR(Val) input);
        PTR(Expr) to_expr();
        PTR(Val) call(PTR(Val) actual_argument);
        PTR(Val) mult_to(PTR(Val) input);
        std::string to_string();
//        Val* interp();
};
