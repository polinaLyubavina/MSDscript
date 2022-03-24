#ifndef parse_h

#include "expr.h"

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

#endif

PTR(Expr) parse(std::istream &input);

PTR(Expr) parse_expr(std::istream &input);

PTR(Expr) parse_num(std::istream &input);
PTR(Expr) parse_var(std::istream &input);

PTR(Expr) parse_let(std::istream& input);

PTR(Expr) parse_if(std::istream& input);

PTR(Expr) parse_addend(std::istream &input);
PTR(Expr) parse_multicand(std::istream &input);

static std::string parse_keyword(std::istream &input); 
static void skip_whitespace(std::istream &input); 
static void consume(std::istream &input, int expect);  
PTR(Expr) parse_str(std::string s);
std::string var_helper(std::istream& input);
PTR(Expr) parse_helper (std::istream& input);
