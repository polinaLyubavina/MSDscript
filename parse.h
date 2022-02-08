#include "expr.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

class Parse : public Expr {

    public:
        void parse_num(std::istream& in);
        void parse_var(std::istream& in);
        void parse_add(std::istream& in);
        void parse_mult(std::istream& in);
        void parse_let(std::istream& in);    

};