#include "expr.h"
#include "catch.h"
#include <stdexcept>

/******************
 *      NUM
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

void Num::print(std::ostream& out) {
    out << this -> val; 
};

void Num::pretty_print(std::ostream& out) {
    out << this -> val; 
};