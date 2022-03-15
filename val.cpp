#include <iostream>
#include <string.h>

#include "val.h"
#include "expr.h"

/******************
 *      NumVal
*******************/

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

PTR(Val) NumVal::add_to(PTR(Val) input) {
    PTR(NumVal) verifiedInput = CAST(NumVal)(input);
    if(input == nullptr) {
        throw std::runtime_error("Not a valid input.");
    }
    else {
        return NEW(NumVal)(this -> val + verifiedInput -> val);
    }
}

 PTR(Expr) NumVal::to_expr() {
     return NEW(NumExpr)(this -> val);
 }

PTR(Val) NumVal::call(PTR(Val) actual_argument){
    throw std::runtime_error("Cannot call on Vals");
}

PTR(Val) NumVal::mult_to(PTR(Val) input) {
    PTR(NumVal) verifiedInput = CAST(NumVal)(input);
    if(input == nullptr) {
        throw std::runtime_error("Not a valid input.");
    }
    else {
        return NEW (NumVal)(this -> val * verifiedInput -> val);
    }
}

//int NumVal::interp() {
//}


/******************
 *      BoolVal
*******************/

BoolVal::BoolVal(bool input) {
    this -> input = input;
}

bool BoolVal::equals(PTR(Val) input) {
    PTR(BoolVal) myinput = CAST(BoolVal)(input);
    if(myinput == nullptr) {
        return false;
    }
    else {
        return (this -> input == myinput -> input);
    }
}

PTR(Val) BoolVal::add_to(PTR(Val) input) {
    throw std::runtime_error("Cannot add booleans");
}

PTR(Expr) BoolVal::to_expr() {
    return NEW(BoolExpr)(this -> input);
}

PTR(Val) BoolVal::call(PTR(Val) actual_argument) {
    throw std::runtime_error("Cannot call on Vals");
}

PTR(Val) BoolVal::mult_to(PTR(Val) input) {
    throw std::runtime_error("Cannot add booleans");
}

//Val* BoolVal::interp() {
//}
//std::string BoolVal::to_string() {
//}


/******************
 *      FunVal
*******************/

FunVal::FunVal(std::string formal_arg, Expr* body) {
    this -> formal_arg = formal_arg;
    this -> body = body;
}

bool FunVal::equals(PTR(Val) input) {
    PTR(FunVal) myinput = dynamic_cast<FunVal*>(input);
    if(myinput == nullptr) {
        return false;
    }
    else {
        return (this -> formal_arg == myinput -> formal_arg)
        && (this -> body == myinput -> body);
    }
}

PTR(Val) FunVal::add_to(PTR(Val) input) {
    throw std::runtime_error("Cannot add FunVals");
}

PTR(Expr) FunVal::to_expr() {
    return NEW(FunExpr)(this -> formal_arg, this -> body);
}

PTR(Val) FunVal::mult_to(PTR(Val) input) {
    throw std::runtime_error("Cannot add FunVals");
}

//Val* FunVal::call(Val* actual_argument) {
//    return this -> body -> subst(this -> formal_arg, actual_argument) -> interp();
//}

//std::string FunVal::to_string() {
//}
//Val* FunVal::interp() {
//}
