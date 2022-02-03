#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      VAR
*******************/

Var::Var(std::string val) {
    this->val = val; 
}

bool Var::equals(Expr* e){
    Var* e_use = dynamic_cast<Var*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
}

int Var::interp() {
    throw std::runtime_error("A Variable has no value"); 
}

bool Var::has_variable() {
    return true; 
}

Expr* Var::subst(std::string var, Expr* e) {
    if(this->val == var) {
        /*
        if they match return e - e that you want to replace val/var with
        */
        return e;
    }
    else {
        return this;
    }
}

void Var::print(std::ostream& out) {
    std::cout << this -> val;
}

void Var::pretty_print(std::ostream& out) {
    std::cout << this -> val; 
}

std::string Var::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t Var::pretty_print_at(){
    return prec_none; 
}

/******************
TESTS
*******************/
TEST_CASE("var") {
    
    /******************
    Var Tests
    *******************/
    CHECK((new Var("5"))->equals(new Var("7")) == false);
    CHECK((new Add(new Var("cookie"), new Var("batter")))->equals(new Add(new Var("cookie"), new Var("batter"))) == true);
    CHECK((new Mult(new Var("5"), new Var("7")))->equals(new Mult(new Var("5"), new Var("7"))) == true);

    /******************
    interp()
    *******************/
    CHECK_THROWS_WITH( (new Var("x"))->interp(), "A Variable has no value" );

    /******************
    has_variable()
    *******************/
    CHECK((new Var("5"))->has_variable() == true);
    CHECK((new Add(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Mult(new Num(7), new Var("7")))->has_variable() == true);

    /******************
    subst()
    *******************/
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->equals(new Add(new Var("y"), new Num(7))) );

}