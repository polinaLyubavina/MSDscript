#include <iostream>
#include <string.h>

#include "val.h"
#include "expr.h"
#include "catch.h"

/******************
 *      NumVal
*******************/

NumVal::NumVal(int input) {
    
    this -> val = input;
    
}

//compares the values at the pointer
bool NumVal::equals(PTR(Val) input) {
    
    PTR(NumVal) verifiedInput = CAST(NumVal)(input);
    
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
    
    if(verifiedInput == nullptr) {
        throw std::runtime_error("Invalid input");
    }
    
    else {
        return NEW(NumVal)(this -> val + verifiedInput -> val);
    }
}

 PTR(Expr) NumVal::to_expr() {
     
     return NEW(NumExpr)(this -> val);
     
 }

PTR(Val) NumVal::call(PTR(Val) actual_argument){
    
//    throw std::runtime_error("Cannot call on Vals");
    throw std::runtime_error("Invalid input");

    
}

PTR(Val) NumVal::mult_to(PTR(Val) input) {
    
    PTR(NumVal) verifiedInput = CAST(NumVal)(input);
    
    if(verifiedInput == nullptr) {
        throw std::runtime_error("Invalid input");
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
    
    PTR(BoolVal) verifiedInput = CAST(BoolVal)(input);
    
    if(verifiedInput == nullptr) {
        return false;
    }
    
    else {
        return (this -> input == verifiedInput -> input);
    }
}

PTR(Val) BoolVal::add_to(PTR(Val) input) {
    
//    throw std::runtime_error("Cannot add booleans");
    throw std::runtime_error("Invalid input");
    
}

PTR(Expr) BoolVal::to_expr() {
    
    return NEW(BoolExpr)(this -> input);
    
}

PTR(Val) BoolVal::call(PTR(Val) actual_argument) {
    
//    throw std::runtime_error("Cannot call on Vals");
    throw std::runtime_error("Invalid input");
    
}

PTR(Val) BoolVal::mult_to(PTR(Val) input) {
    
//    throw std::runtime_error("Cannot multiply booleans");
    throw std::runtime_error("Invalid input");
    
}

std::string BoolVal::to_string() {
    
    if(input) {
        return "_true";
    }
    else {
        return "_false";
    }
    
//    return std::to_string(this -> input);
    
}

//Val* BoolVal::interp() {
//}


/******************
 *      FunVal
*******************/

FunVal::FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env) {
    
    this -> formal_arg = formal_arg;
    this -> body = body;
    this -> env = env;
    
}

bool FunVal::equals(PTR(Val) input) {
    
    PTR(FunVal) verifiedInput = CAST(FunVal)(input);
    
    if(verifiedInput == nullptr) {
        
        return false;
    }
    
    else {
        
        return (this -> formal_arg == verifiedInput -> formal_arg)
                    &&
                        ((this -> body) -> equals(verifiedInput -> body) );
    }
}

PTR(Val) FunVal::add_to(PTR(Val) input) {
    
//    throw std::runtime_error("Cannot add FunVals");
    throw std::runtime_error("Invalid input");

}

PTR(Expr) FunVal::to_expr() {
    
    return NEW(FunExpr)(this -> formal_arg, this -> body);
    
}

PTR(Val) FunVal::mult_to(PTR(Val) input) {
    
//    throw std::runtime_error("Cannot add FunVals");
    throw std::runtime_error("Invalid input");

}

PTR(Val) FunVal::call(PTR(Val) actual_argument) {
    
    return body -> interp(NEW(ExtendedEnv)(this -> formal_arg, actual_argument, this -> env));
    
}

std::string FunVal::to_string() {
    
    return "_fun (" + this -> formal_arg + ") " + this -> body -> to_string();
    
}

//Val* FunVal::interp() {
//
//}

/******************
TESTS
*******************/
TEST_CASE("Val") {
    
    SECTION("NumVal") {
        
        SECTION("NumVal equals()") {
            CHECK( ( NEW(NumVal)(15) )
                  -> equals( NEW(NumVal)(15) ) );
            
            CHECK( ! ( NEW(NumVal)(20) )
                  -> equals( NEW(NumVal)(15) ) );
            
            CHECK( ! ( NEW(NumVal)(15) )
                  -> equals( NEW(BoolVal)(true) ) );
        }
        
        SECTION("NumVal to_string()") {
            CHECK( ( NEW(NumVal)(15) )
                  -> to_string() == "15" );
        }
        
        SECTION("NumVal to_expr()") {
            CHECK( ( NEW(NumVal)(15) )
                  -> to_expr()
                  -> equals( NEW(NumExpr)(15) ) );
            CHECK( ( NEW(NumVal)(25) )
                  -> to_expr()
                  -> equals( NEW(NumExpr)(25) ) );
        }
        
        SECTION("NumVal mult_to()") {
            CHECK ( ( NEW(NumVal)(5) )
                -> mult_to( NEW(NumVal)(5) )
                -> equals( NEW(NumVal)(25) ) );
            
            CHECK_THROWS_WITH ( ( NEW(NumVal)(5) )
                               -> mult_to( NEW(BoolVal)(true) ), "Invalid input" );
        }
        
        SECTION("NumVal add_to()") {
            CHECK ( ( NEW(NumVal)(5) )
                   -> add_to( NEW(NumVal)(10) )
                   -> equals( NEW(NumVal)(15) ) );
            
            CHECK_THROWS_WITH ( ( NEW(NumVal)(5))
                               -> add_to( NEW(BoolVal)(true)), "Invalid input" );
        }
    }
    
    SECTION("BoolVal") {
        
        SECTION("BoolVal equals()") {
            
            CHECK( ( NEW(BoolVal)(true) )
                  -> equals( NEW(BoolVal)(true) ) );
        }
        
        SECTION("BoolVal to_string()") {
    
            CHECK( ( NEW(BoolVal)(true))
                  -> to_string() == "_true" );
            CHECK( ( NEW(BoolVal)(false))
                  -> to_string() == "_false" );
        }
        
        SECTION("BoolVal to_expr()") {
            
            CHECK( ( NEW(BoolVal)(false) )
                  -> to_expr()
                  -> equals( NEW(BoolExpr)(false) ) );
            
            CHECK( ( NEW(BoolVal)(true) )
                  -> to_expr()
                  -> equals( NEW(BoolExpr)(true) ) );
        }
        
        SECTION("BoolVal mult_to()") {
            
            CHECK_THROWS_WITH ( ( NEW(BoolVal)(true) )
                               -> mult_to( NEW(BoolVal)(true) ), "Invalid input" );
            CHECK_THROWS_WITH ( ( NEW(BoolVal)(false) )
                               -> mult_to( NEW(BoolVal)(false) ), "Invalid input" );
        }
        
        SECTION("BoolVal add_to()") {
            
            CHECK_THROWS_WITH ( ( NEW(BoolVal)(true) )
                               -> add_to( NEW(BoolVal)(true) ), "Invalid input" );
            CHECK_THROWS_WITH ( ( NEW(BoolVal)(false) )
                               -> add_to( NEW(BoolVal)(false) ), "Invalid input" );
        }
    }
    
    SECTION("FunVal") {
        
        SECTION("FunVal equals()") {
            
            CHECK( ( NEW(FunVal)("x", NEW(NumExpr)(15), Env::empty) )
                  -> equals( NEW(FunVal)("x", NEW(NumExpr)(15), Env::empty) ) );
            
            CHECK( ! (NEW(FunVal)("x", NEW(NumExpr)(25), Env::empty ) )
                  -> equals(NEW(FunVal)("y", NEW(NumExpr)(25), Env::empty ) ) );
            
            CHECK( ! ( NEW(FunVal)("y", NEW(NumExpr)(15), Env::empty ) )
                  -> equals( NEW(FunVal)("y", NEW(NumExpr)(20), Env::empty ) ) );
        }
        
        SECTION("FunVal mult_to()") {
            
            CHECK_THROWS_WITH( ( NEW(FunVal)("y", NEW(NumExpr)(15), Env::empty ) )
                              -> mult_to( NEW(NumVal)(15) ), "Invalid input");
        }
        
        SECTION("FunVal add_to()") {
            
            CHECK_THROWS_WITH( ( NEW(FunVal)("z", NEW(NumExpr)(20), Env::empty ) )
                              -> add_to( NEW(NumVal)(20) ), "Invalid input");
        }
        
        SECTION("FunVal to_string()") {
            
            CHECK( ( NEW(FunVal)("y", NEW(NumExpr)(15), Env::empty ) )
                  -> to_string() == "_fun (y) 15" );
        }
        
        SECTION("FunVal to_expr()") {
            
            CHECK( ( NEW(FunVal)("z", NEW(NumExpr)(5), Env::empty ) )
                  ->to_expr()
                  ->equals( NEW(FunExpr)("z", NEW(NumExpr)(5) ) ) );
        }
    }
}
