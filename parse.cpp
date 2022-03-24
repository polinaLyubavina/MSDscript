#include "parse.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     Parse
*******************/

void skip_whitespace(std::istream& input) {
    while(1) {
        int n = input.peek();
        if(!isspace(n)) {
            break;
        }
        consume(input, n);
    }
}

void consume(std::istream& input, int expect) {
    int c = input.get();
    if(c != expect) {
        throw std::runtime_error("Consume can't eat a mismatch");
    }
}

PTR(Expr) parse(std::istream &input) {
    skip_whitespace(input);
    PTR(Expr) e = parse_expr(input);
    return e;
}

PTR(Expr) parse_fun(std::istream& input) {
    skip_whitespace(input);
     std::string formal_arg;
    
     if (input.peek() == '('){
         consume(input, '(');
         skip_whitespace(input);
         formal_arg = parse_var(input) -> to_string();
         skip_whitespace(input);
         
         int c = input.get();
         if (c!= ')'){
             throw std::runtime_error("missing close parenthesis");
         }
     }
     skip_whitespace(input);
     PTR(Expr) body = parse_expr(input);
     return NEW(FunExpr)(formal_arg, body);
}

PTR(Expr) parse_helper (std::istream& input) {
    skip_whitespace(input);
    int c = input.peek();
    
    if((c=='-') || isdigit(c)){
        return parse_num(input);
        
    } else if (c == '('){
        consume(input, '(');
        PTR(Expr)e = parse_expr(input);
        skip_whitespace(input);
        c = input.get();
        if (c!= ')'){
            throw std::runtime_error("missing close parenthesis");
        }
        return e;
        
    } else if (isalpha(c)){
        return parse_var(input);
        
    } else if ( c == '_'){
        std::string kw = parse_keyword(input);
        
        if(kw == "_let"){
            return parse_let(input);
        } else if (kw == "_true"){
            return NEW(BoolExpr)(true);
        } else if (kw == "_false"){
            return NEW(BoolExpr)(false);
        } else if (kw == "_if"){
            return parse_if(input);
        } else if (kw == "_fun"){
            return parse_fun(input);
        }else {
            throw std::runtime_error("can't parse keyword");
        }
    }
    else {
        throw std::runtime_error("can't parse keyword");
    }
}

PTR(Expr) parse_str(std::string s) {
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

PTR(Expr) parse_comparg(std::istream& input) {
    PTR(Expr) e = parse_addend(input);
    skip_whitespace(input);

    int c = input.peek();

    if(c == '+') {
        consume(input, '+');
        PTR(Expr) rhs = parse_expr(input);
        
        return NEW(AddExpr)(e, rhs);
    }
    else {
        return e;
    }
}

PTR(Expr) parse_expr(std::istream& input) {
    PTR(Expr) e = parse_comparg(input);
    skip_whitespace(input);
    int c = input.peek();
    
    if(c == '=') {
        consume(input, '=');
        c = input.peek();
        
        if(c == '=') {
           consume(input, '=');
            PTR(Expr) rhs = parse_expr(input);
            return NEW(EqulExpr)(e, rhs);
        }
        else {
            throw std::runtime_error("finish the equal sign '==' symbol");
        }
    }
    else {
        return e;
    }
}

static std::string parse_keyword(std::istream& input) {
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
                    c = input.get();
                    if(c == ' ') {
                        return "_let ";
                    }
                }
            }
        }
        //check for _in
        else if(c == 'i') {
            c = input.get();
            if(c == 'n') {
                c = input.get();
                if(c == ' ') {
                    return "_in ";
                }
            }
        }
        else {
            throw std::runtime_error("Invalid keyword");
        }
    }
    //check for '='
    if(c == '=') {
        return "=";
    }
    else {
        throw std::runtime_error("Invalid structure");
    }
}



PTR(Expr) parse_num(std::istream& input) {
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
    return NEW(NumExpr)(n);
}

PTR(Expr) parse_var(std::istream& input) {
    std::string outputVar = var_helper(input);
    return NEW(VarExpr)(outputVar);
}

PTR(Expr) parse_let(std::istream& input) {
    std::string lhs;
    PTR(Expr) rhs;
    PTR(Expr) body;
    skip_whitespace(input);

    if(parse_keyword(input).compare("_let ") == 0) {
        skip_whitespace(input);
        std::string outputVar = var_helper(input);
        lhs = outputVar;
    }
    else {
        throw std::runtime_error("Invalid _let lhs input");
    }
    
    if(parse_keyword(input).compare("_in ") == 0) {
        skip_whitespace(input);
        body = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid _let body input");
    }

    if(parse_keyword(input).compare("=") == 0) {
        rhs = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid _let rhs input");
    }
    return NEW(LetExpr)(lhs, rhs, body);
}

PTR(Expr) parse_addend(std::istream& input) {
    skip_whitespace(input);
    PTR(Expr) e = parse_expr(input);
    int n = input.peek();
    
    if((n == '-') || (isdigit(n))) {
        return parse_num(input);
    }
    else if(n == '(') {
        consume(input, '(');
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
    return e;
}

PTR(Expr) parse_multicand(std::istream& input) {
    skip_whitespace(input); 
    int c = input.peek();
    PTR(Expr) e = parse_expr(input);

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
    
    return e;
}

PTR(Expr) parse_if(std::istream& input) {
    skip_whitespace(input);
    PTR(Expr) test_input = parse_expr(input);
    int c = input.peek();

    if(parse_keyword(input) != "_then") {
        throw std::runtime_error("not what we expected");
    }
    
    skip_whitespace(input);
    PTR(Expr) then_input = parse_expr(input);
    skip_whitespace(input);
    c = input.peek();
    
    if(parse_keyword(input) != "_else") {
        throw std::runtime_error("not what we expected");
    }
    
    PTR(Expr) else_input = parse_expr(input);
    return NEW(IfExpr)(test_input, then_input, else_input); 
}


/******************
TESTS
*******************/
TEST_CASE("parse") {
  CHECK_THROWS_WITH( parse_str("()"), "bad input" );
  
  CHECK( parse_str("(1)") -> equals(NEW(NumExpr)(1) ) );
  CHECK( parse_str("(((1)))") -> equals(NEW(NumExpr)(1) ) );
  
  CHECK_THROWS_WITH( parse_str("(1"), "bad input" );
  
  CHECK( parse_str("1") -> equals(NEW(NumExpr)(1)) );
  CHECK( parse_str("10") -> equals(NEW(NumExpr)(10) ) );
  CHECK( parse_str("-3") -> equals(NEW(NumExpr)(-3) ) );
  CHECK( parse_str("  \n 5  ") -> equals(NEW(NumExpr)(5) ) );
  CHECK_THROWS_WITH( parse_str("-"), "invalid input" );
  // This was some temporary debugging code:
  //  std::istringstream in("-");
  //  parse_num(in) -> print(std::cout); std::cout << "\n";
  
  CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
  
  CHECK( parse_str("x") -> equals(NEW(VarExpr)("x") ) );
  CHECK( parse_str("xyz") -> equals(NEW(VarExpr)("xyz") ) );
  CHECK( parse_str("xYz") -> equals(NEW(VarExpr)("xYz") ) );
  CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );
  
  CHECK( parse_str("x + y") -> equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) );
  CHECK( parse_str("x * y") -> equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) );
  CHECK( parse_str("z * x + y")
        -> equals(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("z"), NEW(VarExpr)("x") ),
                              NEW(VarExpr)("y") ) ) );
  
  CHECK( parse_str("z * (x + y)")
        -> equals(NEW(MultExpr)(NEW(VarExpr)("z"),
                               NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) ) );
}
