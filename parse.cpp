#include "parse.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     Parse
*******************/

Expr* parse_expr(std::istream& in) {
    skip_whitespace(in);

    int c = in.peek();
    if((c == '-') || (isdigit(c))) {
        return parse_num(in);
    }
    else if(c == '(') {
        // consume(in, '(');
        Expr* e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();

        if(c != ')') {
            throw std::runtime_error("missing close parenthesis");
            return e;
        }
        else {
            // consume(in, c);
            throw std::runtime_error("invalid input");
        }
    }
}

Expr* parse_num(std::istream& in) {

}

Expr* parse_var(std::istream& in) {

}

Expr* parse_add(std::istream& in) {

}

Expr* parse_mult(std::istream& in) {

}

Expr* parse_let(std::istream& in) {

} 

static void skip_whitespace(std::istream& in) {
    while(1) {
        int c = in.peek();
        if(!isspace(c)) {
            break;
        }
        //consume(in, c);
    }
}