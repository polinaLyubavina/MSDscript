#include "expr.h"
#include "val.h"
#include "catch.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

/******************
 *      NUM
*******************/

NumExpr::NumExpr(int val){
    this->val = val; 
};

bool NumExpr::equals(Expr* e){
    NumExpr* e_use = dynamic_cast<NumExpr*>(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
}; 

Val* NumExpr::interp() {
    return new NumVal (this->val);
};

bool NumExpr::has_variable() {
    return false;
};

Expr* NumExpr::subst(std::string var, Expr* e) {
    /*
    there is no variable to substitute so you return the number
    */
    return this;
};

void NumExpr::print(std::ostream& out) {
    out << this -> val; 
};

void NumExpr::pretty_print(std::ostream& out) {
    out << this -> val; 
};

std::string NumExpr::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t NumExpr::pretty_print_at(){
    return prec_none; 
}

/******************
TESTS
*******************/
TEST_CASE("num") {
    
    /******************
    Num & Add
    *******************/
    CHECK((new NumExpr(5))->equals(new NumExpr(7)) == false);
    CHECK((new AddExpr(new NumExpr(5), new NumExpr(7)))->equals(new AddExpr(new NumExpr(5), new NumExpr(7))) == true);
    // CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(7), new Num(5))) == true);
    CHECK((new MultExpr(new NumExpr(5), new NumExpr(7)))->equals(new MultExpr(new NumExpr(5), new NumExpr(7))) == true);

    /******************
    interp()
    *******************/
    NumExpr* num1 = new NumExpr(5);
    NumExpr* num2 = new NumExpr(7);
    CHECK((new NumExpr(5))->interp() == 5);

    /******************
    has_variable()
    *******************/
//    CHECK((new NumExpr(7))->has_variable() == false);

    /******************
    subst()
    *******************/
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
       ->subst("x", new VarExpr("y"))
       ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );

}
