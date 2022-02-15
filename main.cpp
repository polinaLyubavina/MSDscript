#include "cmdline.h"
#include "expr.h"
#include <iostream>

int main(int argc, char **argv)
{
    try {
        use_arguments(argc, argv); 
        return 0;
    }
    catch (std::runtime_error exception) {
        std::cerr << exception.what() << "\n";
        return 1;
    }

}
