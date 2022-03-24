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
    this -> val = val;
}

bool VarExpr::equals(PTR(Expr) e){
    PTR(VarExpr) e_use = CAST(VarExpr)(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this -> val == e_use -> val;
    }
}

PTR(Val) VarExpr::interp(PTR(Env) env) {
    throw std::runtime_error("A Variable has no value");
}

PTR(Expr) VarExpr::subst(std::string var, PTR(Expr) e) {
    if(this -> val == var) {
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

//bool VarExpr::has_variable() {
//    return true;
//}


/******************
 *      NUM
*******************/

NumExpr::NumExpr(int val){
    this->val = val;
};

bool NumExpr::equals(PTR(Expr) e){
    PTR(NumExpr) e_use = CAST(NumExpr)(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        return this->val == e_use->val;
    }
};

PTR(Val) NumExpr::interp(PTR(Env) env) {
    return new NumVal (this->val);
};

PTR(Expr) NumExpr::subst(std::string var, PTR(Expr) e) {
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

//bool NumExpr::has_variable() {
//    return false;
//};


/******************
 *      ADD
*******************/

AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool AddExpr::equals(PTR(Expr) e){
    PTR(AddExpr) e_use = CAST(AddExpr)(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
}

PTR(Val) AddExpr::interp(PTR(Env) env) {
    return (this->lhs) -> interp(env) -> add_to( (this->rhs) -> interp(env) );
}

PTR(Expr) AddExpr::subst(std::string var, PTR(Expr) e) {
    return new AddExpr((this->lhs)->subst(var, e), (this->rhs)->subst(var, e));
}

void AddExpr::print(std::ostream& output) {
    output << "(";
    lhs -> print(output);
    output << "+";
    rhs -> print(output);
    output << ")";
}

std::string AddExpr::to_string() {
    std::stringstream output;
    this -> print(output);
    return output.str();
}

precedence_t AddExpr::pretty_print_at(){
    return prec_add;
}

//void AddExpr::pretty_print(std::ostream& output) {
//    if(this -> lhs -> pretty_print_at() == prec_let) {
//        output << "(";
//        this -> lhs -> pretty_print(output);
//        output << ")";
//    }
//    else {
//        this -> lhs -> pretty_print(output);
//    }
//
//    output << " + ";
//    this -> rhs -> pretty_print(output);
//}

//bool AddExpr::has_variable() {
//    return (this->lhs)->has_variable() || (this->rhs)->has_variable();
//}


/******************
 *      MULT
*******************/

MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
};

bool MultExpr::equals(PTR(Expr) e){
    PTR(MultExpr) e_use = CAST(MultExpr)(e);
    if(e_use == nullptr) {
        return false;
    }
    else {
        // return ((this->lhs == e_use->lhs) && (this->rhs == e_use->rhs));
        return (this->lhs)->equals(e_use->lhs) && (this->rhs)->equals(e_use->rhs);
    }
};

PTR(Val) MultExpr::interp(PTR(Env) env) {
    return (this->lhs) -> interp(env) -> mult_to( (this->rhs) -> interp(env) );
};

PTR(Expr) MultExpr::subst(std::string var, PTR(Expr) e) {
    return NEW(MultExpr)( (this->lhs)->subst(var, e), (this->rhs)->subst(var, e) );
}

void MultExpr::print(std::ostream& output) {
    output << "(";
    lhs -> print(output);
    output << "*";
    rhs -> print(output);
    output << ")";
}

std::string MultExpr::to_string() {
    std::stringstream output;
    this -> print(output);
    return output.str();
}

//void MultExpr::pretty_print(std::ostream& output) {
//    if(this -> lhs -> pretty_print_at() == prec_add || this -> lhs -> pretty_print_at() == prec_let) {
//        output << "(";
//        this -> lhs -> pretty_print(output);
//        output << ")";
//    }
//    else {
//        this -> lhs -> pretty_print(output);
//    }
//
//    output << " * ";
//
//    if(this -> rhs -> pretty_print_at() == prec_add) {
//        output << "(";
//        this -> rhs -> pretty_print(output);
//        output << ")";
//    }
//    else {
//        this -> rhs -> pretty_print(output);
//    }
//}

//bool MultExpr::has_variable() {
//    return (this->lhs)->has_variable() || (this->rhs)->has_variable();
//};

//precedence_t MultExpr::pretty_print_at(){
//    return prec_mult;
//}


/******************
 *     LetExpr
*******************/

LetExpr::LetExpr(std::string lhs, PTR(Expr) rhs, PTR(Expr) body) {
    this->lhs = lhs;
    this->rhs = rhs;
    this->body = body;
}

bool LetExpr::equals(Expr* another_expression){
//    return  this->interp(env) == another_expression->interp(env);
    PTR(LetExpr) casted_another_expression = CAST(LetExpr)(another_expression);
    if(casted_another_expression == nullptr) {
        return false;
    }
    else {
        return (lhs == casted_another_expression -> lhs
                && rhs -> equals(casted_another_expression -> rhs)
                && body -> equals(casted_another_expression -> body));
    }
}

PTR(Val) LetExpr::interp(PTR(Env) env) {
    return this -> body -> subst(lhs, this -> rhs -> interp(env) -> to_expr()) -> interp(env);
}

// returns true if rhs or body has a variable
//bool LetExpr::has_variable() {
//    return this -> rhs -> has_variable() || this -> body -> has_variable();
//}

PTR(Expr) LetExpr::subst(std::string var, PTR(Expr) e) {
    if(lhs.compare(var)) {
        return this;        //if it matches don't change it
    }
    else {
        PTR(LetExpr) output = NEW(LetExpr)(lhs, rhs -> subst(var, e), body -> subst(var, e));
        return output;
    }
}

void LetExpr::print(std::ostream& out) {
    out << "(_let ";
    out << this -> lhs;
    out << "=";
    this -> rhs -> print(out);
    out << " _in ";
    out << "(";
    this -> body -> print(out);
    out << ")";
    out << ")";
}

std::string LetExpr::to_string() {
    std::stringstream out;
    this -> print(out);
    return out.str();
}

//void _let::pretty_print(std::ostream& out) {
//    out << "_let ";
//    int num_spaces = out.tellp();
//
//    out << this -> lhs;
//    out << " = ";
//    this -> rhs -> pretty_print(out);
//
//    out << "\n";
//    for(int i = 0; i < num_spaces; i++) {
//        out << " ";
//    }
//    out << "_in ";
//
//    this -> body -> pretty_print(out);
//}

//precedence_t _let::pretty_print_at(){
//    return prec_let;
//}


/******************
 *      BoolExpr
*******************/

//constructor
BoolExpr::BoolExpr(bool input) {
    this -> val = input;
}

bool BoolExpr::equals(PTR(Expr) compared_against) {
    PTR(BoolExpr) casted_val = CAST(BoolExpr)(compared_against);
    if(casted_val == NULL) {
        return false;
    }
    else {
        return (this -> val == casted_val -> val);
    }
}

PTR(Val) BoolExpr::interp(PTR(Env) env) {
    return NEW(BoolVal)(this -> val);
}

//printing true and false
void BoolExpr::print(std::ostream& output) {
    if(this -> val == true) {
        output << "_true";
    }
    else {
        output << "_false";
    }
}

PTR(Expr) BoolExpr::subst(std::string var, PTR(Expr) e) {
    return this;
};

std::string BoolExpr::to_string() {
    if(this -> val == true) {
        return "_true";
    }
    else {
        return "_false";
    }
};

//bool BoolExpr::has_variable() {
//    return false;
//}

//void BoolExpr::pretty_print(std::ostream& output) {
//
//}

//precedence_t BoolExpr::pretty_print_at() {
//
//}


/******************
 *      EqulExpr
*******************/

//constructor
EqulExpr::EqulExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this -> lhs = lhs;
    this -> rhs = rhs;
}

bool EqulExpr::equals(PTR(Expr) compared_against) {
    PTR(EqulExpr) casted_val = CAST(EqulExpr)(compared_against);
    if(casted_val == NULL) {
        return false;
    }
    else {
        return (this -> lhs) -> equals(casted_val -> lhs) && (this -> rhs) -> equals(casted_val -> rhs);
    }
}

PTR(Val) EqulExpr::interp(PTR(Env) env) {
    PTR(Val) temp_lhs = lhs -> interp(env);
    PTR(Val) temp_rhs = rhs -> interp(env);
    return NEW(BoolVal)(temp_lhs -> equals(temp_rhs) );
}

void EqulExpr::print(std::ostream& output) {
    PTR(Expr) temp_lhs = this -> lhs;
    PTR(Expr) temp_rhs = this -> rhs;
    
    output << "(";
    temp_lhs -> print(output);
    output << "==";
    temp_rhs -> print(output);
    output << ")";
}

PTR(Expr) EqulExpr::subst(std::string var, PTR(Expr) e) {
    return NEW(EqulExpr)( (this->lhs)->subst(var, e), (this->rhs)->subst(var, e) );
};

std::string EqulExpr::to_string() {
    return (this -> lhs -> to_string() ) + "==" + (this -> rhs -> to_string() );
}

//void EqulExpr::pretty_print(std::ostream& output) {
//
//}
//precedence_t EqulExpr::pretty_print_at() {
//
//}



/******************
 *      IfExpr
*******************/

//constructor
IfExpr::IfExpr(PTR(Expr) input, PTR(Expr) then_input, PTR(Expr) else_input) {
    this -> test_input = input;
    this -> then_input = then_input;
    this -> else_input = else_input;
}

bool IfExpr::equals(PTR(Expr) compared_against) {
    PTR(IfExpr) casted_val = CAST(IfExpr)(compared_against);
    if(casted_val == NULL) {
        return false;
    }
    else {
        return (this -> test_input) -> equals(casted_val -> test_input)
                && (this -> then_input) -> equals(casted_val -> then_input)
                && (this -> else_input) -> equals(casted_val -> else_input);
    }
}

PTR(Val) IfExpr::interp(PTR(Env) env) {
    if(test_input -> interp(env) ) {
        return then_input -> interp(env);
    }
    else {
        return else_input -> interp(env);
    }
}

void IfExpr::print(std::ostream& output) {
    PTR(Expr) temp_input = this -> test_input;
    PTR(Expr) temp_thenInput = this -> then_input;
    PTR(Expr) temp_elseInput = this -> else_input;
    
    output << "_if(";
    temp_input -> print(output);
    output << "_then";
    temp_thenInput -> print(output);
    output << "_else";
    temp_elseInput -> print(output);
    output << ")";
}

PTR(Expr) IfExpr::subst(std::string var, PTR(Expr) e) {
    return NEW(IfExpr)( (this -> test_input) -> subst(var, e),
                       (this -> then_input) -> subst(var, e),
                       (this -> else_input) -> subst(var, e) );
};

std::string IfExpr::to_string() {
    return "(_if " + (test_input -> to_string() ) + " _then " + (then_input -> to_string() ) + " _else " + (else_input -> to_string() ) + ")";
}

//void IfExpr::pretty_print(std::ostream& output) {
//
//}

//precedence_t IfExpr::pretty_print_at() {
//
//}


/******************
 *      FunExpr
*******************/

FunExpr::FunExpr(std::string formal_arg, Expr* body) {
    this -> formal_arg = formal_arg;
    this -> body = body;
}

PTR(Val) FunExpr::interp(PTR(Env) env) {
    return new FunVal(formal_arg, body);
}

bool FunExpr::equals(Expr* compared_against) {
    FunExpr* casted_val = dynamic_cast<FunExpr*>(compared_against);
    if(casted_val == NULL) {
        return false;
    }
    else {
        return (this -> formal_arg == casted_val -> formal_arg)
        && (this -> body) -> equals(casted_val -> body);
    }
}

void FunExpr::print(std::ostream& output) {
    output << "(_fun (" << formal_arg << ") ";
    this -> body -> print(output);
    output << ")";
}

PTR(Expr) FunExpr::subst(std::string var, PTR(Expr) e) {
    if(this -> formal_arg == var) {
        return this;
    }
    else {
        return NEW(FunExpr)( (this -> formal_arg), (this -> body) -> subst(var, e) );
    }
};

std::string FunExpr::to_string() {
    return "(_fun (" + formal_arg + ") " + (body -> to_string() ) + ")";
}

//void FunExpr::pretty_print(std::ostream& output) {
//
//}
//precedence_t FunExpr::pretty_print_at() {
//
//}


/******************
 *      CallExpr
*******************/

CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg) {
    this -> to_be_called = to_be_called;
    this -> actual_arg = actual_arg; 
}

PTR(Val) CallExpr::interp(PTR(Env) env) {
    return to_be_called -> interp(env) -> call(actual_arg -> interp(env) );
}

bool CallExpr::equals(PTR(Expr) compared_against) {
    PTR(CallExpr) casted_val = CAST(CallExpr)(compared_against);
    if(casted_val == NULL) {
        return false;
    }
    else {
        return (this -> to_be_called == casted_val -> to_be_called)
        && (this -> actual_arg) -> equals(casted_val -> actual_arg);
    }
}

void CallExpr::print(std::ostream& output) {
    this -> to_be_called -> print(output);
    output << "(";
    this -> actual_arg -> print(output);
    output << ")";
}

PTR(Expr) CallExpr::subst(std::string var, PTR(Expr) e) {
    return NEW(CallExpr)( (this -> to_be_called) -> subst(var, e), (this -> actual_arg) -> subst(var, e) );
};

std::string CallExpr::to_string() {
    return "(" + (to_be_called->to_string() ) + " (" + (actual_arg->to_string() ) + "))";
}

//void CallExpr::pretty_print(std::ostream& output) {
//
//}
//precedence_t CallExpr::pretty_print_at() {
//
//}



/******************
    TESTS
*******************/

TEST_CASE("Equals") {
    
    SECTION("NumExpr") {
        PTR(NumExpr) num1 = NEW(NumExpr)(5);
        PTR(NumExpr) num2 = NEW(NumExpr)(7);
                
        CHECK( (NEW(NumExpr)(5) ) -> equals(NEW(NumExpr)(7) ) == false);
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(7) ) ) -> equals(NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(7) ) ) == true);
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(7 ) ) ) -> equals(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(7) ) ) == true);
        CHECK( (NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7 ) ) )
           -> subst("x", NEW(VarExpr)("y"))
           -> equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7) ) ) );
    }
    
    SECTION("AddExpr") {
        CHECK( (NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7) ) )
           -> subst("x", NEW(VarExpr)("y"))
           -> equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7) ) ) );
    }
    
    SECTION("MultExpr") {
        PTR(NumExpr) num1 = NEW(NumExpr)(5);
        PTR(NumExpr) num2 = NEW(NumExpr)(7);
        
//        CHECK((new MultExpr(new NumExpr(7), new VarExpr("7")))->has_variable() == true);
//        CHECK((new MultExpr(new NumExpr(7), new NumExpr(7)))->has_variable() == false);
//        CHECK( (new Add(new Var("x"), new Num(7)))
//        ->subst("x", new Var("y"))
//        ->equals(new Add(new Var("y"), new Num(7))) );
    }
    
    SECTION("VarExpr") {
        CHECK( (NEW(VarExpr)("5") ) -> equals(NEW(VarExpr)("7") ) == false);
        CHECK( (NEW(AddExpr)(NEW(VarExpr)("cookie"), NEW(VarExpr)("batter") ) ) -> equals(NEW(AddExpr)(NEW(VarExpr)("cookie"), NEW(VarExpr)("batter") ) ) == true);
        CHECK( (NEW(MultExpr)(NEW(VarExpr)("5"), NEW(VarExpr)("7") ) ) -> equals(NEW(MultExpr)(NEW(VarExpr)("5"), NEW(VarExpr)("7") ) ) == true);
        CHECK_THROWS_WITH( (NEW(VarExpr)("x") ) -> interp(NEW(EmptyEnv)), "A Variable has no value" );
        CHECK( (NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7) ) )
           -> subst("x", NEW(VarExpr)("y") )
           -> equals(NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(7) ) ) );
    }
    
    SECTION("LetExpr") {
        CHECK((NEW(LetExpr)(
                        "x",
                        NEW(NumExpr)(7),
                        NEW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(7))
                    ))
                    -> equals(NEW(NumExpr)(14)) == true);
    }
    
    SECTION("BoolExpr") {
        PTR(BoolExpr) test_true_bool = NEW(BoolExpr)(true);
        PTR(BoolExpr) test_true_bool_2 = NEW(BoolExpr)(true);
        PTR(BoolExpr) test_false_bool_ = NEW(BoolExpr)(false);
        PTR(BoolExpr) test_false_bool_2 = NEW(BoolExpr)(false);
        CHECK(test_true_bool -> equals(test_true_bool_2));
        CHECK(test_false_bool_ -> equals(test_false_bool_2));
    }
    
    SECTION("EqulExpr") {
//        CHECK( (NEW(EqulExpr) (NEW(NumExpr)(5), NEW(NumExpr)(6) ) ) -> equals(NEW(EqulExpr) (NEW(NumExpr(5), NEW(NumExpr)(6) ) ) == true);
//        CHECK( (NEW(EqulExpr) (NEW(NumExpr)(10), NEW(NumExpr)(5) ) ) -> equals(NEW(EqulExpr) (NEW(NumExpr(5), NEW(NumExpr)(5) ) ) == false);
    }
    
    SECTION("IfExpr") {
        PTR(IfExpr)test_1 = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(7), NEW(NumExpr)(3));
        PTR(IfExpr)test_2 = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(7), NEW(NumExpr)(3));
        PTR(IfExpr)test_3 = NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(7), NEW(NumExpr)(10));
        CHECK(test_1->equals(test_3) == false);
        CHECK(test_1->equals(test_2));
    }
    
    SECTION("FunExpr") {
        CHECK( (NEW(FunExpr)("new_fun_xpr", NEW(NumExpr)(3) ) ) -> equals(NEW(FunExpr)("new_fun_xpr", NEW(NumExpr)(3) ) ) == true);
    }
    
    SECTION("CallExpr") {
        CHECK( (NEW(CallExpr) (NEW(NumExpr)(7), NEW(NumExpr)(3) ) ) -> equals (NEW(CallExpr) (NEW(NumExpr)(7), NEW(NumExpr)(3) ) ) == true);
    }
}


TEST_CASE("Interp") {
    SECTION("NumExpr") {
        CHECK( (NEW(NumExpr)(5)) -> interp(NEW(EmptyEnv)) -> equals( NEW(NumVal)(5) ) );
        CHECK( (NEW(NumExpr)(-5)) -> interp(NEW(EmptyEnv)) -> equals( NEW(NumVal)(-5) ) );
        CHECK( (NEW(NumExpr)(0)) -> interp(NEW(EmptyEnv)) -> equals( NEW(NumVal)(0) ) );
    }
    
    SECTION("AddExpr") {
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5) ) ) -> interp(NEW(EmptyEnv)) -> equals((NEW(NumVal)(10) ) ) );
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(-5), NEW(NumExpr)(-5) ) ) -> interp(NEW(EmptyEnv)) -> equals((NEW(NumVal)(-10) ) ) );
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(-5), NEW(NumExpr)(5) ) ) -> interp(NEW(EmptyEnv)) -> equals((NEW(NumVal)(0) ) ) );
    }
    
    SECTION("MultExpr") {
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5) ) ) -> interp(Env::empty) -> equals((NEW(NumVal)(25) ) ) );
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(0) ) ) -> interp(Env::empty) -> equals((NEW(NumVal)(0) ) ) );
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(-5), NEW(NumExpr)(-5) ) ) -> interp(Env::empty) -> equals((NEW(NumVal)(25) ) ) );
    }
    
    SECTION("LetExpr") {
//        CHECK( (NEW(LetExpr)("x",
//                             NEW(NumExpr)(5),
//                             EW(AddExpr)(NEW(VarExpr)("x"), NEW(NumExpr)(5) ) )
//                -> interp()
//                -> equals(NEW(NumVal)(10) ) ) );
        CHECK( (NEW(LetExpr)("z",
                             NEW(NumExpr)(0),
                             NEW(MultExpr)(NEW(VarExpr)("z"), NEW(NumExpr)(5) ) ) )
              -> interp(Env::empty)
              -> equals(NEW(NumVal)(0) ) );
        //TODO: add tests for _let with Mult and Add, more complicated ones for _let
    }
    
    SECTION("BoolExpr") {
        CHECK( (NEW(BoolExpr)(true) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(true) ) );
        CHECK( (NEW(BoolExpr)(false) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(false) ) );
    }
    
    SECTION("EqulExpr") {
        CHECK( (NEW(EqulExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(5) ), NEW(NumExpr)(25) ) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(true) ) );
        CHECK( (NEW(EqulExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(4) ), NEW(NumExpr)(25) ) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(false) ) );
        CHECK( (NEW(EqulExpr)(NEW(AddExpr)(NEW(NumExpr)(5), NEW(NumExpr)(15) ), NEW(NumExpr)(20) ) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(true) ) );
        CHECK( (NEW(EqulExpr)(NEW(MultExpr)(NEW(NumExpr)(5), NEW(NumExpr)(10) ), NEW(NumExpr)(20) ) ) -> interp(Env::empty) -> equals(NEW(BoolVal)(false) ) );
    }
    
    SECTION("IfExpr") {
        CHECK( ( (NEW(IfExpr)(NEW(BoolExpr)(true), NEW(NumExpr)(5), NEW(VarExpr)("x") ) ) -> interp(Env::empty) -> equals(NEW(NumVal)(5) ) ) );
        CHECK( ( (NEW(IfExpr)(NEW(BoolExpr)(false), NEW(NumExpr)(5), NEW(NumExpr)(15) ) ) -> interp(Env::empty) -> equals(NEW(NumVal)(5) ) ) );
    }
    
    SECTION("FunExpr") {
        
    }
    
    SECTION("CallExpr") {
        
    }
}


TEST_CASE("Print") {
    SECTION("NumExpr") {
        CHECK( (NEW(NumExpr)(7) ) -> to_string() == "7" );
        CHECK( (NEW(NumExpr)(-7) ) -> to_string() == "-7" );
        CHECK( (NEW(NumExpr)(0) ) -> to_string() == "0" );
    }
    
    SECTION("AddExpr") {
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(5), NEW(AddExpr)(NEW(NumExpr)(25), NEW(NumExpr)(1) ) ) ) -> to_string() == "(5+(25+1))" );
        CHECK( (NEW(AddExpr)(NEW(NumExpr)(-5), NEW(AddExpr)(NEW(NumExpr)(25), NEW(NumExpr)(1) ) ) ) -> to_string() != "(-5+(25+1))" );
    }
    
    SECTION("MultExpr") {
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(5), NEW(MultExpr)(NEW(NumExpr)(25), NEW(NumExpr)(1) ) ) ) -> to_string() == "(5*(25*1))" );
        CHECK( (NEW(MultExpr)(NEW(NumExpr)(-5), NEW(MultExpr)(NEW(NumExpr)(25), NEW(NumExpr)(1) ) ) ) -> to_string() != "(-5*(25*1))" );
    }
    
    SECTION("VarExpr") {
        CHECK( (NEW(VarExpr)("7") ) -> to_string() == "7" );
        CHECK( (NEW(VarExpr)("18") ) -> to_string() == "18" );
    }
    
    SECTION("LetExpr") {
//        CHECK( (NEW(LetExpr) ("x",
//                              NEW(NumExpr)(5),
//                              NEW(AddExpr)(New(VarExpr)("x"), NEW(NumExpr)(5) ) ) )
//              -> to_string() == "(_let x=5 _in (x+5))" );
//        CHECK( (NEW(LetExpr) ("z",
//                              NEW(NumExpr)(10),
//                              NEW(AddExpr)(NEW(LetExpr)(New(VarExpr)("y"), NEW(NumExpr)(5) ) ) ) )
//              -> to_string() == "(_let z=10 _in ((y+5))" );
    }

    SECTION("BoolExpr") {
        CHECK( (NEW(BoolExpr)(true) ) -> to_string() == "_true" );
        CHECK( (NEW(BoolExpr)(false) ) -> to_string() == "_false" );
    }

    SECTION("EqulExpr") {
        CHECK( (NEW(EqulExpr) (NEW(NumExpr)(5), NEW(NumExpr)(5) ) ) -> to_string() == "5==5" );
        CHECK( (NEW(EqulExpr) (NEW(NumExpr)(0), NEW(NumExpr)(0) ) ) -> to_string() == "0==0" );
        CHECK( (NEW(EqulExpr) (NEW(NumExpr)(-5), NEW(NumExpr)(-5) ) ) -> to_string() == "-5==-5" );
    }

    SECTION("IfExpr") {
        CHECK(
              (NEW(IfExpr)(
                           NEW(BoolExpr)(true),
                           NEW(NumExpr)(3),
                           NEW(NumExpr)(2)
                           )
              ) -> to_string() == "(_if _true _then 3 _else 2)"
        );
        CHECK(
              (NEW(IfExpr)(
                           NEW(NumExpr)(5),
                           NEW(BoolExpr)(true),
                           NEW(BoolExpr)(false)
                           )
              ) -> to_string() == "(_if 5 _then _true _else _false)"
        );
    }

    SECTION("FunExpr") {
        CHECK(
              (NEW(FunExpr)(
                            "x",
                            NEW(NumExpr)(5)
                            )
               )
              -> to_string() == "(_fun (x) 5)"
        );
        CHECK(
              (NEW(FunExpr)(
                            "z",
                            NEW(NumExpr)(-5)
                            )
               )
              -> to_string() == "(_fun (z) -5)"
        );
    }

    SECTION("CallExpr") {
        CHECK(
              (NEW(CallExpr)(
                             NEW(FunExpr)(
                                          "x",
                                          NEW(AddExpr)(
                                                       NEW(NumExpr)(5),
                                                       NEW(VarExpr)("x")
                                                       )
                                          ),
                             NEW(NumExpr)(2)
                             )
               )
              -> to_string() == "((_fun (x) (5 + x)) (2))"
        );
    }
}


TEST_CASE("Subst") {
    SECTION("NumExpr") {
        CHECK(
                (NEW(NumExpr)(5)
             )
               -> subst("x", NEW(NumExpr)(10)
                        )
               -> equals(NEW(NumExpr)(5)
                        )
        );
    }
    
    SECTION("AddExpr") {
        CHECK(
              (NEW(AddExpr)(
                            NEW(NumExpr)(2),
                            NEW(VarExpr)("x")
                            )
               )
               -> subst("x", NEW(NumExpr)(3)
                          )
               -> equals(NEW(AddExpr)(NEW(NumExpr)(2), NEW(NumExpr)(3)
                                      )
                         )
              );
    }
    
    SECTION("MultExpr") {
        CHECK(
              (NEW(MultExpr)(
                             NEW(NumExpr)(2),
                             NEW(VarExpr)("x")
                             )
               )
              -> subst("x", NEW(NumExpr)(3)
                       )
              -> equals(NEW(MultExpr)(
                                      NEW(NumExpr)(2),
                                      NEW(NumExpr)(3)
                                      )
                        )
            );
    }
    
    SECTION("VarExpr") {
        CHECK(
                (NEW(VarExpr)("x")
              ) -> subst("x", NEW(NumExpr)(3)
                       )
               -> equals(NEW(NumExpr)(3)
                       )
        );
    }
    
    SECTION("LetExpr") {
        CHECK(
              (NEW(LetExpr)(
                            "x",
                            NEW(NumExpr)(3),
                            NEW(AddExpr)(
                                         NEW(VarExpr)("y"),
                                         NEW(NumExpr)(2)
                                         )
                            )
               )
              -> subst("y",NEW(NumExpr)(5)
                       )
              ->equals(NEW(LetExpr)(
                                    "x",
                                    NEW(NumExpr)(3),
                                    NEW(AddExpr)(
                                                 NEW(NumExpr)(5),
                                                 NEW(NumExpr)(2)
                                                 )
                                    )
                       )
              );
    }
    
    SECTION("BoolExpr") {
        CHECK(
              (NEW(BoolExpr)(true)
              )
              -> subst("x", NEW(NumExpr)(5)
                       )
              -> equals(NEW(BoolExpr)(true)
                        )
        );
    }
    
    SECTION("EqulExpr") {
        CHECK(
              (NEW(EqulExpr)(
                             NEW(NumExpr)(5),
                             NEW(VarExpr)("x")
                             )
               )
              -> subst("x", NEW(NumExpr)(15)
                       )
              -> equals(NEW(EqulExpr)(
                                      NEW(NumExpr)(5),
                                      NEW(NumExpr)(15)
                                      )
                        )
              );
    }
    
    SECTION("IfExpr") {
        
        CHECK(
              (NEW(IfExpr)(
                           NEW(BoolExpr)(true),
                           NEW(VarExpr)("x"),
                           NEW(NumExpr)(2)
                           )
               )
              -> subst("x", NEW(NumExpr)(5)
                       )
              -> equals(NEW(IfExpr)(
                                    NEW(BoolExpr)(true),
                                    NEW(NumExpr)(5),
                                    NEW(NumExpr)(2)
                                    )
                        )
              );
    }
    
    SECTION("FunExpr") {
        CHECK(
              (NEW(FunExpr)(
                            "x",
                            NEW(NumExpr)(4)
                            )
               )
              -> subst(
                       "x",
                       NEW(NumExpr)(5)
                       )
              -> equals(NEW(FunExpr)(
                                     "x",
                                     NEW(NumExpr)(4)
                                     )
                        )
              );
        CHECK(
              (NEW(FunExpr)(
                            "x",
                            NEW(VarExpr)("y")
                            )
               )
              -> subst(
                       "y",
                       NEW(NumExpr)(2)
                       )
              -> equals(
                        NEW(FunExpr)(
                                     "x",
                                     NEW(NumExpr)(2)
                                     )
                        )
              );
    }
    
    SECTION("CallExpr") {
        CHECK(
              (NEW(CallExpr)(
                             NEW(FunExpr)(
                                          "x",
                                          NEW(AddExpr)(
                                                       NEW(NumExpr)(5),
                                                       NEW(VarExpr)("y")
                                                       )
                                          ),
                             NEW(NumExpr)(2)
                             )
               )
              -> subst(
                       "y",
                       NEW(NumExpr)(2)
                       )
              -> equals(
                        (NEW(CallExpr)(
                                       NEW(FunExpr)(
                                                    "x",
                                                    NEW(AddExpr)(
                                                                NEW(NumExpr)(5),
                                                                 NEW(NumExpr)(2)
                                                                 )
                                                    ),
                                       NEW(NumExpr)(2)
                                       )
                                )
                        )
        );
    }
}
