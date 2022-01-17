#include "cmdline.h"
#include <iostream>
#include <string.h>
#define CATCH_CONFIG_RUNNER
#include "catch.h"


// definition for use_arguments

void use_arguments(int argc, char **argv) {

    std::string argvalue1 = argv[1];
    std::string help = "--help"; 
    std::string test = "--test"; 

    if(argc == 2) {

        if(argvalue1.compare(help) == 0) {
            std::cout << "Arguments available to you are: --test, --help\n";
        }

        else if(argvalue1.compare(test) == 0) {
            // std::cout << "Tests passed\n";
            Catch::Session().run(1, argv);
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