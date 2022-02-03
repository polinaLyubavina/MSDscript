#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      ADD
*******************/

Add::Add(Expr* lhs, Expr*rhs) {
    this->lhs = lhs;
    this->rhs = rhs; 
}

bool Add::equals(Expr* e){
    Add* e_use = dynamic_cast<Add*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
}

int Add::interp() {
    return (this->lhs)->interp() + (this->rhs)->interp();
}

bool Add::has_variable() {
    return (this->lhs)->has_variable() || (this->rhs)->has_variable(); 
}

Expr* Add::subst(std::string var, Expr* e) {
    return new Add((this->lhs)->subst(var, e), (this->rhs)->subst(var, e)); 
}

void Add::print(std::ostream& out) {
    out << "(";
    lhs -> print(out);
    out << "+";
    rhs -> print(out);
    out << ")";
}

void Add::pretty_print(std::ostream& out) {
    if(this -> lhs -> pretty_print_at() == prec_add) {
        out << "(";
        this -> lhs -> pretty_print(out);
        out << "(";
    } 
    else {
        this -> rhs -> pretty_print(out);
    }
    out << " + ";
    this -> rhs -> pretty_print(out);
}

std::string Add::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t Add::pretty_print_at(){
    return prec_add;
}

/******************
TESTS
*******************/
TEST_CASE("add") {
    
    /******************
    interp()
    *******************/
    Num* num1 = new Num(5);
    Num* num2 = new Num(7);
    Add* add1 = new Add(num1, num2);
    CHECK(add1->interp() == 12);

    /******************
    has_variable() 
    *******************/
    CHECK((new Add(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Add(new Num(7), new Num(7)))->has_variable() == false);

    /******************
    subst()
    *******************/
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->equals(new Add(new Var("y"), new Num(7))) );

    /******************
    print() and pretty_print()
    *******************/
    CHECK((new Add(new Num(5), new Add(new Num(2), new Num(1))))->to_string() == "(5+(2+1))");
    CHECK((new Add(new Num(5), new Add(new Num(2), new Num(1))))->to_string() != "(7+(2+1))");

}