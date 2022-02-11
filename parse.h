#include "expr.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

class Parse : public Expr {

    public:

        Expr* parse_expr(std::istream& input);

        Expr* parse_num(std::istream& input);
        Expr* parse_var(std::istream& input);
        Expr* parse_add(std::istream& input);
        Expr* parse_mult(std::istream& input);

        Expr* parse_let(std::istream& input);

        //what are these??
        Expr* parse_addend(std::istream& input);
        Expr* parse_multicand(std::istream& input);

        //helpers
        static void skip_whitespace(std::istream& input); 
        static void consume(std::istream& input, int expect);  
        Expr* parse_keyword(std::istream& input); 

};