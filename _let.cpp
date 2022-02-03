#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     _let
*******************/

_let::_let(std::string lhs, Expr* rhs, Expr* body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}

bool _let::equals(Expr* another_expression){
    return  this->interp() == another_expression->interp();
}

int _let::interp() {
    return this -> body -> subst(lhs, rhs) -> interp(); 
}

bool _let::has_variable() {
    return body -> has_variable();
}

Expr* _let::subst(std::string var, Expr* e) {
    body->subst(lhs, rhs);
}

void _let::print(std::ostream& out) {

}

void _let::pretty_print(std::ostream& out) {

}

std::string _let::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t _let::pretty_print_at(){
    
}

/******************
TESTS
*******************/
TEST_CASE("_let") {
    // CHECK(to_string(new _let(new Var("x"), new Num (7))) == "(_let x=7)"); 
}

