#include "expr.h"
#include "catch.h"

/*
Num
*/
Num::Num(int val){
    this->val = val; 
};

bool Num::equals(Expr* e){
    // if (e is num) {
    //     return this->val == e->val;
    // } else {
    //     e->equals(this);
    // }

    return false;
}; 

/*
Add
*/
Add::Add(Expr* lhs, Expr*rhs) {
    this->lhs = lhs;
    this->rhs = rhs; 
};

bool Add::equals(Expr* e){
    return false;
};

/*
Mult
*/
Mult::Mult(Expr* lhs, Expr* rhs) {
    this-> lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(Expr* e){
    return false;
};

/*
Var
*/
Var::Var(Expr* lhs, Expr* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
};

bool Var::equals(Expr* e){
    return false; 
};

/*
TESTS
*/
TEST_CASE("equals") {
    CHECK((new Num(5))->equals(new Num(7)) == false);
    // CHECK(new Add(new Num(484)).equals(new Num(123)) == false);
    // CHECK(new Mult(new Num(20)).equals(new Num(60)) == false);
    // CHECK(new Var(new Num("200")).equals(new Add(new Num("300"))) == false);
}; 
