#include <iostream>
#include <string.h>
#include "expr.h"
#include "val.h"

NumVal::NumVal(int input) {
    this -> val = input;
}

//compares the values at the pointer
bool NumVal::equals(Val* input) {
    NumVal* verifiedInput = dynamic_cast<NumVal*>(input);
    if(verifiedInput == nullptr) {
        return false;
    }
    else {
        return this -> val == verifiedInput -> val;
    }
}

std::string NumVal::to_string() {
    return std::to_string(this -> val); 
}

Val* NumVal::add_to(Val* input) {
    NumVal* verifiedInput = dynamic_cast<NumVal*>(input);
    if(input == nullptr) {
        throw std::runtime_error("Not a valid input.");
    }
    else {
        return new NumVal(this -> val + verifiedInput -> val); 
    }
}

// Expr* NumVal::to_expr() {
//     return new Expr(this -> val);
// }