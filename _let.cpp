#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     _let
*******************/

_let::_let(std::string name, Expr* val, Expr * rhs) {
    this->name = name;
    this->val = val;
    this->rhs = rhs;
}

bool _let::equals(Expr* rhs){
    return  this->interp() == rhs->interp();
}

int _let::interp() {
    return this->rhs->subst(name, val)->interp(); 
}

bool _let::has_variable() {
    return rhs -> has_variable();
}

Expr* _let::subst(std::string var, Expr* e) {
    rhs->subst(name, val);
}

void _let::print(std::ostream& out) {
    // std::cout << "( _let " << name << "=" << val << " _in " << rhs->print() << ")";
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

