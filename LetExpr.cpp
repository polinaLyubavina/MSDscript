#include "expr.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *     _let
*******************/

LetExpr::LetExpr(std::string lhs, Expr* rhs, Expr* body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}

bool LetExpr::equals(Expr* another_expression){
    return  this->interp() == another_expression->interp();
}

Val* LetExpr::interp() {
    return body -> subst(lhs, new NumExpr(rhs -> interp())) -> interp();
}

// returns true if rhs or body has a variable
bool LetExpr::has_variable() {
    return (this -> body -> has_variable());
}

Expr* LetExpr::subst(std::string var, Expr* e) {
    if(lhs.compare(var)) {
        return this;        //if it matches don't change it
    }
    else {
        LetExpr* output = new LetExpr(lhs, rhs -> subst(var, e), body -> subst(var, e));
        return output;
    }
}

void LetExpr::print(std::ostream& out) {
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

void LetExpr::pretty_print(std::ostream& out) {
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

std::string LetExpr::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t LetExpr::pretty_print_at(){
    return prec_let;
}

/******************
TESTS
*******************/
TEST_CASE("_let") {

    /******************
    equals()
    *******************/
    CHECK((new LetExpr(
                    "x",
                    new NumExpr (7),
                    new AddExpr(new VarExpr("x"), new NumExpr(7))
                )) 
                -> equals(new NumExpr(14)) == true);

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

