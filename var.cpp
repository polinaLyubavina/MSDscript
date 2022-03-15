#include "expr.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      VAR
*******************/

VarExpr::VarExpr(std::string val) {
    this->val = val; 
}

bool VarExpr::equals(Expr* e){
    VarExpr* e_use = dynamic_cast<VarExpr*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
}

Val* VarExpr::interp() {
    throw std::runtime_error("A Variable has no value"); 
}

bool VarExpr::has_variable() {
    return true;
}

Expr* VarExpr::subst(std::string var, Expr* e) {
    if(this->val == var) {
        /*
        if they match return e - e that you want to replace val/var with
        */
        return e;
    }
    else {
        return this;
    }
}

void VarExpr::print(std::ostream& out) {
    std::cout << this -> val;
}

void VarExpr::pretty_print(std::ostream& out) {
    std::cout << this -> val; 
}

std::string VarExpr::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t VarExpr::pretty_print_at(){
    return prec_none; 
}

/******************
TESTS
*******************/
TEST_CASE("var") {
    
    /******************
    Var Tests
    *******************/
    CHECK((new VarExpr("5"))->equals(new VarExpr("7")) == false);
    CHECK((new AddExpr(new VarExpr("cookie"), new VarExpr("batter")))->equals(new AddExpr(new VarExpr("cookie"), new VarExpr("batter"))) == true);
    CHECK((new MultExpr(new VarExpr("5"), new VarExpr("7")))->equals(new MultExpr(new VarExpr("5"), new VarExpr("7"))) == true);

    /******************
    interp()
    *******************/
    CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "A Variable has no value" );

    /******************
    has_variable()
    *******************/
//    CHECK((new VarExpr("5"))->has_variable() == true);
//    CHECK((new AddExpr(new NumExpr(7), new VarExpr("7")))->has_variable() == true);
//    CHECK((new MultExpr(new NumExpr(7), new VarExpr("7")))->has_variable() == true);

    /******************
    subst()
    *******************/
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
       ->subst("x", new VarExpr("y"))
       ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );

}
