#include "expr.h"
#include "catch.h"
#include <stdexcept>

/******************
 *     TESTS
*******************/

TEST_CASE("equals") {

    /******************
    Num Tests
    *******************/
    CHECK((new Num(5))->equals(new Num(7)) == false);
    CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(5), new Num(7))) == true);
    // CHECK((new Add(new Num(5), new Num(7)))->equals(new Add(new Num(7), new Num(5))) == true);
    CHECK((new Mult(new Num(5), new Num(7)))->equals(new Mult(new Num(5), new Num(7))) == true);

    /******************
    Num Tests where lhs and rhs don't == on both sides
    *******************/
    // CHECK((new Add(new Num(7), new Num(5)))->equals(new Add(new Num(5), new Num(7))) == true);

    /******************
    Var Tests
    *******************/
    CHECK((new Var("5"))->equals(new Var("7")) == false);
    CHECK((new Add(new Var("cookie"), new Var("batter")))->equals(new Add(new Var("cookie"), new Var("batter"))) == true);
    CHECK((new Mult(new Var("5"), new Var("7")))->equals(new Mult(new Var("5"), new Var("7"))) == true);

    /******************
    Interp Tests
    *******************/
    Num* num1 = new Num(5);
    Num* num2 = new Num(7);
    Add* add1 = new Add(num1, num2);
    CHECK(add1->interp() == 12);

    CHECK((new Num(5))->interp() == 5);

    Mult* mult = new Mult(num1, num2);
    CHECK(mult->interp() == 35);

    CHECK_THROWS_WITH( (new Var("x"))->interp(), "A Variable has no value" );

    /******************
    has_variable Tests
    *******************/
    CHECK((new Var("5"))->has_variable() == true);
    CHECK((new Num(7))->has_variable() == false);
    CHECK((new Add(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Mult(new Num(7), new Var("7")))->has_variable() == true);
    CHECK((new Add(new Num(7), new Num(7)))->has_variable() == false);
    CHECK((new Mult(new Num(7), new Num(7)))->has_variable() == false);

    /******************
    Subst Tests
    *******************/
    CHECK( (new Add(new Var("x"), new Num(7)))
       ->subst("x", new Var("y"))
       ->equals(new Add(new Var("y"), new Num(7))) );

    /******************
    Print and Pretty_Print Tests
    *******************/
    (new Num(5)) -> print(std::cout); 

};