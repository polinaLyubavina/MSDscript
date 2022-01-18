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
        return ((this->val == e_use->val));
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
        return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
    }
};

/*
Mult
*/
Mult::Mult(Expr* lhs, Expr* rhs) {
    this-> lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr* e){
    Mult* e_use = dynamic_cast<Mult*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
    }
};

/*
Var
*/
Var::Var(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
};

bool Var::equals(Expr* e){
    Var* e_use = dynamic_cast<Var*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
    }
};

/*
TESTS
*/
TEST_CASE("equals") {
    CHECK((new Num(5))->equals(new Num(7)) == false);
    CHECK((new Add(new Num(5)),(new Num(7)))->equals(new Add(new Num(5)),(new Num(7))) == true);
    CHECK((new Mult(new Num(5)),(new Num(7)))->equals(new Mult(new Num(5)),(new Num(7))) == true);
    CHECK((new Add(new Var("5")),(new Num("7")))->equals(new Var(new Num("5")),(new Num("7"))) == true);
}; 
