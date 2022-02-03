#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      MULT
*******************/

Mult::Mult(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
};

bool Mult::equals(Expr* e){
    Mult* e_use = dynamic_cast<Mult*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
};

int Mult::interp() {
    return (this->lhs)->interp() * (this->rhs)->interp();
};

bool Mult::has_variable() {
    return (this->lhs)->has_variable() || (this->rhs)->has_variable(); 
};

Expr* Mult::subst(std::string var, Expr* e) {
    return new Mult((this->lhs)->subst(var, e), (this->rhs)->subst(var, e)); 
}

void Mult::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "*";
    rhs -> print(out);
    out << ")";
}

void Mult::pretty_print(std::ostream& out) {
    if(this -> lhs -> pretty_print_at() == prec_add || this -> lhs -> pretty_print_at() == prec_let) {
        out << "(";
        this -> lhs -> pretty_print(out);
        out << ")";
    }
    else {
        this -> lhs -> pretty_print(out);
    }

    out << " * ";

    if(this -> rhs -> pretty_print_at() == prec_add) {
        out << "(";
        this -> rhs -> pretty_print(out);
        out << ")";
    }
    else {
        this -> rhs -> pretty_print(out);
    }
}

std::string Mult::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t Mult::pretty_print_at(){
    return prec_mult; 
}

/******************
TESTS
*******************/
TEST_CASE("mult") {

    /******************
    interp()
    *******************/
    Num* num1 = new Num(5);
    Num* num2 = new Num(7);
    Add* add1 = new Add(num1, num2);
    Mult* mult = new Mult(num1, num2);
    CHECK(mult->interp() == 35);

    /******************
    has_variable()
    *******************/
    CHECK((new Mult(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Mult(new Num(7), new Num(7)))->has_variable() == false);

    /******************
    subst()
    *******************/
    // CHECK( (new Add(new Var("x"), new Num(7)))
    //    ->subst("x", new Var("y"))
    //    ->equals(new Add(new Var("y"), new Num(7))) );

}