# MSDSCRIPT

MSDScript was created as a semester-long project for the Software Engineering course for Master's of Software Development degree at the University of Utah. 

## Description
-----
### What it is

The MSDScript project is an interpreter built with a C++ foundation and based losely on JavaScript. MSDScript allows for parsing and interpreting of mathematical expressions. 
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

MSDScript is built and ran from the command line. Users can input an expression which the MSDScript will then parse and interpret. 

The MSDScript follows a basic mathematical precedence, including:
1. Booleans
2. Multiplication
3. Addition
4. Let
5. If/Else, Function, Equivalence, and Call Expressions

## Getting Started
-----
MSDScript runs from the command line, so navigate to the directory and run the following commands.

* `make`
Creates the MSDScript executable

* `./msdscript` 
This will run the program and execute any commands you pass to it

### Usage Guide

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
  - Use the == for which the MSDScript will return a Boolean Expression
  - The == can work on any value, such as booleans, numbers and variables, etc.
  - Only a Boolean Expression can be equivalent to a Boolean Expression, and only a Numerical Expression can be equivalent to a Numerical Expression.
  - Examples
    - 15 == 15
    - _true == _false 
    - _true == _true

## Cmdline 
-----

* --help
* --print
* --pretty-print
* --interp
* --test
* 'Ctrl+D'
    - to submit input
    
## Files
-----

Files included in the MSDScript:

- main.cpp
- cmdline.cpp & cmdline.h
    - contain everything necessary for the commandline arguments to function
- expr.cpp & expr.h
    - used for expression classes
- parse.cpp & parse.h
    - used for parsing
- val.cpp & val.h
    - used for values
- pointer.h
    - used for regular and shared pointers
- test_msdscript
    - tests the program against itself or two programs against each other
- exec.cpp & exec.h
    - used for test_msdscript 
- env.cpp & env.h
    - environment variables
- Makefile
    - used to compile program
- catch.h
    - used to run tests
