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

void consume(std::istream& input, char expect) {
   
    int c; 
    
    if(input.peek() == expect) {
        c = input.get();
    }
    else {
        throw std::runtime_error("Invalid Input");
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
         
         formal_arg = var_helper(input);
         skip_whitespace(input);
         int c = input.get();
         
         if (c != ')'){
             throw std::runtime_error("Invalid Input");
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
        
        if (c != ')'){
            throw std::runtime_error("Invalid Input");
        }
        
        return e;
        
    } else if (isalpha(c)){
        
        return parse_var(input);
        
    } else if ( c == '_'){
        
        std::string kw = parse_keyword(input);
        
        if(kw.compare("_let") == 0){
            return parse_let(input);
        }
        
        else if (kw.compare("_true") == 0){
            return NEW(BoolExpr)(true);
        }
        
        else if (kw.compare("_false") == 0){
            return NEW(BoolExpr)(false);
        }
        
        else if (kw.compare("_if") == 0){
            return parse_if(input);
        }
        
        else if (kw.compare("_fun") == 0){
            return parse_fun(input);
        }
        
        else {
            throw std::runtime_error("Invalid Input");
        }
    }
    
    else {
        throw std::runtime_error("Invalid Input");
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
        throw std::runtime_error("Invalid Input");
    }
    
    while(1) {
        char c = input.peek();
        
        if (c == '_') {
            throw std::runtime_error("Invalid Input");
        }
        
        else if(!isalpha(c)) {
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
        PTR(Expr) rhs = parse_comparg(input);
        
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
           
            return NEW(EqualExpr)(e, rhs);
        }
        else {
            throw std::runtime_error("Invalid Input");
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
                    return "_let";
                }
            }
        }
        
        //check for _false
        else if(c == 'f') {
            c = input.get();
            
            if(c == 'a') {
                c = input.get();
                
                if(c == 'l') {
                    c = input.get();
                    
                    if(c == 's') {
                        c = input.get();
                        
                        if(c == 'e') {
                            return "_false";
                        }
                    }
                }
            }
            
            //check for _fun
            else if(c == 'u') {
                c = input.get();
                
                if(c == 'n') {
                    return "_fun";
                }
            }
        }
        
        //check for _true
        else if(c == 't') {
            c = input.get();
            
            if(c == 'r') {
                c = input.get();
                
                if(c == 'u') {
                    c = input.get();
                    
                    if(c == 'e') {
                        return "_true";
                    }
                }
            }
            
            //check for _then
            else if(c == 'h') {
                c = input.get();
                
                if(c == 'e') {
                    c = input.get();

                    if(c == 'n') {
                        return "_then";
                    }
                }
            }
        }
        
        //check for _in
        else if(c == 'i') {
            c = input.get();
            
            if(c == 'n') {
                return "_in";
            }
            
            else if(c == 'f') {
                return "_if";
            }
        }
        
        //check for _else
        else if(c == 'e') {
            c = input.get();
            
            if(c == 'l') {
                c = input.get();
                
                if(c == 's') {
                    c = input.get();

                    if(c == 'e') {
                        return "_else";
                    }
                }
            }
        }
        
        else {
            throw std::runtime_error("Invalid Input");
        }
    }
    
    //check for '='
    if(c == '=') {
        return "=";
    }
    
    else {
        throw std::runtime_error("Invalid Input");
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
        if (n == 0) {
            throw std::runtime_error("Invalid Input");
        }
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
    
    lhs = var_helper(input);
    skip_whitespace(input);

    if(parse_keyword(input).compare("=") == 0) {
        skip_whitespace(input);
        rhs = parse_expr(input);
        skip_whitespace(input);
    }
    else {
        throw std::runtime_error("Invalid Input");
    }
    
    skip_whitespace(input);
    
    if(parse_keyword(input).compare("_in") == 0) {
        skip_whitespace(input);
        body = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid Input");
    }
    
    return NEW(LetExpr)(lhs, rhs, body);
}


PTR(Expr) parse_addend(std::istream& input) {
    
    skip_whitespace(input);
    PTR(Expr) e = parse_multicand(input);    //sends parse_expr into loop
    skip_whitespace(input);
    
    int c = input.peek();

    if(c == '*') {
        
        consume(input, '*');
        PTR(Expr) rhs = parse_addend(input);
        
        return NEW(MultExpr)(e, rhs);
        
    }
    
    return e;
}


PTR(Expr) parse_multicand(std::istream& input) {

    
    PTR(Expr) e;
    PTR(Expr) actual_arg;
    
    e = parse_helper(input);
    
    skip_whitespace(input);
    
    if (input.peek() == '(') {
        consume(input, '(');
        actual_arg = parse_expr(input);
        consume(input, ')');
        e = NEW (CallExpr)(e, actual_arg);
    }
    
    skip_whitespace(input);
    
    return e;
}

PTR(Expr) parse_if(std::istream& input) {
    
    PTR(Expr) test_expr;
    PTR(Expr) then_expr;
    PTR(Expr) else_expr;
   
    skip_whitespace(input);
    test_expr = parse_expr(input);
    skip_whitespace(input);
    
    if(parse_keyword(input).compare("_then") == 0) {
        skip_whitespace(input);
        then_expr = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid Input");
    }
    
    skip_whitespace(input);
    
    if(parse_keyword(input).compare("_else") == 0) {
        skip_whitespace(input);
        else_expr = parse_expr(input);
    }
    else {
        throw std::runtime_error("Invalid Input");
    }
    
    return NEW(IfExpr)(test_expr, then_expr, else_expr);
}


/******************
TESTS
*******************/
TEST_CASE("Parser") {
    
    SECTION("Invalid Input") {
        CHECK_THROWS_WITH( parse_str("()"), "Invalid Input" );
        CHECK_THROWS_WITH( parse_str("(1"), "Invalid Input" );
        CHECK_THROWS_WITH( parse_str(" -   5  "), "Invalid Input" );
        CHECK_THROWS_WITH( parse_str("x_z"), "Invalid Input" );
        CHECK_THROWS_WITH( parse_str("-"), "Invalid Input" );
    }
    
    SECTION("NumExpr") {
        CHECK( parse_str("1") -> equals(NEW(NumExpr)(1)) );
        CHECK( parse_str("10") -> equals(NEW(NumExpr)(10) ) );
        CHECK( parse_str("-3") -> equals(NEW(NumExpr)(-3) ) );
        CHECK( parse_str("  \n 5  ") -> equals(NEW(NumExpr)(5) ) );
        CHECK( parse_str("(1)") -> equals(NEW(NumExpr)(1) ) );
        CHECK( parse_str("(((1)))") -> equals(NEW(NumExpr)(1) ) );
    }
    
    SECTION("VarExpr") {
        CHECK( parse_str("x") -> equals(NEW(VarExpr)("x") ) );
        CHECK( parse_str("xyz") -> equals(NEW(VarExpr)("xyz") ) );
        CHECK( parse_str("xYz") -> equals(NEW(VarExpr)("xYz") ) );
        CHECK( parse_str("then") -> equals(NEW(VarExpr)("then") ) );
    }
    
    SECTION("AddExpr") {
        CHECK( parse_str("x + y") -> equals(NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) );
        CHECK( parse_str("z * x + y")
            -> equals(NEW(AddExpr)(NEW(MultExpr)(NEW(VarExpr)("z"), NEW(VarExpr)("x") ),
                                  NEW(VarExpr)("y") ) ) );
    }
    
    SECTION("MultExpr") {
        CHECK( parse_str("x * y") -> equals(NEW(MultExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) );
        CHECK( parse_str("z * (x + y)")
              -> equals(NEW(MultExpr)(NEW(VarExpr)("z"),
                                     NEW(AddExpr)(NEW(VarExpr)("x"), NEW(VarExpr)("y") ) ) ) );
    }
    
    SECTION("BoolExpr") {
        CHECK(parse_str("_false") -> equals(NEW(BoolExpr)(false)));
        CHECK(parse_str("_true") -> equals(NEW(BoolExpr)(true)));
    }
    
    SECTION("LetExpr") {
        CHECK( parse_str("_let x = _false _in x + 5")
                  -> equals( NEW(LetExpr)(
                                          "x",
                                          NEW(BoolExpr)(false),
                                          NEW(AddExpr)(
                                                       NEW(VarExpr)("x"),
                                                       NEW(NumExpr)(5)
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_let y = _true _in y")
                  -> equals( NEW(LetExpr)(
                                          "y",
                                          NEW(BoolExpr)(true),
                                          NEW(VarExpr)("y")
                                          )
                            )
              );
        CHECK( parse_str("_let x = 20 _in x + 50")
                  -> equals( NEW(LetExpr)(
                                          "x",
                                          NEW(NumExpr)(20),
                                          NEW(AddExpr)(
                                                       NEW(VarExpr)("x"),
                                                       NEW(NumExpr)(50)
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_let y = 255 _in y + y")
                  -> equals( NEW(LetExpr)(
                                          "y",
                                          NEW(NumExpr)(255),
                                          NEW(AddExpr)(
                                                       NEW(VarExpr)("y"),
                                                       NEW(VarExpr)("y")
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_let z = 5 _in z * z")
                  -> equals( NEW(LetExpr)(
                                          "z",
                                          NEW(NumExpr)(5),
                                          NEW(MultExpr)(
                                                       NEW(VarExpr)("z"),
                                                       NEW(VarExpr)("z")
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_let w = 10 _in w * 10")
                  -> equals( NEW(LetExpr)(
                                          "w",
                                          NEW(NumExpr)(10),
                                          NEW(MultExpr)(
                                                       NEW(VarExpr)("w"),
                                                       NEW(NumExpr)(10)
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_let v = 5 _in _let u = 10 _in v * 5")
                  -> equals( NEW(LetExpr)(
                                          "v",
                                          NEW(NumExpr)(5),
                                          NEW(LetExpr)("u",
                                                       NEW(NumExpr)(10),
                                                       NEW(MultExpr)(
                                                                    NEW(VarExpr)("v"),
                                                                    NEW(NumExpr)(5)
                                                                    )
                                                       )
                                          )
                            )
              );
            
            
    }
    
    SECTION("IfExpr") {
        CHECK( parse_str("_if _false _then 1 _else 2")
                  -> equals( NEW(IfExpr)(
                                         NEW(BoolExpr)(false),
                                         NEW(NumExpr)(1),
                                         NEW(NumExpr)(2)
                                         )
                            )
              );
        CHECK( parse_str("_if _true _then 1 _else 2")
                  -> equals( NEW(IfExpr)(
                                         NEW(BoolExpr)(true),
                                         NEW(NumExpr)(1),
                                         NEW(NumExpr)(2)
                                         )
                            )
              );
        CHECK( parse_str("_if _true _then 5 _else x")
                  -> equals( NEW(IfExpr)(
                                         NEW(BoolExpr)(true),
                                         NEW(NumExpr)(5),
                                         NEW(VarExpr)("x")
                                         )
                            )
              );
        CHECK( parse_str("_if 5 + 15 == 25 _then _true _else _false")
                  -> equals( NEW(IfExpr)(
                                         NEW(EqualExpr)(
                                                        NEW(AddExpr)(
                                                                     NEW(NumExpr)(5),
                                                                     NEW(NumExpr)(15)),
                                                        NEW(NumExpr)(25)),
                                         NEW(BoolExpr)(true),
                                         NEW(BoolExpr)(false)
                                         )
                            )
              );
        CHECK( parse_str("_if 15 + 15 == 30 _then _true _else _false")
                  -> equals( NEW(IfExpr)(
                                         NEW(EqualExpr)(
                                                        NEW(AddExpr)(
                                                                     NEW(NumExpr)(15),
                                                                     NEW(NumExpr)(15)),
                                                        NEW(NumExpr)(30)),
                                         NEW(BoolExpr)(true),
                                         NEW(BoolExpr)(false)
                                         )
                            )
              );
    }
    
    SECTION("EqualExpr") {

    }
    
    SECTION("FunExpr") {
        CHECK( parse_str("_fun (x) y + 25")
                  -> equals( NEW(FunExpr)(
                                          "x",
                                          NEW(AddExpr)(
                                                       NEW(VarExpr)("y"),
                                                       NEW(NumExpr)(25)
                                                       )
                                          )
                            )
              );
        CHECK( parse_str("_fun (z) z + 15")
                  -> equals( NEW(FunExpr)(
                                          "z",
                                          NEW(AddExpr)(
                                                        NEW(VarExpr)("z"),
                                                        NEW(NumExpr)(15)
                                                        )
                                          )
                            )
              );
        CHECK( parse_str("(_fun (w) w + 20) (5)")
              -> equals( NEW(CallExpr)(
                                       NEW(FunExpr)(
                                                    "w",
                                                    NEW(AddExpr)(
                                                                 NEW(VarExpr)("w"),
                                                                 NEW(NumExpr)(20)
                                                                 )
                                                    ),
                                       NEW(NumExpr)(5)
                                       )
                        )
              );
        
        CHECK( parse_str("(_fun (w) x + y) (5)")
              -> equals( NEW(CallExpr)(
                                       NEW(FunExpr)(
                                                    "w",
                                                    NEW(AddExpr)(
                                                                 NEW(VarExpr)("x"),
                                                                 NEW(VarExpr)("y")
                                                                 )
                                                    ),
                                       NEW(NumExpr)(5)
                                       )
                        )
              );
    }

  // This was some temporary debugging code:
  //  std::istringstream in("-");
  //  parse_num(in) -> print(std::cout); std::cout << "\n";
}
