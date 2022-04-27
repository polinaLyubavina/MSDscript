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

MSDscript runs from the command line, so navigate to its directory and run the following commands:

* `make`
Creates the MSDscript executable

* `./msdscript` 
This will run the program and execute any commands you pass to it

### Command Line Arguments 
-----

* --help
    - will print all the options available for you to use with the program
* --print
* --pretty-print
* --interp
* --test
* 'Ctrl+D'
    - to submit input for interpretation or printing by the program
    
## User Guide
-----

The MSDscript contains Expressions and Values. They are different. Expressions are un-interpreted equations, and Values are the interpreted results.  

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
  - Use the `+` operator
  - Do not use the `-` operator
  - Examples
    - 5 + 5
    - 5 + -5
    - 5 + (-5)

- Multiplication
  - Use the `*` operator
  - Do not use the `/` operator
  - Examples
    - 5 * 5
    - 5 * -5
    - 5 * (-5)

- Let Expressions
  - Use the following format: `_let` (variable) = (expression) `_in` (expression)
  - Example
    - _let x = 5 _in x + 15

- Boolean Expressions
  - Use the keywords: `_true` or `_false`
  - Do not use false or true, 1 or 0
  - Examples
    - _true
    - _false

- If/Else Expressions
  - Use the keywords: `_if` (expression with a boolean value) `_then` (expression) `_else` (expression)
  - A `_` must be in front of the keywords
  - Place a boolean expression after the `_if`, otherwise the program will throw an error
  - Examples
    - _if _false _then 5 _else 20
    - _if 15 == 15 _then 15 _else 5

- Equivalence Expressions
  - Use the `==` for which the MSDscript will return a Boolean Expression
  - The` ==` can work on any value, such as booleans, numbers and variables, etc.
  - A Boolean Expression can be equal to a Boolean Expression if their Values are equal. Similarly, a Numerical Expression can be equal to a Numerical Expression if their Values are equal.
  - Examples
    - 15 == 15
    - _true == _false 
    - _true == _true

- Fun Expr
  - Fun Exprs represent a function in the MSDscript. 
  - The Fun Expr has an argument that is passed to it as a string, and an Expr that makes up the body of the function.
  - Example
    - `_fun` (expression) (expression)
    
    
## API Documentation
-----
    
###Files

The files included in the MSDscript are:

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
    
### External Functions
To get an easy start on using the MSDscript, just use the three main functions below. They will allow you to interpret your input, parse your functions, and conver anything to a string. 

#### Interp
    - PTR(Val) interp(PTR(Env) env)
        - returns a Val that represents the interpreted expression which can be converted to a string
        
#### String
    - std::string to_string()
        - converts an expression to a string

#### Parse
    - PTR(Expr) parse(std::istream &input)
        - Parses an expression provided by the user through an istream input, and returns the entire input as an Expr
        

