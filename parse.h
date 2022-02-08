#include "expr.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

class Parse : public Expr {

    public:
        Expr* parse_expr(std::istream& in);
        Expr* parse_num(std::istream& in);
        Expr* parse_var(std::istream& in);
        Expr* parse_add(std::istream& in);
        Expr* parse_mult(std::istream& in);
        Expr* parse_let(std::istream& in);
        static void skip_whitespace(std::istream& in);    

};