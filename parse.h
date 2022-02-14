#include "expr.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>


Expr* parse(std::istream &input);

Expr* parse_expr(std::istream &input);

Expr* parse_num(std::istream &input);
Expr* parse_var(std::istream &input);

Expr* parse_let(std::istream &input);

Expr* parse_addend(std::istream &input);
Expr* parse_multicand(std::istream &input);

Expr* parse_keyword(std::istream &input); 

static void skip_whitespace(std::istream &input); 
static void consume(std::istream &input, int expect);  
