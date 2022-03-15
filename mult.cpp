#include "expr.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      MULT
*******************/

MultExpr::MultExpr(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
};

bool MultExpr::equals(Expr* e){
    MultExpr* e_use = dynamic_cast<MultExpr*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
};

Val* MultExpr::interp() {
    return (this->lhs)->interp() * (this->rhs)->interp();
};

bool MultExpr::has_variable() {
    return (this->lhs)->has_variable() || (this->rhs)->has_variable();
};

Expr* MultExpr::subst(std::string var, Expr* e) {
    return new MultExpr((this->lhs)->subst(var, e), (this->rhs)->subst(var, e)); 
}

void MultExpr::print(std::ostream& output) {
    output << "(";
    lhs -> print(output);
    output << "*";
    rhs -> print(output);
    output << ")";
}

void MultExpr::pretty_print(std::ostream& output) {
    if(this -> lhs -> pretty_print_at() == prec_add || this -> lhs -> pretty_print_at() == prec_let) {
        output << "(";
        this -> lhs -> pretty_print(output);
        output << ")";
    }
    else {
        this -> lhs -> pretty_print(output);
    }

    output << " * ";

    if(this -> rhs -> pretty_print_at() == prec_add) {
        output << "(";
        this -> rhs -> pretty_print(output);
        output << ")";
    }
    else {
        this -> rhs -> pretty_print(output);
    }
}

std::string MultExpr::to_string() {
    std::stringstream output;
    this -> print(output);
    return output.str();
}

precedence_t MultExpr::pretty_print_at(){
    return prec_mult; 
}

/******************
TESTS
*******************/
TEST_CASE("mult") {

    /******************
    interp()
    *******************/
    NumExpr* num1 = new NumExpr(5);
    NumExpr* num2 = new NumExpr(7);
    AddExpr* add1 = new AddExpr(num1, num2);
    MultExpr* mult = new MultExpr(num1, num2);
    CHECK(mult->interp() == 35);

    /******************
    has_variable()
    *******************/
//    CHECK((new MultExpr(new NumExpr(7), new VarExpr("7")))->has_variable() == true);
//    CHECK((new MultExpr(new NumExpr(7), new NumExpr(7)))->has_variable() == false);

    /******************
    subst()
    *******************/
    // CHECK( (new Add(new Var("x"), new Num(7)))
    //    ->subst("x", new Var("y"))
    //    ->equals(new Add(new Var("y"), new Num(7))) );

}
