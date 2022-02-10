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
    return body -> subst(lhs, rhs) -> interp(); 
}

// returns true if rhs or body has a variable
bool _let::has_variable() {
    return this -> rhs -> has_variable() || this -> body -> has_variable();
}

Expr* _let::subst(std::string var, Expr* e) {
    if(lhs.compare(var)) {
        return this;        //if it matches don't change it
    }
    else {
        _let* output = new _let(lhs, rhs -> subst(var, e), body -> subst(var, e));
        return output;
    }
}

void _let::print(std::ostream& out) {
    out << "(_let ";
    out << this -> lhs; 
    out << "=";
    this -> rhs -> print(out);
    out << " _in ";
    out << "(";
    this -> body -> print(out);
    out << ")";
    out << ")";
}

void _let::pretty_print(std::ostream& out) {
    out << "_let ";
    int num_spaces = out.tellp();

    out << this -> lhs;
    out << " = ";
    this -> rhs -> pretty_print(out);

    out << "\n";
    for(int i = 0; i < num_spaces; i++) {
        out << " ";
    }
    out << "_in ";

    this -> body -> pretty_print(out);
}

std::string _let::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t _let::pretty_print_at(){
    return prec_let;
}

/******************
TESTS
*******************/
TEST_CASE("_let") {

    /******************
    equals()
    *******************/
    CHECK((new _let(
                    "x",
                    new Num (7),
                    new Add(new Var("x"), new Num(7))
                )) 
                -> equals(new Num(14)) == true);

    /******************
    print()
    *******************/
//    std::ostream out = "40";
//     CHECK((new _let(
//                     "zu",
//                     new Num(20),
//                     new Mult(new Var("zu"), new Num(2))
//                 ))  
//                 -> print(out) == true);


}

