#include "parse.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     Parse
*******************/

Expr* parse(std::istream &input) {
    skip_whitespace(input);
    Expr* e = parse_expr(input);
    return e; 
}

Expr* parse_num(std::istream& input) {

    skip_whitespace(input);
    int n = 0;
    bool negative = false;

    if(input.peek() == '-') {
        negative = true;
        consume(input, '-');
    }

    while(1) {
        int c = input.peek();

        if(isdigit(c)) {
            consume(input, c);
            n = n*10 + (c - '0');
        }
        else {
            break;
        }
    }

    if(negative) {
        n = -n;
    }

    return new Num(n); 

}

Expr* parse_str(std::string s) {
    std::stringstream input(s);
    return parse(input);
}

//gives back a string that Var & _let can use
std::string var_helper(std::istream& input) {
    std::string outputVar;
    skip_whitespace(input);

    if(input.peek() == '-') {  
        throw std::runtime_error("Invalid input");
    } 

    while(1) {
        char c = input.peek();
        if(!isalpha(c)) {
            break;
        }
        else {
            consume(input, c);
            outputVar += c;
        } 
    }
    return outputVar;
}

Expr* parse_var(std::istream& input) {
    std::string outputVar = var_helper(input);
    return new Var(outputVar);
}

Expr* parse_let(std::istream& input) { 
    std::string lhs;
    Expr* rhs;
    Expr* body;

    //check if keyword is '_let'
    if(parse_keyword(input) == '_let ') {
        skip_whitespace(input);
        std::string outputVar = var_helper(input);
        lhs = outputVar;
    }
    else {
        throw std::runtime_error("Invalid _let lhs input");
    }

    //check if keyword is '_in'
    if(parse_keyword(input) == '_in ') {
        skip_whitespace(input);
        body = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid _let body input");
    }

    //check if keyword is '='
    skip_whitespace(input);
    if(parse_keyword(input) == '=') {
        rhs = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid _let rhs input");
    }

    //return new _let() with given input
} 

void skip_whitespace(std::istream& input) {
    while(1) {
        int n = input.peek();
        if(!isspace(n)) {
            break;
        }
        consume(input, n);
    }
}

//consume is a hungry function that eats an input before going to the next one
void consume(std::istream& input, int expect) {
    int c = input.get();                           
    if(c != expect) {
        throw std::runtime_error("Consume can't eat a mismatch");
    }
}

//parse_keyword() works for finding keywords _let and _in in the input
static char parse_keyword(std::istream& input) {

    skip_whitespace(input);
    char c = input.get();

    if(c == '_') {
        //check for _let
        c = input.get();
        if(c == 'l') {
            c = input.get();
            if(c == 'e') {
                c = input.get();
                if(c == 't') {
                    c == input.get();
                    if(c == ' ') {
                        return '_let ';
                    }
                }
            }
        }
        //check for _in
        else if(c == 'i') {
            c == input.get();
            if(c == 'n') {
                c == input.get();
                if(c == ' ') {
                    return '_in ';
                }
            }
        }
        else {
            throw std::runtime_error("Invalid keyword");
        }
    }
    //check for '='
    if(c == '=') {
        return '=';
    }
    else {
        throw std::runtime_error("Invalid structure");
    }
}

Expr* parse_addend(std::istream& input) {

    skip_whitespace(input);

    int n = input.peek();

    if((n == '-') || (isdigit(n))) {
        return parse_num(input);
    }
    
    else if(n == '(') {

        consume(input, '(');
        Expr* e = parse_expr(input);
        skip_whitespace(input);
        n = input.get(); 

        if(n != ')') {
            throw std::runtime_error("Missing close parenthesis");
            return e;
        }
        else {
            consume(input, n);
            throw std::runtime_error("Invalid input");
        }
    }

}

Expr* parse_multicand(std::istream& input) {

    skip_whitespace(input); 
    int c = input.peek(); 

    //if input is digit
    if((isdigit(c)) || (c == '-')) {
        return parse_num(input);
    }
    //if input is variable
    else if(isalpha(c)) {
        return parse_var(input);
    }
    //if input is an expression
    else if(c == '(') {
        consume(input, '(');
        Expr* e = parse_expr(input);
        consume(input, ')');
        if(c != ')') {
            std::runtime_error("Missing close paranthesis");
        }
        return e;
    }
    else {
        consume(input, c);
        throw std::runtime_error("Invalid input");
    }
}

Expr* parse_expr(std::istream& input) {

    Expr* e;

    e = parse_addend(input);

    skip_whitespace(input);

    int c = input.peek();

    if(c == '+') {

        consume(input, '+');
        Expr* rhs = parse_expr(input);
        return new Add(e, rhs);
    }
    else {
        return e;
    }
}


/******************
TESTS
*******************/
TEST_CASE("parse") {
  CHECK_THROWS_WITH( parse_str("()"), "bad input" );
  
  CHECK( parse_str("(1)")->equals(new Num(1)) );
  CHECK( parse_str("(((1)))")->equals(new Num(1)) );
  
  CHECK_THROWS_WITH( parse_str("(1"), "bad input" );
  
  CHECK( parse_str("1")->equals(new Num(1)) );
  CHECK( parse_str("10")->equals(new Num(10)) );
  CHECK( parse_str("-3")->equals(new Num(-3)) );
  CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
  CHECK_THROWS_WITH( parse_str("-"), "invalid input" );
  // This was some temporary debugging code:
  //  std::istringstream in("-");
  //  parse_num(in)->print(std::cout); std::cout << "\n";
  
  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
  
  CHECK( parse_str("x")->equals(new Var("x")) );
  CHECK( parse_str("xyz")->equals(new Var("xyz")) );
  CHECK( parse_str("xYz")->equals(new Var("xYz")) );
  CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );
  
  CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );
  CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );
  CHECK( parse_str("z * x + y")
        ->equals(new Add(new Mult(new Var("z"), new Var("x")),
                         new Var("y"))) );
  
  CHECK( parse_str("z * (x + y)")
        ->equals(new Mult(new Var("z"),
                          new Add(new Var("x"), new Var("y"))) ));
}