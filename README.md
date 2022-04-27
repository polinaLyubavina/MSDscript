# MSDscript

MSDscript was created as a semester-long project for the Software Engineering course for Master's of Software Development degree at the University of Utah. 

## Description
-----
### What it is

The MSDscript project is an interpreter built with a C++ foundation and based losely on JavaScript. MSDscript allows for parsing and interpreting of mathematical expressions from the comfort of your command line. The MSDscript may also be embedded into other programs.

The mathematical expressions include:
- Function Expressions
- Numerical Expressions
- Variable Expressions
- Addition Expressions
- Multiplication Expressions
- Let Expressions
- Boolean Expressions
- If/Else Expressions
- Equivalence Expressions
- Call Expressions

### Use

MSDscript is built and ran from the command line. Users can input an expression which the MSDscript will then parse and interpret. 

The MSDscript follows a basic mathematical precedence, including:
1. Booleans
2. Multiplication
3. Addition
4. Let
5. If/Else, Function, Equivalence, and Call Expressions

## Getting Started
-----
MSDscript runs from the command line, so navigate to the directory and run the following commands.

* `make`
Creates the MSDscript executable

* `./msdscript` 
This will run the program and execute any commands you pass to it

## User Guide
-----

- Numerical Expressions
  - Numbers can be positive or negative. 
  - Not allowed: decimals, commas, division, or spaces.
  - Examples
    - -20
    - 1000000000
    - 0

- Variables
  - Unbroken strings of uppercase or lowercase letters that contain no numbers or spaces.
  - Examples 
    - EXPR
    - expr
    - y

- Addition
  - Use the + operator
  - Do not use the - operator
  - Examples
    - 5 + 5
    - 5 + -5
    - 5 + (-5)

- Multiplication
  - Use the * operator
  - Do not use the / operator
  - Examples
    - 5 * 5
    - 5 * -5
    - 5 * (-5)

- Let Expressions
  - Use the following format: _let (variable) = (expression) _in (expression)
  - Example
    - _let x = 5 _in x + 15

- Boolean Expressions
  - Use the keywords: _true or _false
  - Do not use false or true, 1 or 0
  - Examples
    - _true
    - _false

- If/Else Expressions
  - Use the keywords: _if (boolean) _then (expression) _else (expression)
  - A _ must be in front of the keywords
  - The program will return the _if if the Boolean Expression is true, and the _else if the Boolean Expression is false
  - Place a boolean expression after the _if, otherwise the program will throw an error
  - Examples
    - _if _false _then 5 _else 20
    - _if 15 == 15 _then 15 _else 5

- Equivalence Expressions
  - Use the == for which the MSDscript will return a Boolean Expression
  - The == can work on any value, such as booleans, numbers and variables, etc.
  - Only a Boolean Expression can be equivalent to a Boolean Expression, and only a Numerical Expression can be equivalent to a Numerical Expression.
  - Examples
    - 15 == 15
    - _true == _false 
    - _true == _true

## Command Line Interface 
-----

* --help
    - will print all the options available for you to use with the program
* --print
* --pretty-print
* --interp
* --test
* 'Ctrl+D'
    - to submit input for interpretation or printing by the program
    
## API Documentation
-----

The files included in the MSDscript:
- main.cpp
    - the program runs through the main 
- cmdline.cpp & cmdline.h
    - contains everything necessary for the commandline arguments to function
- expr.cpp & expr.h
    - used for expression classes
- parse.cpp & parse.h
    - used for parsing
- val.cpp & val.h
    - used for values
- pointer.h
    - used for regular and shared pointers
- env.cpp & env.h
    - used for environment variables
- Makefile
    - used to compile the program
- catch.h
    - used to run tests
    
#### Expr Functions
    - equals(PTR(Expr) compared_against)
        - returns a boolean to determine if two expressions are equivalent
    - interp(PTR(Env) env)
        - returns a Val pointer that represents the interpreted expression
    - to_string()
        - returns a printed string
    - subst(std::string var, PTR(Expr) substitute)
        - returns an Expr pointer 
    - print(std::ostream& output)
        - returns void and prints out to the command line

#### Expr Subtypes
    - NumExpr
        - Numeric Expressions
    - AddExpr
        - Addition Expressions
    - MultExpr
        - Multiplication Expressions
    - VarExpr
        - Variable Expressions
    - LetExpr
        - Let Expressions
    - BoolExpr
        - Boolean Expressions
    - EqualExpr
        - Equivalence Expression
    - IfExpr
        - Else/If Expressions
    - FunExpr
        - Function Expressions
    - CallExpr
        - Call to a Function Expressions

#### Val Functions
    - equals(Val* input) 
        - Returns a boolean to determine if two expressions are equivalent
    - add_to(Val* input)
        - Returns a Val pointer after performing addition 
    - to_expr()
        - Returns an Expr pointer after converting the Val to an Expr
    - call(Val* actual_argument) 
        - Returns a Val pointer
    - mult_to(Val* input)
        - Returns a Val pointer after performing multiplication
    - to_string()
        - Returns a printed string

#### Val Subtypes
    - NumVal
        - Number Value
    - BoolVal  
        - Boolean Value
    - FunVal
        - Function Value

#### Parser
    - parse(std::istream &input)
        - Parses user input into an expression and returns an Expr pointer
    - parse_expr(std::istream &input)
        - Returns Expr pointer and parses an Expression
    - parse_num(std::istream &input)
        - Parses a number and returns an Expr pointer
    - parse_var(std::istream &input)
        - Parses a variable and returns an Expr pointer
    - parse_let(std::istream& input)
        - Parses a let expression and returns and Expr pointer
    - parse_if(std::istream& input)
        - Parses an if expression and returns an Expr pointer
    - parse_str(std::string s)
        - Parses a string and returns an Expr pointer
