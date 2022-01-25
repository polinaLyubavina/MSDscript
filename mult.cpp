#include "expr.h"
#include "catch.h"
#include <stdexcept>

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
};

void Mult::print(std::ostream& out) {

};

void Mult::pretty_print(std::ostream& out) {

};