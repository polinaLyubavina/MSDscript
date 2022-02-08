#include "cmdline.h"
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#define CATCH_CONFIG_RUNNER
#include "catch.h"


    // definition for use_arguments
    std::string help = "--help"; 
    std::string test = "--test"; 
    std::string interp = "--interp";
    std::string print = "--print";
    std::string pretty_print = "--pretty-print";

    std::string allowed_arguments = "Allowed arguments:\n --test\n --help\n --interp\n --print\n --pretty-print\n";
    std::ostream& cmdline_output;       // cmdline output
    std::istream& cmdline_input;        // stores input from cmdline

void use_arguments(int argc, char **argv) {

    std::string argvalue1 = argv[1];

    //begin command line output
    if(argc == 2) {

        if(argvalue1.compare(help) == 0) {
            std::cout << allowed_arguments;
        }

        else if(argvalue1.compare(test) == 0) {
            // std::cout << "Tests passed\n";
            Catch::Session().run(1, argv);
        }

        else if(argvalue1.compare(interp) == 0) {
            
        }

        else if(argvalue1.compare(print) == 0) {
            exit(0);
        }

        else if(argvalue1.compare(pretty_print) == 0) {
            exit(0);
        }

        else {
            std::cerr << "Error \n";
            exit(1);
        }
    }

    if(argc == 3) {
        
        std::string argvalue2 = argv[2];

        if(argvalue1.compare(test) == 0 && argvalue2.compare(test) == 0) {
            std::cerr << "Error \n";
            exit(1);
        }

    }

}