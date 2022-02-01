#include "expr.h"
#include "catch.h"
#include <sstream>
#include <stdexcept>

/******************
 *      ADD
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

void Add::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "+";
    rhs -> print(out);
    out << ")";
};

void Add::pretty_print(std::ostream& out) {
    // out << "(";
    // lhs -> print(out);
    // out << " + ";
    // rhs -> print(out);
    // out << ")";
    std::out pretty_print_at(std::ostream& out); 
};

std::string Add::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t Add::pretty_print_at(std::ostream& out){
    return prec_add;
}