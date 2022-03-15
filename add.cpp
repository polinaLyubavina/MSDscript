#include "expr.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      ADD
*******************/

AddExpr::AddExpr(Expr* lhs, Expr*rhs) {
    this->lhs = lhs;
    this->rhs = rhs; 
}

bool AddExpr::equals(Expr* e){
    AddExpr* e_use = dynamic_cast<AddExpr*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
}

Val* AddExpr::interp() {
    return (this->lhs)->interp() + (this->rhs)->interp();
}

bool AddExpr::has_variable() {
    return (this->lhs)->has_variable() || (this->rhs)->has_variable();
}

Expr* AddExpr::subst(std::string var, Expr* e) {
    return new AddExpr((this->lhs)->subst(var, e), (this->rhs)->subst(var, e)); 
}

void AddExpr::print(std::ostream& output) {
    output << "(";
    lhs -> print(output);
    output << "+";
    rhs -> print(output);
    output << ")";
}

void AddExpr::pretty_print(std::ostream& output) {
    if(this -> lhs -> pretty_print_at() == prec_let) {
        output << "(";
        this -> lhs -> pretty_print(output);
        output << ")";
    }
    else {
        this -> lhs -> pretty_print(output);
    }

    output << " + ";
    this -> rhs -> pretty_print(output);
}

std::string AddExpr::to_string() {
    std::stringstream output;
    this -> print(output);
    return output.str();
}

precedence_t AddExpr::pretty_print_at(){
    return prec_add;
}

/******************
TESTS
*******************/
TEST_CASE("add") {
    
    /******************
    interp()
    *******************/
    NumExpr* num1 = new NumExpr(5);
    NumExpr* num2 = new NumExpr(7);
    AddExpr* add1 = new AddExpr(num1, num2);
    CHECK(add1->interp() == 12);

    /******************
    has_variable() 
    *******************/
//    CHECK((new AddExpr(new NumExpr(7), new VarExpr("7")))->has_variable() == true);
//    CHECK((new AddExpr(new NumExpr(7), new NumExpr(7)))->has_variable() == false);

    /******************
    subst()
    *******************/
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
       ->subst("x", new VarExpr("y"))
       ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );

    /******************
    print() and pretty_print()
    *******************/
    CHECK((new AddExpr(new NumExpr(5), new AddExpr(new NumExpr(2), new NumExpr(1))))->to_string() == "(5+(2+1))");
    CHECK((new AddExpr(new NumExpr(5), new AddExpr(new NumExpr(2), new NumExpr(1))))->to_string() != "(7+(2+1))");

}
