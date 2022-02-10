#include "parse.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     Parse
*******************/

Expr* parse_expr(std::istream& input) {
    
    skip_whitespace(input);
    int n = input.peek();

    if((n == '-') || (isdigit(n))) {
        return parse_num(input);
    }
    else if(n == '(') {
        // consume(input, '(');
        Expr* e = parse_expr(input);
        skip_whitespace(input);
        n = input.get();

        if(n != ')') {
            throw std::runtime_error("Missing close parenthesis");
            return e;
        }
        else {
            // consume(input, n);
            throw std::runtime_error("Invalid input");
        }
    }
}

Expr* parse_num(std::istream& input) {

    skip_whitespace(input);
    int n = input.peek();

    if((n == '-') || (isdigit(n))) {
        //consume(input, '-');
        return new(Num)(n);
    }

    if(n == '(' || n == ')') {
        // consume((input '(') || (input, ')')) {
            return new(Num)(n);
        }
    }
    else {
        throw std::runtime_error("Invalid input");
        // exit(1);
    }
}

Expr* parse_var(std::istream& input) {

    std::string inputVar;
    skip_whitespace(input);

    if(n == '-') || (isdigit(n)) {
        throw std::runtime_error("Invalid input");
    }

    while(1) {
        char c = in.peek();
        if(!isalpha(c)) {
            inputVar += in.get();
        }
    }

    return new(Var)(inputVar);

}

Expr* parse_add(std::istream& input) {

    

}

Expr* parse_mult(std::istream& input) {

}

Expr* parse_let(std::istream& input) {

} 

static void skip_whitespace(std::istream& input) {
    while(1) {
        int n = input.peek();
        if(!isspace(n)) {
            break;
        }
        //consume(in, n);
    }
}


/******************
TESTS
*******************/
// TEST_CASE("parse") {
//   CHECK_THROWS_WITH( parse_str("()"), "bad input" );
  
//   CHECK( parse_str("(1)")->equals(new Num(1)) );
//   CHECK( parse_str("(((1)))")->equals(new Num(1)) );
  
//   CHECK_THROWS_WITH( parse_str("(1"), "bad input" );
  
//   CHECK( parse_str("1")->equals(new Num(1)) );
//   CHECK( parse_str("10")->equals(new Num(10)) );
//   CHECK( parse_str("-3")->equals(new Num(-3)) );
//   CHECK( parse_str("  \n 5  ")->equals(new Num(5)) );
//   CHECK_THROWS_WITH( parse_str("-"), "invalid input" );
//   // This was some temporary debugging code:
//   //  std::istringstream in("-");
//   //  parse_num(in)->print(std::cout); std::cout << "\n";
  
//   CHECK_THROWS_WITH( parse_str(" -   5  "), "invalid input" );
  
//   CHECK( parse_str("x")->equals(new Var("x")) );
//   CHECK( parse_str("xyz")->equals(new Var("xyz")) );
//   CHECK( parse_str("xYz")->equals(new Var("xYz")) );
//   CHECK_THROWS_WITH( parse_str("x_z"), "invalid input" );
  
//   CHECK( parse_str("x + y")->equals(new Add(new Var("x"), new Var("y"))) );
//   CHECK( parse_str("x * y")->equals(new Mult(new Var("x"), new Var("y"))) );
//   CHECK( parse_str("z * x + y")
//         ->equals(new Add(new Mult(new Var("z"), new Var("x")),
//                          new Var("y"))) );
  
//   CHECK( parse_str("z * (x + y)")
//         ->equals(new Mult(new Var("z"),
//                           new Add(new Var("x"), new Var("y"))) ));
// }