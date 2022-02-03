#include "expr.h"
#include "catch.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

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

std::string Num::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

precedence_t Num::pretty_print_at(){
    // return this->val; 
}

/******************
TESTS
*******************/
TEST_CASE("num") {
    
    /******************
    Num & Add
    *******************/
    CHECK((new Num(5))->equals(new Num(7)) == false);
    CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(5), new Num(7))) == true);
    // CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(7), new Num(5))) == true);
    CHECK((new Mult(new Num(5), new Num(7)))->equals(new Mult(new Num(5), new Num(7))) == true);

    /******************
    interp()
    *******************/
    Num* num1 = new Num(5);
    Num* num2 = new Num(7);
    CHECK((new Num(5))->interp() == 5);

    /******************
    has_variable()
    *******************/
    CHECK((new Num(7))->has_variable() == false);

    /******************
    subst()
    *******************/
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->equals(new Add(new Var("y"), new Num(7))) );

}