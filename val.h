#include <iostream>
#include <string.h>
#include "expr.h"

class Expr;

class Val {
    public:
        virtual bool equals(Val* input) = 0; 
        virtual std::string to_string() = 0;
        virtual Val* add_to(Val* input);
        virtual Expr* to_expr() = 0;
};

class NumVal : public Val {
    public:
        int val;

        NumVal(int input);
        bool equals(Val* input); 
        std::string to_string();
        Val* add_to(Val* input);
        Expr* to_expr();
};
