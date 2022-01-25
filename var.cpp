#include "expr.h"
#include "catch.h"
#include <stdexcept>

/******************
 *      VAR
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

void Var::print(std::ostream& out) {
    std::cout << this;
};

void Var::pretty_print(std::ostream& out) {
    std::cout << this; 
};