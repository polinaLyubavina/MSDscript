#include <string>
#include <iostream>

#include "exec.h"


//Helper function to compare lhs & rhs
void compare(int argc, char *const *argv, const ExecResult &lhs, const ExecResult &rhs) {
    
    if(!rhs.err.empty() || !rhs.out.empty() ) {
        std::cout << "\n rhs: " << "\n Out: " << rhs.out << "\n EXIT_CODE: " << rhs.exit_code << "\n Error: " << rhs.err << "\n";
    }
    
    else {
        
        if(argc == 3) {
            std::cerr << argv[2] << "Missing Output. Double-check for Errors \n";
        }
        
        else {
            std::cerr << argv[1] << "Missing Output. Double-check for Errors \n";
        }
        
        exit(1);
    }
    
    if(!lhs.err.empty() || !lhs.out.empty() ) {
        std::cout << "\n lhs: "<< "\nOut: " << lhs.out << "\n EXIT_CODE: " << lhs.exit_code << "\n Error: " << lhs.err << "\n";
    }
    
    else {
        std::cerr << argv[1] << "Missing Output. Double-check for Errors \n";
        exit(1);
    }
}

std::string random_expr_string();

int main(int argc, char **argv) {
    
    const char * const interp_argv[] = { argv[1], "--interp" };
    const char * const print_argv[] = { argv[1], "--print" };
    const char * const pretty_print_argv[] = { argv[1], "--pretty-print" };

    for(int i = 0; i < 100; i++) {
        
        // Generate random input and run print + interp
        std::string in = random_expr_string();
        std::cout << "Trying " << i + 1 << " " << in << "\n";
        ExecResult interp_result = exec_program(2, interp_argv, in);
        ExecResult print_result = exec_program(2, print_argv, in);
        
        if (argc == 2) {
            ExecResult second_interp_result = exec_program(2, interp_argv, print_result.out);
            
            if (interp_result.out.compare(second_interp_result.out) != 0) {
                throw std::runtime_error("Different result for --print\n");
            }
        } else if (argc == 3) {
            const char * const different_interp_argv[] = { argv[2], "--interp" };
            const char * const different_print_argv[] = { argv[2], "--print" };
            
            ExecResult different_interp_result = exec_program(2, different_interp_argv, in);
            ExecResult different_print_result = exec_program(2, different_print_argv, in);
            
            if (print_result.out.compare(different_print_result.out) != 0) {
                throw std::runtime_error("Different result for --print\n");
            }
            
            if (interp_result.out.compare(different_interp_result.out) != 0) {
                throw std::runtime_error("Different result for --interp\n");
            }
        } else {
            throw std::runtime_error("Too many command line arguments");
        }
    }
    
    return 0;
}

//Generates random Expressions to be tested
std::string random_expr_string() {
    
    int test = rand() % 100;
    
    if (test < 10)
        return std::to_string(rand());
    
    if (test < 20)
        return "-" + std::to_string(rand());
    
    if (test < 30)
        return "_true";
    
    if (test < 40)
        return "_false";
    
    if (test < 50) {
        return random_expr_string() + " + " + random_expr_string();
    }
    
    if (test < 60) {
        return random_expr_string() + " * " + random_expr_string();
    }
    
    if (test < 70) {
        return "x";
    }
    
    if (test < 80) {
        return "_let x = " + random_expr_string() + " _in " + random_expr_string();
    }
    
    if (test < 90) {
        return "_if " + random_expr_string() + " _then " + random_expr_string() + " _else " + random_expr_string();
    }
    if (test < 100) {
        return random_expr_string() + " == " + random_expr_string();
    }
    
    return std::to_string(rand());
}
