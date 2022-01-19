#include "expr.h"
#include "catch.h"

/*
Num
*/
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

/*
Add
*/
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

/*
Mult
*/
Mult::Mult(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

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

/*
Var
*/
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

/*
TESTS
*/
TEST_CASE("equals") {
    CHECK((new Num(5))->equals(new Num(7)) == false);
    CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(5), new Num(7))) == true);
    // CHECK((new Add(new Num(7), new Num(5)))->equals(new Add(new Num(5), new Num(7))) == true);
    CHECK((new Mult(new Num(5), new Num(7)))->equals(new Mult(new Num(5), new Num(7))) == true);

    CHECK((new Var("5"))->equals(new Var("7")) == false);
    // CHECK((new Add(new Var("cookie"), new Var("batter")))->equals(new Add(new Var("cookie"), new Var("batter"))) == true);
    // CHECK((new Mult(new Var("5"), new Var("7")))->equals(new Mult(new Var("5"), new Var("7"))) == true);
}; 
