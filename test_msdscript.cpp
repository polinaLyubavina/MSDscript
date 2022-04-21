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
    
    const char * const interp_argv2[] = { argv[2], "--interp" };
    const char * const print_argv2[] = { argv[2], "--print" };
    
    std::string in = random_expr_string();
    
    ExecResult interp_result = exec_program(2, interp_argv, in);
    ExecResult print_result = exec_program(2, print_argv, in);
    ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
    
    ExecResult interp_result2 = exec_program(2, interp_argv, in);
    ExecResult print_result2 = exec_program(2, print_argv, in);
    ExecResult interp_again_result2 = exec_program(2, interp_argv, print_result.out);
    
    if(argc == 2) {

        for(int i = 0; i < 100; i++) {
            
            std::cout << "Trying " << i + 1 << in << "\n";
            
            if(interp_again_result.exit_code == 0 && interp_result.exit_code == 0) {
                
                if (interp_again_result.out != interp_result.out)
                    
                    compare(argc, argv, interp_result, interp_again_result);
                    throw std::runtime_error("Different result for printed \n");
            }
            
            interp_again_result = exec_program(2, interp_argv, print_result.out);
            
            if(interp_again_result.out != interp_result.out) {
                
                compare(argc, argv, interp_result, interp_again_result);
                throw std::runtime_error("Different result for printed \n");
            }
            
            else {
                std::cerr << "Program Exited With Error \n";
                return 1;
            }
        }
    }
    
    else if(argc == 3) {
        
        for(int i = 0; i < 100; i++) {
            
            std::cout << "Trying " << i + 1 << in << "\n";

            if(interp_result.exit_code == 0 && interp_result2.exit_code == 0) {
                
                if(interp_result.out != interp_result2.out) {
                    
                    compare(argc, argv, print_result, print_result2);
                    throw std::runtime_error("Different result for interpret \n");
                }
                
                else if (print_result.out != print_result2.out) {
                    
                    compare(argc, argv, print_result, print_result2);
                    throw std::runtime_error("Different result for interpret \n");
                }
                
                else {
                    std::cerr << "Program Exited With Error \n";
                    return 1;
                }
            }
        }
    }
    
    else {
        std::cerr << "Error: No Program Names Entered" << std::endl;
        return 1;
        
    }
    
    std::cout << "Tests Passed Successfully \n";
    return 0;
}

//Generates random Expressions to be tested
std::string random_expr_string() {
    
    int test = rand() % 10;
    
    if (test < 6)
        return std::to_string(test);
    
    else if (test < 8) {
        return random_expr_string() + "+" + random_expr_string();
    }
    
    else if (test < 10) {
        return random_expr_string() + "*" + random_expr_string();
    }
    
    else {
        return std::to_string(test);
    }
}
