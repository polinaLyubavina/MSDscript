#include "expr.h"
#include "catch.h"
#include <stdexcept>

/******************
Num
*******************/
Num::Num(int val){
    this->val = val; 
};

bool Num::equals(Expr* e){
    Num* e_use = dynamic_cast<Num*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
}; 

int Num::interp() {
    return this->val;
};

bool Num::has_variable() {
    return false;
};

Expr* Num::subst(std::string var, Expr* e) {
    /*
    there is no variable to substitute so you return the number
    */
    return this;
};

std::ostream& Num::print(std::ostream&) {

};

std::ostream& Num::pretty_print(std::ostream&) {

};

/******************
Add
*******************/
Add::Add(Expr* lhs, Expr*rhs) {
    this->lhs = lhs;
    this->rhs = rhs; 
};

bool Add::equals(Expr* e){
    Add* e_use = dynamic_cast<Add*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
};

int Add::interp() {
    return (this->lhs)->interp() + (this->rhs)->interp();
};

bool Add::has_variable() {
    return (this->lhs)->has_variable() || (this->rhs)->has_variable(); 
};

Expr* Add::subst(std::string var, Expr* e) {
    return new Add((this->lhs)->subst(var, e), (this->rhs)->subst(var, e)); 
};

std::ostream& Add::print(std::ostream&) {

};

std::ostream& Add::pretty_print(std::ostream&) {

};

/******************
Mult
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
};

std::ostream& Mult::print(std::ostream&) {

};

std::ostream& Mult::pretty_print(std::ostream&) {

};

/******************
Var
*******************/
Var::Var(std::string val) {
    this->val = val; 
};

bool Var::equals(Expr* e){
    Var* e_use = dynamic_cast<Var*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
};

int Var::interp() {
    throw std::runtime_error("A Variable has no value"); 
};

bool Var::has_variable() {
    return true; 
};

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
};

std::ostream& Var::print(std::ostream&) {

};

std::ostream& Var::pretty_print(std::ostream&) {

};

/******************
TESTS
*******************/
TEST_CASE("equals") {
    /******************
    Num Tests
    *******************/
    CHECK((new Num(5))->equals(new Num(7)) == false);
    CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(5), new Num(7))) == true);
    // CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(7), new Num(5))) == true);
    CHECK((new Mult(new Num(5), new Num(7)))->equals(new Mult(new Num(5), new Num(7))) == true);

    /******************
    Num Tests where lhs and rhs don't == on both sides
    *******************/
    // CHECK((new Add(new Num(7), new Num(5)))->equals(new Add(new Num(5), new Num(7))) == true);

    /******************
    Var Tests
    *******************/
    CHECK((new Var("5"))->equals(new Var("7")) == false);
    CHECK((new Add(new Var("cookie"), new Var("batter")))->equals(new Add(new Var("cookie"), new Var("batter"))) == true);
    CHECK((new Mult(new Var("5"), new Var("7")))->equals(new Mult(new Var("5"), new Var("7"))) == true);

    /******************
    Interp Tests
    *******************/
    Num* num1 = new Num(5);
    Num* num2 = new Num(7);
    Add* add1 = new Add(num1, num2);
    CHECK(add1->interp() == 12);

    CHECK((new Num(5))->interp() == 5);

    Mult* mult = new Mult(num1, num2);
    CHECK(mult->interp() == 35);

    CHECK_THROWS_WITH( (new Var("x"))->interp(), "A Variable has no value" );

    /******************
    has_variable Tests
    *******************/
    CHECK((new Var("5"))->has_variable() == true);
    CHECK((new Num(7))->has_variable() == false);
    CHECK((new Add(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Mult(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Add(new Num(7), new Num(7)))->has_variable() == false);
    CHECK((new Mult(new Num(7), new Num(7)))->has_variable() == false);

    /******************
    Subst Tests
    *******************/
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->equals(new Add(new Var("y"), new Num(7))) );
}; 
